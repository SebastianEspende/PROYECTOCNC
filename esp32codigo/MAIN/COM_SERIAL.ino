#include <LcdMenu.h>
#include <MenuScreen.h>
#include <display/LiquidCrystal_I2CAdapter.h>
#include <renderer/CharacterDisplayRenderer.h>
LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);
CharacterDisplayRenderer renderer(new LiquidCrystal_I2CAdapter(&lcd), LCD_COLS, LCD_ROWS);
LcdMenu menu(renderer);
extern MenuScreen* mainScreen;

// Configuración del puerto serial para comunicación con Arduino
HardwareSerial arduinoSerial(2); 

// Inicializa la comunicación serial
void COM_SERIAL_SETUP() {
  Serial.begin(115200); // Para depuración en el ESP32 
  arduinoSerial.begin(115200, SERIAL_8N1, ARDUINO_RX_PIN, ARDUINO_TX_PIN); // Para comunicacion con el GRBL de Arduino
}
//waitForGrblStartup(); // Esperamos a una respuesta de GRBL para continuar
// Función de loop para manejar comunicación serial
void COM_SERIAL_LOOP() {
  if (arduinoSerial.available() > 0) {
    String grblResponse = arduinoSerial.readStringUntil('\n');
    grblResponse.trim();
    if (grblResponse.length() > 0) {
      Serial.print("Respuesta de Grbl: ");
      Serial.println(grblResponse);
    }
  }
}

// Maneja la selección y procesamiento de archivos G-code
void handleFileSelection(fs::FS& fs, const String filename) {
  Serial.print("\r\nAbriendo archivo: ");
  Serial.println(filename);
  
  String temppath = String("/") + String(filename);
  const char* path = temppath.c_str();
  File arch = fs.open(path);
  
  if (!arch) {
      Serial.println("No se pudo abrir el archivo");
      return;
  }
  
  // Procesa cada línea del archivo y la envía a GRBL
  while (arch.available()) {   
      String line = readLine(arch);
      if (line != "") {
        Serial.println("Mandando a GRBL: ");
        Serial.println(line);
        arduinoSerial.println(line);
        delay(100);
      }
      while(arduinoSerial.available() > 0 ) {
           String grblResponse = arduinoSerial.readStringUntil('\n');
           if (grblResponse == "ok") break;
           Serial.println("Respuesta de GRBL: ");
           Serial.println(grblResponse);
      }
  }
  
  arch.close();
  menu.setScreen(mainScreen);
  Serial.println("\r\nLectura de archivo completada");
}

// Espera a que GRBL inicie y esté listo
/*void waitForGrblStartup() {
  Serial.println("Esperando inicio de Grbl...");  
  String grblLine;
  bool grblStarted = false;
  delay(10); 
  if (arduinoSerial.available() > 0) {
    grblLine = arduinoSerial.readStringUntil('\n');
    grblLine.trim(); 

    Serial.print("Línea de Grbl: "); // Depuración
    Serial.println(grblLine);  
  }
}*/
