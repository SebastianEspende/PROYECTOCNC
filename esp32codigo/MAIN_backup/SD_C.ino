#include <ItemCommand.h>
#include <MenuItem.h>
#include <ItemBack.h>
#include <MenuScreen.h>
#include <ItemSubMenu.h>
#include <FileMenuItem.h>
int counter = 0;
bool SD0 = false;
String Files[MAX_FILES];
void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  //Monitor.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    //Monitor.println("No se pudo abrir la ruta");
    return;
  }
  if (!root.isDirectory()) {
    //Monitor.println("No es una ruta valida");
    return;
  }
  if (counter > 50) {
    //Monitor.println("El numero de archivos es mayor al maximo");
    return;
    }
  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      //Monitor.print("  DIR : ");
      //Monitor.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      //Monitor.print("  ARCHIVO: ");
      //Monitor.print(file.name());
      //Monitor.print("  TAMAÑO: ");
      //Monitor.println(file.size());
      Files[counter] = String(file.name());
      counter++;
    }
    file = root.openNextFile();
  }
}


void readFile(fs::FS &fs, const char *path) {
  //Monitor.printf("Leyendo archivo: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    //Monitor.println("No se pudo abrir el archivo");
    return;
  }

  while (file.available()) {
  //Monitor.print("Leyendo el archivo: ");
  //Monitor.print(file.name());
  //Monitor.print("\n");
    //Monitor.write(file.read());
  }
  file.close();
}

void sdsetup() {
  if (!SD.begin()) {
    //Monitor.println("No se pudo inicializar la tarjeta SD");
    SD0 = true;
    return;
  } else {
    SD.begin();
  }
  uint8_t cardType = SD.cardType();
 
  if (cardType == CARD_NONE) {
    //Monitor.println("No hay tarjeta SD");
    return;
  }

  //Monitor.print("Tipo de tarjeta: ");
  if (cardType == CARD_MMC) {
    //Monitor.println("MMC");
  } else if (cardType == CARD_SD) {
    //Monitor.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    //Monitor.println("SDHC");
  } else {
    //Monitor.println("DESCONOCIDA");
  }
  listDir(SD, "/", 0);
  buildSDlocScreen();
  
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  //Monitor.printf("TAMAÑO DE SD: %lluMB\n", cardSize);

  //Monitor.printf("Espacio total: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  //Monitor.printf("Espacio usado: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}



char selectedFilename[256];
#include <functional> // For std::function
#include <string>   // For std::string
#include <cstring>  // For strdup
MenuScreen *SDlocScreen = nullptr;
MenuItem *SDlocItems[MAX_FILES + 2]; // +2 for header and back item

// Function to read a line from a file (you'll need to implement this)
String readLine(File& file) {
    String line = "";
    while (file.available()) {
        char c = file.read();
        if (c == '\n' || c == '\r') break; // Stop at newline or carriage return
        line += c;
    }
    return line;
}

String fileNames[MAX_FILES]; // For filename lifetime management


void buildSDlocScreen() {
  //Monitor.println("Building Local Files Screen...");
    if (SDlocScreen != nullptr) {
        delete SDlocScreen;
        SDlocScreen = nullptr;  // Important: Set to nullptr after deleting
    }

    for (int i = 0; i < MAX_FILES + 2; i++) { // Clear the SDlocItems array
      SDlocItems[i] = nullptr;
    }
    
    int menuIndex = 0;

    SDlocItems[menuIndex++] = new MenuItem("Archivos Locales");

    for (int i = 0; i < counter && i < 50; i++) {
        if (Files[i].length() > 0) {
            String* filename = new String(Files[i]); 
            String fn = *filename;
            char* menuItemText = strdup(fn.c_str());

            SDlocItems[menuIndex++] = new FileMenuItem(menuItemText, *filename, SD, handleFileSelection);
        }
    }
    
    SDlocItems[menuIndex++] = new ItemBack();
    SDlocItems[menuIndex] = nullptr;

    SDlocScreen = new MenuScreen(SDlocItems);
}
