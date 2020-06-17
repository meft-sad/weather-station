#include <Arduino.h>

#include <dht.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_BMP280.h> 


#define DHT11_PIN 17



dht DHT;
Adafruit_BMP280 bmp; 

int flagMatrix = 0;
int flagPrint = 0;
int flagMemory = 0;
int inc0 = 0;
int inc1 = 0;
int hum = 0;
int add = 0; //counter 
int i = 0;  // counter 
int r1 = 0; // counter
int c1 = 0; // counter
float press[71];


int pins[17]= { 99, 5, 4, 3, 2, 99, 15, 16, 99, 13, 12, 11, 10, 9, 8, 7, 6};
int cols[8] = {pins[13], pins[10], pins[15], pins[9], pins[4], pins[16], pins[6], pins[1]};
int rows[8] = {pins[8], pins[7], pins[3], pins[14], pins[2], pins[12], pins[11], pins[5]};
int vect[65];



int carSun [65] = {   // sun matrix
 99,                  // value "99" it's filler, used to fill the first(useless) tab spot
 0,0,0,0,0,0,0,0,
 0,0,1,0,0,0,1,0,
 0,0,0,1,0,1,0,0,
 0,1,1,1,1,0,0,0,
 0,0,0,1,1,1,1,0,
 0,0,1,0,1,0,0,0,
 0,1,0,0,0,1,0,0,
 0,0,0,0,0,0,0,0,
};

 int carCloud [65] = {   // cloud matrix
 99,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,1,1,0,1,1,0,0, 
 1,1,1,1,1,1,1,0,
 1,1,1,1,1,1,1,1,
 0,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 };

void setup(){
  cli(); //stop interrupts 

  //set timer0 interrupt at 62Hz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 62hz increments
  OCR0A = 252;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);


//set timer1 interrupt at 0.24Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 0.24hz increments
  OCR1A = 65104;// = (16*10^6) / (0.24*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
  
  Serial.begin(9600);

  if(!bmp.begin(0x76)){ 
      Serial.println(F("Sensor BMP280 not recognised")); 
      while(1);
    } 

  for (int i = 1; i <= 16; i++){ // I'm defining at output all the ports in the array pin
      pinMode(pins[i], OUTPUT);
    }

  for (int i = 1; i <= 8; i++) {// I'm switching off all the pin
    digitalWrite(cols[i - 1], LOW);
    digitalWrite(rows[i - 1], LOW);
    }
}

ISR(TIMER0_COMPA_vect){
  inc0 = inc0 + 1;  // increment the global value untill it reaches 248 meaning that 4s have passed
  if (inc0 == 248)
  {
    flagPrint = 1; // set the flag up in order to stamp the variable
    inc0 = 0;      // clear the global variable in order to restart to count 4 second
  }
}

ISR(TIMER1_COMPA_vect){
  inc1 = inc1 + 1;  // increment the global value untill it reaches 864 meaning that 1 hour has passed
  if (inc1 == 864)
  {
    flagMemory = 1; // set the flag up in order to write in the EEPROM
    inc1 = 0;       // clear the global variable in order to restart to count 1 hour 
  }
}

void loop(){

    if (flagPrint == 1) // timer interrupts make the variable be printed
  {
     int chk = DHT.read11(DHT11_PIN);

    Serial.print(F("Temperature: ")); 
    Serial.print(bmp.readTemperature()); 
    Serial.println(" °C ");
    
    Serial.print(F("Pressure: ")); 
    Serial.print(bmp.readPressure()); 
    Serial.println(" Pa "); 

    Serial.print(F("Humidity: "));
    Serial.print(DHT.humidity);
    Serial.println(" %");

    Serial.println("-----------------------------------"); 

    flagPrint = 0;
  }

 

  
  if (flagMemory == 1)
  {
    hum = DHT.humidity;
    press[add] = bmp.readPressure();
    if (add >= 3)
    {
     if (hum >= 65)
     {
       if ((press[add-3]-press[add]) >= 200 || flagBadW == 1 )
       {
         flagMatrix = 1;
         flagBadW = 1;
       }else
        {
          flagMatrix = 0;
          flagBadW = 0;
        }
      }
    
    if (add == 71)
      {
        add = 0;
      }else
        {
        add = add + 1;
        }
    }
  flagMemory = 0;
  }

  if (flagMatrix == 0)
  {
   for (int i = 1; i <= 64; i++){
        vect[i] = carSun[i];
    }
  }else
  {
    for (int i = 1; i <= 64; i++){
        vect[i] = carCloud[i];
    }
}
  
  for (r1 = 1; r1 <= 8; r1 ++){
    for (c1 = 1; c1 <= 8; c1 ++){
      if (vect [(r1-1)*8 + c1] == 1){ // BYTE = 1 (led to switch on)
          digitalWrite (rows [r1-1], HIGH); // active row (anod)
          digitalWrite (cols [c1-1], LOW); // disactive (catod) and switch on the led on the display
        }
       digitalWrite (rows [r1-1], LOW); // disable the row (anod)
       digitalWrite (cols [c1-1], HIGH); // enable the column (catod) and switch off the led

    }
  } 
}
