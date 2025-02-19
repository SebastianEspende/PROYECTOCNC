 
//LCD
#include <Wire.h>

//SD

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "globales.h"

void wifibegin(const char *ssid,const char *password);
void setup() {

  
  Serial.printf("COM_SERIAL_SETUP");
  COM_SERIAL_SETUP();
  while (!Serial) {
    delay(10);
  }

  // SD ////////////////////////////////////////////////////////
  Serial.printf("sdsetup");
  sdsetup();
  // WIFI ///////////////////////////////////////////////////////////////////////////
  Serial.printf("wifisetup");
  wifisetup();

  //LCD /////////////////////////////////////////////////////////////////////
  Serial.printf("lcdsetup");
  LCDSetup();
}

void loop() {

  //LCD
  Serial.printf("lcdloop");
  LCDLoop();
  // WIFI
  Serial.printf("wifiloop");
  wifiloop();

  COM_SERIAL_LOOP();
}
