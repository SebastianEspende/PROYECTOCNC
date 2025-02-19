#include <WiFi.h>

int btnGPIO = 0;
int btnState = false;
char *ssid = "";
char *password = "";
char *id = "";
int nSSID;
String WIFI[50];
#define MAX_WIFI_NETWORKS 50
MenuScreen *WifiScanScreen = nullptr;
MenuItem *WifiScanItems[MAX_WIFI_NETWORKS + 2]; // +2 for header and back item
String* ssidPointers; // Allocate String* array

void wifisetup() {
  WiFi.mode(WIFI_STA);
  pinMode(btnGPIO, INPUT);
  wifistart(ssid, password);
  Serial.println("Setup done");
  BuildWifiScreen();
}
void cback() {
              ssid = id;
  menu.setScreen(WifiCfgScreen);
              }

void wifiloop() {

  btnState = digitalRead(btnGPIO);
  if (btnState == LOW) {
    Serial.println("[WiFi] Desconectando del WiFi!");
    if (WiFi.disconnect(true, false)) {
      Serial.println("[WiFi] Desconectando del WiFi!");
    }
    delay(1000);
  }
}
void wifiscan() {
  Serial.println("Scan start");

  // WiFi.scanNetworks will return the number of networks found.
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      WIFI[i] = WiFi.SSID(i).c_str();
     // Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
      
      Serial.println();
      delay(10);
    }
}
  Serial.println("");

  // Delete the scan result to free memory for code below.
  WiFi.scanDelete();

  // Wait a bit before scanning again.
  delay(5000);
}

void wifistart(char *ssid, char *password) {
  Serial.println();
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int tryDelay = 500;
  int numberOfTries = 5;  while (true) {
    switch (WiFi.status()) {
      case WL_NO_SSID_AVAIL: Serial.println("[WiFi] SSID not found"); break;
      case WL_CONNECT_FAILED:
        Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
        return;
        break;
      case WL_CONNECTION_LOST: Serial.println("[WiFi] Connection was lost"); break;
      case WL_SCAN_COMPLETED:  Serial.println("[WiFi] Scan is completed"); break;
      case WL_DISCONNECTED:    Serial.println("[WiFi] WiFi is disconnected"); break;
      case WL_CONNECTED:
        Serial.println("[WiFi] WiFi is connected!");
        Serial.print("[WiFi] IP address: ");
        Serial.println(WiFi.localIP());
        return;
        break;
      default:
        Serial.print("[WiFi] WiFi Status: ");
        Serial.println(WiFi.status());
        break;
    }
    delay(tryDelay);

    if (numberOfTries <= 0) {
      Serial.print("[WiFi] No se pudo conectar!");
      // Use disconnect function to force stop trying to connect
      WiFi.disconnect();
      return;
    } else {
      numberOfTries--;
    }
  }
}

void BuildWifiScreen() {
  Serial.println("Start wifi scan");
  wifiscan();
  Serial.println("Building wifi ssid Screen...");
    if (WifiScanScreen != nullptr) {
        delete WifiScanScreen;
        WifiScanScreen = nullptr;  // Important: Set to nullptr after deleting
    }

    for (int i = 0; i < 50 + 2; i++) { // Clear the SDlocItems array
      WifiScanItems[i] = nullptr;
    }
    
    int menuIndex = 0;
    
    WifiScanItems[menuIndex++] = new ItemBack();
    WifiScanItems[menuIndex++] = new MenuItem("Networks");

    for (int i = 0; i < MAX_WIFI_NETWORKS; i++) {
            Serial.println("Aaaaaaa");
            Serial.println(WIFI[i]);
        if (WIFI[i].length() > 0) {
            Serial.println("bbbbbbb");
          const char* cString = WIFI[i].c_str();
           id = new char[strlen(cString) + 1];
           strcpy(id, cString);
            Serial.println(id);
            char* menuItemText = strdup(id);
            delete[] id;
            id = nullptr;

            WifiScanItems[menuIndex++] = new ItemCommand (menuItemText, cback);
        }
    }
    
    WifiScanItems[menuIndex] = nullptr;

    WifiScanScreen = new MenuScreen(WifiScanItems);
}

void wifibegin(const char *ssid,const char *password) {
  
  }
