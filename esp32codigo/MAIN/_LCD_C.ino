#include <ItemSubMenu.h>
#include <LcdMenu.h>
#include <ItemList.h>
#include <display/LiquidCrystal_I2CAdapter.h>
#include <SimpleRotary.h>
#include <input/SimpleRotaryAdapter.h>
#include <renderer/CharacterDisplayRenderer.h>
#include <ItemInputCharset.h>
#include <ItemCommand.h>

extern MenuScreen* SDScreen;
extern MenuScreen* INFOScreen;
extern MenuScreen* WIFIScreen;
extern MenuScreen* ConfScreen;
extern MenuScreen* SDserScreen;
extern MenuScreen* WifiCfgScreen;



MENU_SCREEN(mainScreen, mainItems,
            ITEM_SUBMENU("Agujerear desde:", SDScreen),
            ITEM_SUBMENU("Monitoreo", INFOScreen),
            ITEM_SUBMENU("WiFi", WifiCfgScreen),
            ITEM_SUBMENU("Configuración", ConfScreen));

MENU_SCREEN(SDserScreen, SDserItems,
            ITEM_BASIC("WiFi Conectado"),
            ITEM_BACK());

MENU_SCREEN(SDScreen, SDItems,
            ITEM_SUBMENU("Locales", SDlocScreen),
            ITEM_SUBMENU("Servidor", SDserScreen),
            ITEM_BACK());
MENU_SCREEN(INFOScreen, INFOItems,
            ITEM_BASIC("Coords:"),
            ITEM_BASIC("Espacio libre en SD:"),
            ITEM_BACK()
           );
MENU_SCREEN(WifiCfgScreen, WifiCfgItems,
            ITEM_SUBMENU("Networks", WifiScanScreen),
            ITEM_INPUT_CHARSET("Pass", (char*) "0123456789abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ{}[]()=!¡?¿´+-.,<>", [](char* value) {
              password = value;
              }),
            ITEM_COMMAND("Conectar", []() {
              wifibegin(ssid, password);
            }),
            ITEM_BACK()
           );
MENU_SCREEN(ConfScreen, ConfItems,
            ITEM_BASIC("aaaConfg:"),
            ITEM_BACK()
           );
           
//RECORDATORIO: En los docs de la libreria esta el ejemplo de RTOS, en una parte se ve como mostrar variables :)
LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);
CharacterDisplayRenderer renderer(new LiquidCrystal_I2CAdapter(&lcd), LCD_COLS, LCD_ROWS);
LcdMenu menu(renderer);
SimpleRotary encoder(26, 25, 27);
SimpleRotaryAdapter rotaryInput(&menu, &encoder);

void LCDSetup() {
  renderer.begin();
  menu.setScreen(mainScreen);
}
void LCDLoop() {
  rotaryInput.observe();
}


void inputCallback(char* value) {
  // do something with the input value
  Serial.println(value);
}
