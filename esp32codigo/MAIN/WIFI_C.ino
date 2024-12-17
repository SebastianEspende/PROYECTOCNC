#include <WiFi.h>
const char *ssid = "LaboPLC";
const char *password = "Link1982";

int btnGPIO = 0;
int btnState = false;
void wifisetup() {
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
