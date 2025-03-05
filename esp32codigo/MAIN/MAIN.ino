//LCD
#include <Wire.h>

//SD
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "globales.h"

void setup() {
  // Inicializar comunicación serial
  COM_SERIAL_SETUP();
  while (!Serial) {
    delay(10);
  }

  // Inicializar tarjeta SD
  sdsetup();
  
  // Inicializar WiFi
  wifisetup();

  // Inicializar LCD
  LCDSetup();
}

void loop() {
  // Actualizar la pantalla LCD
  LCDLoop();
  
  // Actualizar el estado del WiFi
  wifiloop();

  // Manejar la comunicación serial
  COM_SERIAL_LOOP();
}