// Written by RedFantom for Red's Wake-Up Light
// Copyright (C) RedFantom 2017
// Available under the GNU GPLv3 license or any later version
// See LICENSE in the root of the repository for details

// EEPROM Data addresses
// TODO Implement Wear levelling to improve EEPROM life expectancy
const uint8_t alarmOneMinuteAddress = 0x00;
const uint8_t alarmOneHourAddress = 0x01;
const uint8_t alarmTwoMinuteAddress = 0x02;
const uint8_t alarmTwoHourAddress = 0x03;
const uint8_t alarmOneRadioChannel = 0x04; // This takes up two uint8_ts
const uint8_t alarmTwoRadioChannel = 0x06; // This takes up two uint8_ts
const uint8_t alarmOneLampBrightness = 0x08;
const uint8_t alarmTwoLampBrightness = 0x09;
const uint8_t alarmOneRadioVolume = 0x10;
const uint8_t alarmTwoRadioVolume = 0x011;

I2C_eeprom storage(eepromAddress, 0x8000);


// Functions for the EEPROM chip
void readEEPROMData(){

}
