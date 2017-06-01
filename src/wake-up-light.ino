// Written by RedFantom for Red's Wake-Up Light
// Copyright (C) RedFantom 2017
// Available under the GNU GPLv3 license or any later version
// See LICENSE in the root of the repository for details

// Include the libraries used
#include <radio.h>
#include <Arduino.h>
#include <RDA5807M.h>
#include <Adafruit_Neopixel.h>
#include <PCF8574.h>
#include <RTClib.h>
#include <I2C_eeprom.h>

// Constant values for use throughout the project
#define ledRingCount 12
// define the pin numbers used for each component connected to the Arduino
#define ledRingPin 3
#define ledBrightPin 5
#define displayDataPin 3
#define displayClockPin 2
#define lightSensorPin A0
// define the pin numbers used for each component connected to the IO Expander
const uint8_t radioToggle = 0;
const uint8_t radioVolumeUp = 1;
const uint8_t radioVolumeDown = 2;
const uint8_t radioChannelUp = 3;
const uint8_t radioChannelDown = 4;
const uint8_t lampToggle = 5;
const uint8_t lampBrightnessUp = 6;
const uint8_t lampBrightnessDown = 7;
// define addresses for different I2C modules
/* i2c_scanner found the addresses:
 * 0x10 -> RDA5807M
 * 0x11 -> RDA5807M
 * 0x20
 * 0x57
 * 0x60 -> RDA5807M in TEA5767 radio module
 * 0x68
*/
#define ioExpanderAddress 0x38
#define radioAddress 0x10
#define clockAddress 0x57
#define eepromAddress 0x50


// Objects to control the different I2C Modules
RDA5807M radio;
PCF8574 ioExpander(ioExpanderAddress);
RTC_DS3231 clock;
I2C_eeprom storage(eepromAddress, 0x8000);
// Radio variables
uint8_t radioVolume = 4;
bool radioMute = false;
bool radioMono = false;
// Lamp variables
uint8_t lampBrightness = 0;
bool lampEnabled = false;
uint8_t redBrightness = 0;
uint8_t greenBrightness = 0;
uint8_t blueBrightness = 0;
// Display variables
uint8_t displayBrightness = 15;
bool displayEnabled = true;
bool showRadioVolume = false;
bool showRadioChannel = false;
bool showLampBrightness = false;
bool flashColon = false;
// Time handling variables
uint8_t alarmOneMinute;
uint8_t alarmOneHour;
uint8_t alarmTwoMinute;
uint8_t alarmTwoHour;
DateTime currentTime;


// Functions to execute when the buttons to control the radio are pressed
void buttonRadioToggle(){
  // Toggles the radio mute, turning it on when it's off and off when it's on
  radioMute != radioMute;
  radio.setMute(radioMute);
}

void buttonRadioSeekUp(){
  // Makes the radio module look for a new channel upwards from the current
  // channel
  radio.seekUp();
  // TODO: Show channel
}

void buttonRadioSeekDown(){
  // Makes the radio module look for a new channel downwards from the current
  // channel
  radio.seekDown();
  // TODO: Show channel
}

uint8_t buttonRadioVolumeUp(){
  // Increases the radio volume
  radioVolume++;
  radio.setVolume(radioVolume);
  // TODO: Show radio volume
  return radioVolume;
}

uint8_t buttonRadioVolumeDown(){
  // Decreases the radio volume
  radioVolume--;
  radio.setVolume(radioVolume);
  // TODO: Show radio volume
  return radioVolume;
}

// Functions to be executed in the loop
void setBrightness(){
  // Change the brightness of the display in accordance with the environment
  uint8_t value = analogRead(lightSensorPin);
  // TODO: Convert the read value to an appropriate brightness level

}

// Functions for the buttons for the lamp
void buttonLampToggle(){
  lampEnabled != lampEnabled;
  updateLampBrightness();
}

void buttonLampBrightnessUp(){
  lampBrightness++;
  updateLampBrightness();
}

void buttonLampBrightnessDown(){
  lampBrightness--;
  updateLampBrightness();
}

void updateLampBrightness(){
  if(lampEnabled){
    analogWrite(ledBrightPin, lampBrightness * 12);
  }
}

void lostPower(){
  // TODO: Function to run after the clock has lost power and needs to be reset
}

// Functions for the display
void displayTime(){
  Serial.println("displayTime called");
  write_time(currentTime.hour(), currentTime.minute());
}

// Normal Arduino functions
void setup(){
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Starting activities");
  radio.init();
  Serial.println("Radio initialized");
  radio.setBandFrequency(RADIO_BAND_FM, 9180);
  Serial.println("Frequency set");
  radio.setVolume(15);
  radio.setMono(radioMono);
  radio.setMute(radioMute);
  if(clock.lostPower()){
    lostPower();
  }
  setup_display();

}

void loop(){
  currentTime = clock.now();
  displayTime();
  setBrightness();
}
