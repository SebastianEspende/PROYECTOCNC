#include <WiFi.h>

int btnGPIO = 0;
int btnState = false;
const char *ssid = "";
const char *password = "";
String id;
const int nSSID = WiFi.scanNetworks();
std::vector<String> WIFI(nSSID);
#define MAX_WIFI_NETWORKS 50
MenuScreen *WifiScanScreen = nullptr;
MenuItem *WifiScanItems[MAX_WIFI_NETWORKS + 2]; // +2 for header and back item
String* ssidPointers; // Allocate String* array

void wifisetup() {
  BuildWifiScreen();
  wifibegin(ssid, password);
}
void cback() {
              ssid = id.c_str();
              }
void BuildWifiScreen() {
  Serial.println("Building Local Files Screen...");
    if (WifiScanScreen != nullptr) {
        delete WifiScanScreen;
        WifiScanScreen = nullptr;  // Important: Set to nullptr after deleting
    }

    for (int i = 0; i < 50 + 2; i++) { // Clear the SDlocItems array
      WifiScanItems[i] = nullptr;
    }
    
    int menuIndex = 0;

    WifiScanItems[menuIndex++] = new MenuItem("Archivos Locales");

    for (int i = 0; i < counter && i < MAX_WIFI_NETWORKS; i++) {
        if (WIFI[i].length() > 0) {
            id = WIFI[i]; 
            char* menuItemText = strdup(id.c_str());

            WifiScanItems[menuIndex++] = new ItemCommand (menuItemText, cback);
        }
    }
    
    WifiScanItems[menuIndex++] = new ItemBack();
    WifiScanItems[menuIndex] = nullptr;

    WifiScanScreen = new MenuScreen(WifiScanItems);
}

void wifibegin(const char *ssid,const char *password) {
  pinMode(btnGPIO, INPUT);
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
