#ifndef globales_h  
#define globales_h

#define ARDUINO_RX_PIN 16 
#define ARDUINO_TX_PIN 4  
#define LCD_ROWS 2
#define LCD_COLS 16
#define MAX_FILES 50

typedef void(*FileCallbackFunction)(fs::FS& fs, String Filename);



#endif
