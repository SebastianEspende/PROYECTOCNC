
//LCD
#include <Wire.h>

//SD

#include "FS.h"
#include "SD.h"
#include "SPI.h"

void setup() {

  Serial.begin(115200);

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
  // QUE HAY Q HACER:
  // SD Y LCD
  /* SD: HAY QUE ACTIVAR EL WIFI, CONECTARSE AL SERVIDOR Y TRAER LOS NOMBRES DE TODOS LOS ARCHIVOS GUARDADOS. PODER SELECCIONAR UNO Y DESCARGARLO.
     WIFI: GET DEL SERVIDOR, CONECTARSE AL INTERNET, CONECTARSE A LA API
     LCD: MOSTRAR LOS NOMBRES DE LOS ARCHIVOS EN EL SERVIDOR , CONTROLAR LOS VENTILADORES
     - INFO
      - SD ESPACIO Y VARIOS
      - COORDENADAS
     - CONFIG?
  */
  //LCD
  LCDLoop();
  // WIFI
  wifiloop();
}
