// Written by RedFantom for Red's Wake-Up Light
// Copyright (C) RedFantom 2017
// Available under the GNU GPLv3 license or any later version
// See LICENSE in the root of the repository for details

// define the pin numbers used for each component connected to the IO Expander
#define radioTogglePin 0
#define radioVolumeUpPin 1
const uint8_t radioVolumeDown = 2;
const uint8_t radioChannelUp = 3;
const uint8_t radioChannelDown = 4;
const uint8_t lampToggle = 5;
const uint8_t lampBrightnessUp = 6;
const uint8_t lampBrightnessDown = 7;

// Functions to execute when the buttons to control the radio are pressed
void buttonRadioToggle(){
  Serial.println("buttonRadioToggle called");
  // Toggles the radio mute, turning it on when it's off and off when it's on
  radioMute != radioMute;
  radio.setMute(radioMute);
}

void buttonRadioSeekUp(){
  Serial.println("buttonRadioSeekUp called");
  // Makes the radio module look for a new channel upwards from the current
  // channel
  radio.seekUp();
  // TODO: Show channel
}

void buttonRadioSeekDown(){
  Serial.println("buttonRadioSeekDown called");
  // Makes the radio module look for a new channel downwards from the current
  // channel
  radio.seekDown();
  // TODO: Show channel
}

uint8_t buttonRadioVolumeUp(){
  Serial.println("buttonRadioVolumeUp called");
  // Increases the radio volume
  radioVolume++;
  radio.setVolume(radioVolume);
  // TODO: Show radio volume
  return radioVolume;
}

uint8_t buttonRadioVolumeDown(){
  Serial.println("buttonRadioVolumeDown called");
  // Decreases the radio volume
  radioVolume--;
  radio.setVolume(radioVolume);
  // TODO: Show radio volume
  return radioVolume;
}
