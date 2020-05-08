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
