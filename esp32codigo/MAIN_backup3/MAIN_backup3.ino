 
//LCD
#include <Wire.h>

//SD

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "globales.h"

void setup() {

  
  COM_SERIAL_SETUP();
  while (!Serial) {
    delay(10);
  }

  // SD ////////////////////////////////////////////////////////
  sdsetup();
  // WIFI ///////////////////////////////////////////////////////////////////////////
  wifisetup();

  //LCD /////////////////////////////////////////////////////////////////////
  LCDSetup();
}

void loop() {

  //LCD
  LCDLoop();
  // WIFI
  wifiloop();

  COM_SERIAL_LOOP();
}
