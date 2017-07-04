# Libraries
This project depends on various libraries. All libraries are available through the PlatformIO IDE Platform built upon
Atom. If you run on Windows, you can also use an improved installer written by me, that you can find
[here](https://www.github.com/RedFantom/atom-windows-installer/releases). This project depends on the following
libraries:

- Radio
  A library to control the RDA5807M radio module
- DS3231
  As the name suggests, this library is for controlling the DS3231 RTC module
- Adafruit Neopixel
  This library is to control the WS2812B RGB LEDs. This library also works with non-Adafruit modules.
- I2C_EEPROM
  This library is to control the EEPROM modules (both the one on the clock if required and the dedicated EEPROM)
- PCF8574
  This is the library to control the PCF8574 IO-expander chip

All these libraries are available through the PlatfomIO libraries system
