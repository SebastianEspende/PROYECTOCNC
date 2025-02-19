#include <WiFi.h>
const char *ssid = "LaboPLC";
const char *password = "Link1982";

int btnGPIO = 0;
int btnState = false;
void wifisetup() {
  pinMode(btnGPIO, INPUT);
  //Monitor.println();
  //Monitor.print("[WiFi] Connecting to ");
  //Monitor.println(ssid);

  WiFi.begin(ssid, password);
  int tryDelay = 500;
  int numberOfTries = 5;  while (true) {
    switch (WiFi.status()) {
      case WL_NO_SSID_AVAIL: //Monitor.println("[WiFi] SSID not found"); break;
      case WL_CONNECT_FAILED:
        //Monitor.print("[WiFi] Failed - WiFi not connected! Reason: ");
        return;
        break;
      case WL_CONNECTION_LOST: //Monitor.println("[WiFi] Connection was lost"); break;
      case WL_SCAN_COMPLETED:  //Monitor.println("[WiFi] Scan is completed"); break;
      case WL_DISCONNECTED:    //Monitor.println("[WiFi] WiFi is disconnected"); break;
      case WL_CONNECTED:
        //Monitor.println("[WiFi] WiFi is connected!");
        //Monitor.print("[WiFi] IP address: ");
        //Monitor.println(WiFi.localIP());
        return;
        break;
      default:
        //Monitor.print("[WiFi] WiFi Status: ");
        //Monitor.println(WiFi.status());
        break;
    }
    delay(tryDelay);

    if (numberOfTries <= 0) {
      //Monitor.print("[WiFi] No se pudo conectar!");
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
    //Monitor.println("[WiFi] Desconectando del WiFi!");
    if (WiFi.disconnect(true, false)) {
      //Monitor.println("[WiFi] Desconectando del WiFi!");
    }
    delay(1000);
  }
}
