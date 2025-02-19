#include "MenuItem.h"
#include "globales.h"

class FileMenuItem : public MenuItem {
private:
    String filename;
    fs::FS& fs;
    FileCallbackFunction ffptr;
public:
    FileMenuItem(const char* text, const String filename, fs::FS& fs, FileCallbackFunction ffptr) : MenuItem(text), filename(filename), fs(fs), ffptr(ffptr) {}

protected:
    bool process(LcdMenu* menu, const unsigned char command) override {
        switch (command) {
            case ENTER:
                executeCommand();
                return true;
            default:
                return false;
        }
    }
    void executeCommand() {
        ffptr(fs, filename);
    }
};
