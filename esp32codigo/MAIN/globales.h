#ifndef globales_h  
#define globales_h

// Pines para comunicación serial con Arduino
#define ARDUINO_RX_PIN 16 
#define ARDUINO_TX_PIN 4  

// Configuración de la pantalla LCD
#define LCD_ROWS 2
#define LCD_COLS 16

// Límite máximo de archivos a manejar
#define MAX_FILES 50

// Definición del tipo de función callback para manejo de archivos
typedef void(*FileCallbackFunction)(fs::FS& fs, String Filename);

#endif