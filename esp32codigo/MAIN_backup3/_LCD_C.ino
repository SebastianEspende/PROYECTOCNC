#include <LcdMenu.h>
#include <ItemList.h>
#include <display/LiquidCrystal_I2CAdapter.h>
#include <SimpleRotary.h>
#include <input/SimpleRotaryAdapter.h>
#include <renderer/CharacterDisplayRenderer.h>

extern MenuScreen* SDScreen;
extern MenuScreen* INFOScreen;
extern MenuScreen* WIFIScreen;
extern MenuScreen* ConfScreen;
extern MenuScreen* SDserScreen;
//extern MenuScreen* SDlocScreen;
extern const char *ssid;

MENU_SCREEN(mainScreen, mainItems,
            ITEM_SUBMENU("Agujerear desde:", SDScreen),
            ITEM_SUBMENU("Monitoreo", INFOScreen),
            ITEM_SUBMENU("WiFi", WIFIScreen),
            ITEM_SUBMENU("Configuración", ConfScreen));

// Create submenu and precise its parent


MENU_SCREEN(SDScreen, SDItems,
            ITEM_SUBMENU("Locales", SDlocScreen),
            ITEM_SUBMENU("Servidor", SDserScreen),
            ITEM_BACK());
MENU_SCREEN(SDserScreen, SDserItems,
            ITEM_BASIC("WiFi Conectado"),
            ITEM_BACK());

MENU_SCREEN(INFOScreen, INFOItems,
            ITEM_BASIC("Coords:"),
            ITEM_BASIC("Espacio libre en SD:"),
            ITEM_BACK()
           );
MENU_SCREEN(WIFIScreen, WIFIItems,
            ITEM_BASIC("Actualemente conectado a:"),
            ITEM_BASIC(ssid),
            ITEM_BACK()
           );
/*MENU_SCREEN(WifiCfgScreen, WifiCfgItems,
            ITEM_STRING_LIST("List 1", ssidPointers, nSSID, [](uint8_t index) {
              ssid = ssidPointers[index].c_str();
              }),
            ITEM_COMMAND("Item 1", []() {
              wifibegin(ssid, password);
            }),
            ITEM_BACK()
           );*/
MENU_SCREEN(ConfScreen, ConfItems,
            ITEM_BASIC("Todos los archivos:"),
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
