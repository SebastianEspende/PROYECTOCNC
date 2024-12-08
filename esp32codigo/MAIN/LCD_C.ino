#include <ItemSubMenu.h>
#include <LcdMenu.h>
#include <ItemList.h>
#include <MenuScreen.h>
#include <ItemBack.h>
#include <display/LiquidCrystal_I2CAdapter.h>
#include <SimpleRotary.h>
#include <input/SimpleRotaryAdapter.h>
#include <renderer/CharacterDisplayRenderer.h>
#define LCD_ROWS 2
#define LCD_COLS 16

extern MenuScreen* SDScreen;
extern MenuScreen* INFOScreen;
extern MenuScreen* WIFIScreen;
extern MenuScreen* configScreen;
extern MenuScreen* SDserScreen;
extern MenuScreen* SDlocScreen;
extern String* Files;
extern std::vector<std::string> all_local_files;
extern const char *ssid;
void arclocselec(uint8_t pos);

MENU_SCREEN(mainScreen, mainItems,
            ITEM_SUBMENU("Settings", SDScreen));

// Create submenu and precise its parent
MENU_SCREEN(SDScreen, SDItems,
            ITEM_SUBMENU("Locales", SDlocScreen),
            ITEM_SUBMENU("Servidor", SDserScreen),
            ITEM_BACK());

MENU_SCREEN(SDlocScreen, SDlocItems,
            ITEM_BASIC("Archivos Locales"),
            ITEM_STRING_LIST("ARCH", Files, all_local_files.size(), arclocselec),
            ITEM_BACK());
MENU_SCREEN(SDserScreen, SDserItems,
            ITEM_BASIC("A"),
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
MENU_SCREEN(configScreen, configItems,
            ITEM_BASIC("Todos los archivos:"),
            ITEM_BACK()
           );
//RECORDATORIO: En los docs de la libreria esta el ejemplo de RTOS, en una parte se ve como mostrar variables :)
LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);
CharacterDisplayRenderer renderer(new LiquidCrystal_I2CAdapter(&lcd), LCD_COLS, LCD_ROWS);
LcdMenu menu(renderer);
SimpleRotary encoder(2, 3, 4);
SimpleRotaryAdapter rotaryInput(&menu, &encoder);

void LCDSetup() {
  renderer.begin();
  menu.setScreen(mainScreen);
}
void LCDLoop() {
  rotaryInput.observe();
}
void arclocselec(uint8_t pos) {
  String NombreArchivo = Files[pos];
  
}
