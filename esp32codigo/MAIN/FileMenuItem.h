#include "MenuItem.h"
#include "globales.h"

class FileMenuItem : public MenuItem {
private:
    String filename;           // Nombre del archivo
    fs::FS& fs;                // Sistema de archivos
    FileCallbackFunction ffptr; // Función callback a ejecutar
public:
    // Constructor
    FileMenuItem(const char* text, const String filename, fs::FS& fs, FileCallbackFunction ffptr) 
        : MenuItem(text), filename(filename), fs(fs), ffptr(ffptr) {}

protected:
    // Procesa los comandos recibidos
    bool process(LcdMenu* menu, const unsigned char command) override {
        switch (command) {
            case ENTER:
                executeCommand();
                return true;
            default:
                return false;
        }
    }
    
    // Ejecuta el comando asociado al archivo
    void executeCommand() {
        ffptr(fs, filename);
    }
};