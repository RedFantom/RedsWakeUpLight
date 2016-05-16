#include <DS3231.h>                         // See http://www.rinkydinkelectronics.com/library.php?id=73
#include <Adafruit_NeoPixel.h>              // See https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library

DS3231  rtc(SDA, SCL);
Time currentTime;
Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(12, 11, NEO_GRB + NEO_KHZ800);

int intensity = 1;
int red = 0;
int green = 0;
int blue = 0;

void setup(){
  Serial.begin(9600);
  rtc.begin();
  neopixel.begin();
  Serial.println("setup() completed");
}

void loop(){
  currentTime = rtc.getTime();
  Serial.print("The current hour is: ");
  Serial.println(currentTime.hour);
  if(currentTime.hour == 06 && currentTime.min == 15){
    Serial.println("Wake-Up cycle started");
    while(intensity < 256){
      red = intensity;
      green = intensity - 43;
      blue = intensity - 172;
      if(green < 0){
        green = 0;
      }
      if(blue < 0){
        blue = 0;
      }
      for(int i = 0; i < 12; i++){
        neopixel.setPixelColor(i, red, green, blue);
      }
      neopixel.show();
      intensity++;
      Serial.println("Intensity increased.");
      delay(7000);
    }
    Serial.println("Wake-Up cycle finished");
    delay(600000);
    Serial.println("Turning off LED's");
    for(int j = 0; j < 12; j++){
      neopixel.setPixelColor(j, 0, 0, 0);
    }
    Serial.println("Cycle will restart tomorrow");
  }
  delay(1000);

}
