std::vector<std::string> all_local_files;
int numFiles = all_local_files.size();
String* Files = (String*)malloc(numFiles * sizeof(String));
int counter = 0;

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("No se pudo abrir la ruta");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("No es una ruta valida");
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
      Files[counter] = file.name();
      counter++;
      all_local_files.push_back(file.name());
    }
    file = root.openNextFile();
  }
}


void readFile(fs::FS &fs, const char *path) {
  Serial.printf("Leyendo archivo: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("No se pudo abrir el archivo");
    return;
  }

  Serial.print("Leyendo el archivo: ");
  Serial.print(file.name());
  Serial.print("/n");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void sdsetup() {
  if (!SD.begin()) {
    Serial.println("No se pudo inicializar la tarjeta SD");
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

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("TAMAÑO DE SD: %lluMB\n", cardSize);

  Serial.printf("Espacio total: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Espacio usado: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}
