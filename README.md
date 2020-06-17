# Weather-station project
### Giovanni De Angelis
## Introduction
This project's aim is to provide to the users a very simple weather station capable to predict the weather in the next 6/12 hour. The weather station will be created by means of the microcontroller Arduino UNO , two sensor and a 8x8 LED matrix. In order to predict the weather a simple model based on pressure and humidity will be used. Here you can se the [circuit schematic](https://github.com/meft-sad/weather-station/blob/master/Schematic.png).

## Model
The best way to predict the weather in a simple and economical way is to study the pressure variation in the last 3/6 hours. Indeed a decreasing of pressure means that there is a good probability to have a worse weather from that time on. On the other side an increasing of pressure in last hours it's a good signal of a better weather coming.
In particular the bigger is the dicreasing of the pressure the fatster the change of the weather will be : a decreasing of 1-2 hPa is a signal of worse weather in the next one or two days; a decreasing of 2-3 hPa is a signal of worse weather in the next 12-24 hours and finally a decrasing of 5-6 hPa is a signal of an incoming storm in the next three hours.
However a change of pressure is not always a signal of a change of weather: that's way monitoring also the humidity can be a good idea in order to improve the model.
Alongside the monitoring of the pressure as explained before, if the humidity is above 70 % and the pressure is decreased in last hours the probability to have a bad weather is even bigger. On the other side, if the the humidity is below 70 % and the pressure is recently increased the weather is going to be good.
It's worth noticing the this project's goal is not to be a perfect weather predictor but it's to be a good indication on the possible weather that the users can find in the following hours.

## Sensors
The sensors used in this project are (with attached the corresponding complete datasheet)
* [DHT11](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf) : temperature and humidity pressure 
* [BMP280](https://cdn-shop.adafruit.com/datasheets/BST-BMP280-DS001-11.pdf) : temperature and atmosferic pressure sensor

## Outputs
The outputs of this projects are mainly two: 
* Serial monitor : the temperature, the pressure and the humidity are printed on the serial monitor every 4 seconds in order to allow the users to know the mentioned parameter in real time.
* 8x8 LED matrix : this device has been used in order to show the estimation done about the weather. Depending on the estimation about the weather a scheme of a sun or of a cloud will be printed. Due to a lack of pin on the UNO arduino board used the matrix has been used as a 7x7 LED matrix in order to gain 2 pin that have been used for other purpose explained here after.

## Interrupts
In this project only internal interrupts have been used, precisely the timer interrupts. The UNO arduino board has three timer called Timer0, Timer1 and Timer2: the first two are 8-bit clocks while the last one is a 16 bit clock. In the project only two time interrupts are used : one for the print of the parameter on the serial monitor and on other to compare the pressure values in order to make the weather estimations. The first one has to allow the print operation every 4 seconds while the second one has to allow the comparation operations every one hour. Since the print operations are needed to be performed more often an 8 bit clock has been used while for the comparation operations the 16 bit has been used. In both case a prefactor is needed in the set up of the interrupts in order to reduce the frequency at which the cloch increment a counter. After this operation two global variables have been used in order to reach the exact time in both cases. When the latter counter reaches the right value a flag has been set up and the relative part of the code is performed. Looking at the code is possible to see the this at line 63-73/108-114 regarding the 4s interrupt and 76-87/117-124 regarding the 1h interrupt.


