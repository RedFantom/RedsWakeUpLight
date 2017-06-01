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
#include <TM1637Display.h>
#include <RTClib.h>
#include <I2C_eeprom.h>

// Constant values for use throughout the project
const byte ledRingCount = 12;
// Define the pin numbers used for each component connected to the Arduino
const byte ledRingPin = 3;
const byte ledBrightPin = 5;
const byte displayDataPin = 13;
const byte displayClockPin = 12;
const byte lightSensorPin = A0;
// Define the pin numbers used for each component connected to the IO Expander
const byte radioToggle = 0;
const byte radioVolumeUp = 1;
const byte radioVolumeDown = 2;
const byte radioChannelUp = 3;
const byte radioChannelDown = 4;
const byte lampToggle = 5;
const byte lampBrightnessUp = 6;
const byte lampBrightnessDown = 7;
// Define addresses for different I2C modules
byte ioExpanderAddress = 0x38;
byte radioAddress = 0x10;  // Currently not used
byte clockAddress = 0x00;  // TODO: Determine I2C Address
byte eepromAddress = 0x50;

// Objects to control the different I2C Modules
RDA5807M radio;
PCF8574 ioExpander(ioExpanderAddress);
TM1637Display display(displayDataPin, displayClockPin);
RTC_DS3231 clock;
I2C_eeprom storage(eepromAddress, 0x8000);
// Radio variables
byte radioVolume = 4;
bool radioMute = false;
bool radioMono = false;
// Lamp variables
byte lampBrightness = 0;
bool lampEnabled = false;
byte redBrightness = 0;
byte greenBrightness = 0;
byte blueBrightness = 0;
byte lampBrightnessByte = 0;
// EEPROM Data addresses
// TODO Implement Wear levelling to improve EEPROM life expectancy
const byte alarmOneMinuteAddress = 0x00;
const byte alarmOneHourAddress = 0x01;
const byte alarmTwoMinuteAddress = 0x02;
const byte alarmTwoHourAddress = 0x03;
const byte alarmOneRadioChannel = 0x04; // This takes up two bytes
const byte alarmTwoRadioChannel = 0x06; // This takes up two bytes
const byte alarmOneLampBrightness = 0x08;
const byte alarmTwoLampBrightness = 0x09;
const byte alarmOneRadioVolume = 0x10;
const byte alarmTwoRadioVolume = 0x011;
// Display variables
byte displayBrightness = 7;
bool displayEnabled = true;
bool showRadioVolume = false;
bool showRadioChannel = false;
bool showLampBrightness = false;
bool flashColon = false;
// Time handling variables
byte alarmOneMinute;
byte alarmOneHour;
byte alarmTwoMinute;
byte alarmTwoHour;
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

byte buttonRadioVolumeUp(){
  // Increases the radio volume
  radioVolume++;
  radio.setVolume(radioVolume);
  // TODO: Show radio volume
  return radioVolume;
}

byte buttonRadioVolumeDown(){
  // Decreases the radio volume
  radioVolume--;
  radio.setVolume(radioVolume);
  // TODO: Show radio volume
  return radioVolume;
}

// Functions to be executed in the loop
void setBrightness(){
  // Change the brightness of the display in accordance with the environment
  byte value = analogRead(lightSensorPin);
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

// Functions for the EEPROM chip
void readEEPROMData(){

}

// Functions for the display
void displayTime(){
  int number = currentTime.hour() * 100 + currentTime.minute();
  display.showNumberDecEx(number, 1, true);
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
  display.setBrightness(displayBrightness, displayEnabled);
  if(clock.lostPower()){
    lostPower();
  }
  display.showNumberDecEx(5000);
}

void loop(){
  currentTime = clock.now();
  displayTime();
  setBrightness();
}
