# Weather-station project
### Giovanni De Angelis
## Introduction
This project's aim is to provide to the users a very simple weather station capable to predict the weather in the next 6/12 hour. The weather station will be created by means of the microcontroller Arduino UNO , two sensor and a 8x8 LED matrix. In order to predict the weather a simple model based on pressure and humidity will be used. Here you can see the [circuit schematic](https://github.com/meft-sad/weather-station/blob/master/Schematic.png), and the table with all the connection between hardware a board is the following :

![tabella](https://github.com/meft-sad/weather-station/blob/master/tabella.JPG)

## Model
The best way to predict the weather in a simple and economical way is to study the pressure variation in the last 3/6 hours. Indeed a decreasing of pressure means that there is a good probability to have a worse weather from that time on.
In particular the bigger is the dicreasing of the pressure the faster the change of the weather will be : a decreasing of 1-2 hPa is a signal of worse weather in the next one or two days; a decreasing of 2-3 hPa is a signal of worse weather in the next 12-24 hours and finally a decreasing of 5-6 hPa is a signal of an incoming storm in the next three hours.
However a change of pressure is not always a signal of a change of weather: that's way monitoring also the humidity can be a good idea in order to improve the model.
Alongside the monitoring of the pressure as explained before, if the humidity is above 65 % and the pressure is decreased in last hours the probability to have a bad weather is even bigger. On the other side, if the the humidity is below 65 % the weather is going to be good.
It's worth noticing the this project's goal is not supposed to be a perfect weather predictor but it's to be a good indication on the possible weather that the users can find in the following hours.

## Sensors
The sensors used in this project are (with attached the corresponding complete datasheet)
* [DHT11](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf) : temperature and humidity pressure 
* [BMP280](https://cdn-shop.adafruit.com/datasheets/BST-BMP280-DS001-11.pdf) : temperature and atmosferic pressure sensor

## Outputs
The outputs of this projects are mainly two: 
* Serial monitor : temperature, pressure and humidity are printed on the serial monitor every 4 seconds in order to allow the users to know the mentioned parameters in real time.
* 8x8 LED matrix : this device has been used in order to show the estimation done about the weather. Depending on the estimation about the weather a scheme of a sun or of a cloud will be printed. Due to a lack of pin on the UNO arduino board used, the matrix has been used as a 7x7 LED matrix in order to gain 2 pin that have been used for other purpose explained here after.

## Interrupts
In this project only internal interrupts have been used, precisely the timer interrupts. The UNO arduino board has three timers called Timer0, Timer1 and Timer2: the first two are 8-bit clocks while the last one is a 16 bit clock. In the project only two time interrupts are used : one for the print of the parameter on the serial monitor and on other to compare the pressure values in order to make the weather estimations. The first one has to allow the print operation every 4 seconds while the second one has to allow the comparation operations every one hour. Since the print operations are needed to be performed more often an 8 bit clock has been used while for the comparation operations the 16 bit clock has been used. In both case a prefactor is needed in the set up of the interrupts in order to reduce the frequency at which the clock increment a counter. After this operation two global variables have been used in order to reach the exact time in both cases. When the latter counter reaches the right value a flag has been set up and the relative part of the code is performed. Looking at the code is possible to see this at line 63-73/108-114 regarding the 4s interrupt and 76-87/117-124 regarding the 1h interrupt.

## DHT11
The DHT11 sensor has been used to calculate the humidity. Data consists of decimal and integral parts. A complete data transmission is 40bit, and the
sensor sends higher data bit first.
Data format: 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data + 8bit check sum. If the data transmission is right, the check-sum should be the last 8bit of "8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data".
Humidity sensing component has two electrodes with moisture holding substrate sandwiched between them.
The ions are released by the substrate as water vapor is absorbed by it, which in turn increases the conductivity between the electrodes.The change in resistance between the two electrodes is proportional to the relative humidity. Higher relative humidity decreases the resistance between the electrodes, while lower relative humidity increases the resistance between the electrodes.
The humidity sensor has been tested artificially in order to make the humidity change. Here it's possible to see a plot showing the change of humidity :

![Humidity plot](https://github.com/meft-sad/weather-station/blob/master/humPlot.jpg)

The digital interface used is a I2C interface: I2C is a serial communication protocol, so data is transferred bit by bit along a single wire. The time diagram of the entire communication is the following :

![Communication process](https://github.com/meft-sad/weather-station/blob/master/communication%20process.JPG)

## BMP280
The BMP280 has been used to calcluate the temperature and the atmosferic pressure. It has a pressure range of 300/1100 hPa and a temperature range of -40/80 °C. The BMP280 is based on Bosch’s proven Piezo-resistive pressure sensor technology featuring high EMC robustness, high accuracy and linearity and long term stability.
The BMP280 supports the I2C and SPI digital interfaces. Interface selection is done automatically based on CSB (chip select) status. If CSB is connected
to VDDIO, the I2C interface is active. In this project, since just SDA (data) and SCL (serial clock) the I2C digital interface is used.

## LED matrix
As already said the LED matrix has been used in order to show to the users the predicition about the weather. In case of good weather a sun is shown as in the following picture: 

![Sun](https://github.com/meft-sad/weather-station/blob/master/Sun.jpeg)

While, if the prediction is bad weather, a cloud is shown as in the following picture :

![Cloud](https://github.com/meft-sad/weather-station/blob/master/Cloud.jpeg).

## Conclusion
The target to predict in a rough way the weather has been achived but it's worth making some consideration. The model used to predict the weather is mainly based on the control of humidity as one of the most important parameter. This means that it could be used only in windy location in which it's very rare to have high humidity and sunny days in the same time. For example this model couldn't work at all if it would be used in north Italy. Moreover some improvements can be performed in order to develope the weather station leading to a better reilability. Firts of all, it could be possible to use the EEPROM of the Arduino board. This would make possible  saving data. With saved data the board can continue to work if it has been switched off for a little amount of time (maximum 3 hours). In order to achieve this improvement, also a real time clock is needed leading to a more complicated hardware used in the weather station. A further improvement could be the use of a more advanced board that could allow to have more avaible pins. In this way it could be possible also to use an LCD display to look after the real time parameters. Moreover, since more pins would be avaiable, it would be possible to use all the 8 columns of the LED matrix leading to a better draw of the outputs. At the end, the project has a limited range of work, both due to the very simple model used and the minimal hardware implemented.


