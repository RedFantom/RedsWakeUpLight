// Written by RedFantom for Red's Wake-Up Light
// Copyright (C) RedFantom 2017
// Available under the GNU GPLv3 license or any later version
// See LICENSE in the root of the repository for details
#include <Arduino.h>
// Based upon this GitHub repository: https://github.com/moozzyk/TM1637Clock

#ifndef displayDataPin
  #define displayDataPin 13
#endif
#ifndef displayClockPin
  #define displayClockPin 12
#endif

byte tcnt2;


bool writeValue(uint8_t value){
  for(uint8_t i = 0; i < 8; i++){
    digitalWrite(displayClockPin, LOW);
    delayMicroseconds(5);
    digitalWrite(displayDataPin, (value & (1 << i)) >> i);
    delayMicroseconds(5);
    digitalWrite(displayClockPin, HIGH);
    delayMicroseconds(5);
  }
  // wait for ACK
  digitalWrite(displayClockPin, LOW);
  delayMicroseconds(5);
  pinMode(displayDataPin, INPUT);
  digitalWrite(displayClockPin, HIGH);
  delayMicroseconds(5);
  bool ack = digitalRead(displayDataPin) == 0;
  pinMode(displayDataPin, OUTPUT);
  return ack;
}


void start(void){
  digitalWrite(displayClockPin, HIGH);//send start signal to TM1637
  digitalWrite(displayDataPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(displayDataPin, LOW);
  digitalWrite(displayClockPin, LOW);
  delayMicroseconds(5);
}

void stop(void){
  digitalWrite(displayClockPin, LOW);
  digitalWrite(displayDataPin, LOW);
  delayMicroseconds(5);
  digitalWrite(displayClockPin, HIGH);
  digitalWrite(displayDataPin, HIGH);
  delayMicroseconds(5);
}


void write(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth){
  start();
  writeValue(0x40);
  stop();
  start();
  writeValue(0xc0);
  writeValue(first);
  writeValue(second);
  writeValue(third);
  writeValue(fourth);
  stop();
}


void setupInterrupt(){
  // Credits for the interrupt setup routine:
  // http://popdevelop.com/2010/04/mastering-timer-interrupts-on-the-arduino/
  // First disable the timer overflow interrupt while we're configuring
  TIMSK2 &= ~(1<<TOIE2);
  // Configure timer2 in normal mode (pure counting, no PWM etc.)
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
  // Select clock source: internal I/O clock
  ASSR &= ~(1<<AS2);
  // Disable Compare Match A interrupt enable (only want overflow)
  TIMSK2 &= ~(1<<OCIE2A);
  // Now configure the prescaler to CPU clock divided by 128
  TCCR2B |= (1<<CS22)  | (1<<CS20); // Set bits
  TCCR2B &= ~(1<<CS21);             // Clear bit
  /* We need to calculate a proper value to load the timer counter.
   * The following loads the value 131 into the Timer 2 counter register
   * The math behind this is:
   * (CPU frequency) / (prescaler value) = 125000 Hz = 8us.
   * (desired period) / 8us = 125.
   * MAX(uint8) + 1 - 125 = 131;
   */
  // Save value globally for later reload in ISR
  tcnt2 = 131;
  // Finally load end enable the timer
  TCNT2 = tcnt2;
  TIMSK2 |= (1<<TOIE2);
}


void setup_display(){
  setupInterrupt();
  pinMode(displayClockPin, OUTPUT);
  pinMode(displayDataPin, OUTPUT);
  start();
  writeValue(0x8c);
  stop();
  // clear display
  write(0x00, 0x00, 0x00, 0x00);
}

void write_time(uint8_t hour, uint8_t minute){
  uint8_t first = hour / 10;
  uint8_t second = hour % 10;
  uint8_t third = minute / 10;
  uint8_t fourth = minute % 10;
  write(first, second, third, fourth);
}
