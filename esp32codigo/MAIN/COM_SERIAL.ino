
HardwareSerial arduinoSerial(2); 

void COM_SERIAL_SETUP() {
  Serial.begin(115200); // For debugging on the ESP32 (using different pins)
  arduinoSerial.begin(115200, SERIAL_8N1, ARDUINO_RX_PIN, ARDUINO_TX_PIN);
  waitForGrblStartup();
  
}

void COM_SERIAL_LOOP() {
    if (arduinoSerial.available() > 0) {
    String grblResponse = arduinoSerial.readStringUntil('\n');
    grblResponse.trim();
    if (grblResponse.length() > 0) {
      Serial.print("Grbl Response: ");
      Serial.println(grblResponse);
    }
  }
  
}

void handleFileSelection(fs::FS& fs, const String filename) {
    Serial.print("\r\nOpening file: ");
    Serial.println(filename);
    
    String temppath = String("/") + String(filename);
    const char* path = temppath.c_str();
    File arch = fs.open(path);
    
    if (!arch) {
        Serial.println("Failed to open file");
        return;
    }
    
    while (arch.available()) {   
        String line = readLine(arch);
        if(arduinoSerial.available() > 0) {
             String grblResponse = arduinoSerial.readStringUntil('\n');
             Serial.println("Respuesta de GRBL: ");
             Serial.println(grblResponse);
        }
        if (line != "") {
          Serial.println("Mandando a GRBL: ");
          Serial.println(line);
          arduinoSerial.print(line);
          delay(100);
        }

    }
    
    arch.close();
    Serial.println("\r\nFile reading complete");
}

void waitForGrblStartup() {
  Serial.println("Waiting for Grbl startup...");  
  String grblLine;
  bool grblStarted = false;
    delay(10); 
        if (arduinoSerial.available() > 0) {
      grblLine = arduinoSerial.readStringUntil('\n');
      grblLine.trim(); 

      Serial.print("Grbl Line: "); //Debug
      Serial.println(grblLine);  
    }
}
