#include <ItemSubMenu.h>
#include <ItemList.h>
#include <SimpleRotary.h>
#include <input/SimpleRotaryAdapter.h>
#include <ItemInputCharset.h>
#include <ItemCommand.h>
#include <ItemValue.h>

// Declaración de pantallas externas
extern MenuScreen* SDScreen;
extern MenuScreen* INFOScreen;
extern MenuScreen* WIFIScreen;
extern MenuScreen* ConfScreen;
extern MenuScreen* SDserScreen;
extern MenuScreen* MOVEScreen;
extern MenuScreen* MOVEXScreen;
extern MenuScreen* MOVEYScreen;
extern MenuScreen* MOVEZScreen;
extern MenuScreen* MOVESPNScreen;

float XC = 0.0;
float YC = 0.0;
float ZC = 0.0;

           
// RECORDATORIO: En los docs de la librería está el ejemplo de RTOS, en una parte se ve cómo mostrar variables 

// Configuración del encoder rotatorio para navegar por los menús
SimpleRotary encoder(26, 25, 27);
SimpleRotaryAdapter rotaryInput(&menu, &encoder);


void DatosPosicion() {

  if (arduinoSerial.available() > 0) {
    String grblLine = arduinoSerial.readStringUntil('\n');
    grblLine.trim(); 
    int inicioPosW = grblLine.indexOf("WPos:");
    if (inicioPosW > 0) {
    int posFin = grblLine.indexOf(',', inicioPosW);
    if (posFin < 0) posFin = grblLine.indexOf('>', inicioPosW);
    if (posFin < 0) return; // Error en formato
    
    String datosPosicion = grblLine.substring(inicioPosW, posFin);
    
    // Dividir por comas
    int primeraComa = datosPosicion.indexOf(',');
    int segundaComa = datosPosicion.indexOf(',', primeraComa + 1);
    
    if (primeraComa > 0 && segundaComa > 0) {
      XC = datosPosicion.substring(0, primeraComa).toFloat();
      YC = datosPosicion.substring(primeraComa + 1, segundaComa).toFloat();
      ZC = datosPosicion.substring(segundaComa + 1).toFloat();
    }
  }
    
  }
}

// Definición de la pantalla principal y sus elementos
MENU_SCREEN(mainScreen, mainItems,
            ITEM_SUBMENU("Agujerear desde:", SDScreen),
            ITEM_SUBMENU("Monitoreo", INFOScreen),
            ITEM_SUBMENU("Movimiento", MOVEScreen),
            ITEM_SUBMENU("WiFi", WifiCfgScreen),
            ITEM_SUBMENU("Configuración", ConfScreen));

// Pantalla de servidor SD
MENU_SCREEN(SDserScreen, SDserItems,
            ITEM_BASIC("WiFi Conectado"),
            ITEM_BACK());

// Pantalla de selección de origen SD
MENU_SCREEN(SDScreen, SDItems,
            ITEM_SUBMENU("Locales", SDlocScreen),
            ITEM_SUBMENU("Servidor", SDserScreen),
            ITEM_BACK());

// Pantalla de información y monitoreo
MENU_SCREEN(INFOScreen, INFOItems,
            ITEM_VALUE("X: ", XC, "%f"), 
            ITEM_VALUE("Y: ", YC, "%f"),
            ITEM_VALUE("Z: ", ZC, "%f"),
            ITEM_BACK()
           );
MENU_SCREEN(MOVEScreen, MOVEItems,
            ITEM_SUBMENU("X", MOVEXScreen), 
            ITEM_SUBMENU("Y", MOVEYScreen),
            ITEM_SUBMENU("Z", MOVEZScreen),
            ITEM_SUBMENU("SPINDLE", MOVESPNScreen),
            ITEM_BACK()
           );
MENU_SCREEN(MOVEXScreen, MOVEXItems,
            ITEM_COMMAND("10mm", []() {
    arduinoSerial.println("G91 G0 X10");
}),
            ITEM_COMMAND("1mm", []() {
    arduinoSerial.println("G91 G0 X1");
}),
            ITEM_COMMAND("0.1mm", []() {
    arduinoSerial.println("G91 G0 X0.1");
}),
            ITEM_COMMAND("-10mm", []() {
    arduinoSerial.println("G91 G0 X-10");
}),
            ITEM_COMMAND("-1mm", []() {
    arduinoSerial.println("G91 G0 X-1");
}),
            ITEM_COMMAND("-0.1mm", []() {
    arduinoSerial.println("G91 G0 X-0.1");
}),
            ITEM_BACK()
           );

MENU_SCREEN(MOVEYScreen, MOVEYItems,
            ITEM_COMMAND("10mm", []() {
    arduinoSerial.println("G91 G0 Y10");
}),
            ITEM_COMMAND("1mm", []() {
    arduinoSerial.println("G91 G0 Y1");
}),
            ITEM_COMMAND("0.1mm", []() {
    arduinoSerial.println("G91 G0 Y0.1");
}),
            ITEM_COMMAND("-10mm", []() {
    arduinoSerial.println("G91 G0 Y-10");
}),
            ITEM_COMMAND("-1mm", []() {
    arduinoSerial.println("G91 G0 Y-1");
}),
            ITEM_COMMAND("-0.1mm", []() {
    arduinoSerial.println("G91 G0 Y-0.1");
}),
            ITEM_BACK()
           );

MENU_SCREEN(MOVEZScreen, MOVEZItems,
            ITEM_COMMAND("10mm", []() {
    arduinoSerial.println("G91 G0 Z10");
}),
            ITEM_COMMAND("1mm", []() {
    arduinoSerial.println("G91 G0 Z1");
}),
            ITEM_COMMAND("0.1mm", []() {
    arduinoSerial.println("G91 G0 Z0.1");
}),
            ITEM_COMMAND("-10mm", []() {
    arduinoSerial.println("G91 G0 Z-10");
}),
            ITEM_COMMAND("-1mm", []() {
    arduinoSerial.println("G91 G0 Z-1");
}),
            ITEM_COMMAND("-0.1mm", []() {
    arduinoSerial.println("G91 G0 Z-0.1");
}),
            ITEM_BACK());

MENU_SCREEN(MOVESPNScreen, MOVESPNItems,
            ITEM_COMMAND("Horario", []() {
    arduinoSerial.println("M3 S1000");
}),
ITEM_COMMAND("Horario", []() {
    arduinoSerial.println("M4 S1000");
}),
            ITEM_BACK());

// Pantalla de configuración WiFi
MENU_SCREEN(WifiCfgScreen, WifiCfgItems,
            ITEM_SUBMENU("Networks", WifiScanScreen),
            ITEM_INPUT_CHARSET("Pass", (char*) "0123456789abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ{}[]()=!¡?¿´+-.,<>", [](char* value) {
              password = value;
              }),
            ITEM_COMMAND("Conectar", []() {
              wifistart(ssid, password);
            }),
            ITEM_BACK()
           );

// Pantalla de configuración general
MENU_SCREEN(ConfScreen, ConfItems,
            ITEM_BASIC("aaaConfg:"),
            ITEM_BACK()
           );

           
// Inicializa la pantalla LCD
void LCDSetup() {
  renderer.begin();
  menu.setScreen(mainScreen);
}

// Función de loop para la pantalla LCD
void LCDLoop() {
  rotaryInput.observe();
  menu.poll(1000);
}
