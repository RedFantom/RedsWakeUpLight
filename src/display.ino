// Written by RedFantom for Red's Wake-Up Light
// Copyright (C) RedFantom 2017
// Available under the GNU GPLv3 license or any later version
// See LICENSE in the root of the repository for details
#include <Arduino.h>

TM1637Display display(displayClockPin, displayDataPin);

void display_set_time(uint8_t hour, uint8_t minute){
  uint16_t number = 100 * hour + minute;
  display.showNumberDecEx(number, 2, true);
}

void display_set_brightness(uint8_t brightness){
  display.setBrightness(brightness, displayEnabled);
}

void display_set_number(uint16_t number){
  display.showNumberDec(number);
}
