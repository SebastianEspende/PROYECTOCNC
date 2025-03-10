#include <ItemCommand.h>
#include <MenuItem.h>
#include <ItemBack.h>
#include <ItemSubMenu.h>
#include <FileMenuItem.h>

// Configuración del LCD


// Referencias externas
extern MenuScreen* WifiCfgScreen;

// Variables para manejo de archivos
int counter = 0;
bool SD0 = false;
String Files[MAX_FILES];

// Lista los archivos en un directorio de la SD
void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listando directorio: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("No se pudo abrir la ruta");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("No es una ruta válida");
    return;
  }
  if (counter > 50) {
    Serial.println("El número de archivos es mayor al máximo");
    return;
  }
  
  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  ARCHIVO: ");
      Serial.print(file.name());
      Serial.print("  TAMAÑO: ");
      Serial.println(file.size());
      Files[counter] = String(file.name());
      counter++;
    }
    file = root.openNextFile();
  }
}

// Configura e inicializa la tarjeta SD
void sdsetup() {
  if (!SD.begin()) {
    Serial.println("No se pudo inicializar la tarjeta SD");
    SD0 = true;
    return;
  } else {
    SD.begin();
  }
  
  uint8_t cardType = SD.cardType();
 
  if (cardType == CARD_NONE) {
    Serial.println("No hay tarjeta SD");
    return;
  }

  Serial.print("Tipo de tarjeta: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("DESCONOCIDA");
  }
  
  // Lista archivos y construye la pantalla
  listDir(SD, "/", 0);
  buildSDlocScreen();
  
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("TAMAÑO DE SD: %lluMB\n", cardSize);
  Serial.printf("Espacio total: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Espacio usado: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

char selectedFilename[256];
MenuScreen *SDlocScreen = nullptr;
MenuItem *SDlocItems[MAX_FILES + 2];

String readLine(File& file) {
    String line = "";
    while (file.available()) {
        char c = file.read();
        if (c == '\n' || c == '\r') break; 
        line += c;
    }
    return line;
}

String fileNames[MAX_FILES]; 


void buildSDlocScreen() {
  Serial.println("Building Local Files Screen...");
    if (SDlocScreen != nullptr) {
        delete SDlocScreen;
        SDlocScreen = nullptr;  
    }

    for (int i = 0; i < MAX_FILES + 2; i++) { 
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
    
    SDlocItems[menuIndex++] = new ItemBack("..");
    SDlocItems[menuIndex] = nullptr;

    SDlocScreen = new MenuScreen(SDlocItems);
}
