#include <WiFi.h>

// Configuración y variables WiFi
int btnGPIO = 0;
int btnState = false;
char *ssid = "";
char *password = "";
char *id = "";
int nSSID;
String WIFI[50];
#define MAX_WIFI_NETWORKS 50

// Pantalla para escaneo WiFi
MenuScreen *WifiScanScreen = nullptr;
MenuItem *WifiScanItems[MAX_WIFI_NETWORKS + 2]; // +2 para encabezado y botón atrás
String *ssidPointers;                           

// Configura el WiFi
void wifisetup()
{
  WiFi.mode(WIFI_STA);
  pinMode(btnGPIO, INPUT);
  wifistart(ssid, password);
  Serial.println("Configuración completada");
  BuildWifiScreen();
}

// Callback para selección de red WiFi
void cback()
{
  ssid = id;
  menu.setScreen(WifiCfgScreen);
}

// Loop para monitorear estado WiFi
void wifiloop()
{
  btnState = digitalRead(btnGPIO);
  if (btnState == LOW)
  {
    Serial.println("[WiFi] ¡Desconectando del WiFi!");
    if (WiFi.disconnect(true, false))
    {
      Serial.println("[WiFi] ¡Desconectando del WiFi!");
    }
    delay(1000);
  }
}

// Escanea redes WiFi disponibles
void wifiscan()
{
  Serial.println("Iniciando escaneo");

  // WiFi.scanNetworks devuelve el número de redes encontradas
  int n = WiFi.scanNetworks();
  Serial.println("Escaneo finalizado");

  if (n == 0)
  {
    Serial.println("No se encontraron redes");
  }
  else
  {
    Serial.print(n);
    Serial.println(" redes encontradas");
    for (int i = 0; i < n; ++i)
    {
      WIFI[i] = WiFi.SSID(i).c_str();
      Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
      Serial.println();
      delay(10);
    }
  }

  Serial.println("");

  // Eliminar el resultado del escaneo para liberar memoria
  WiFi.scanDelete();

  // Esperar un poco antes de escanear de nuevo
  delay(5000);
}

// Inicia la conexión WiFi
void wifistart(char *ssid, char *password)
{
  Serial.println();
  Serial.print("[WiFi] Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int tryDelay = 500;
  int numberOfTries = 5;

  while (true)
  {
    switch (WiFi.status())
    {
    case WL_NO_SSID_AVAIL:
      Serial.println("[WiFi] SSID no encontrado");
      break;
    case WL_CONNECT_FAILED:
      Serial.print("[WiFi] Fallo - ¡WiFi no conectado! Razón: ");
      return;
      break;
    case WL_CONNECTION_LOST:
      Serial.println("[WiFi] La conexión se perdió");
      break;
    case WL_SCAN_COMPLETED:
      Serial.println("[WiFi] El escaneo está completado");
      break;
    case WL_DISCONNECTED:
      Serial.println("[WiFi] WiFi está desconectado");
      break;
    case WL_CONNECTED:
      Serial.println("[WiFi] ¡WiFi está conectado!");
      Serial.print("[WiFi] Dirección IP: ");
      Serial.println(WiFi.localIP());
      return;
      break;
    default:
      Serial.print("[WiFi] Estado WiFi: ");
      Serial.println(WiFi.status());
      break;
    }

    delay(tryDelay);

    if (numberOfTries <= 0)
    {
      Serial.print("[WiFi] ¡No se pudo conectar!");
      // Usar función disconnect para forzar detener intentos de conexión
      WiFi.disconnect();
      return;
    }
    else
    {
      numberOfTries--;
    }
  }
}

// Construye la pantalla de selección de red WiFi
void BuildWifiScreen()
{
  Serial.println("Iniciando escaneo wifi");
  wifiscan();
  Serial.println("Construyendo pantalla de ssid WiFi...");

  if (WifiScanScreen != nullptr)
  {
    delete WifiScanScreen;
    WifiScanScreen = nullptr;
  }

  for (int i = 0; i < 50 + 2; i++)
  { // Limpiar el array WifiScanItems
    WifiScanItems[i] = nullptr;
  }

  int menuIndex = 0;

  WifiScanItems[menuIndex++] = new ItemBack("..");
  WifiScanItems[menuIndex++] = new MenuItem("Redes wifi");
  Serial.println("Procesando redes...");

  for (int i = 0; i < MAX_WIFI_NETWORKS; i++)
  {
    Serial.println(WIFI[i]);
    if (WIFI[i].length() > 0)
    {
      Serial.println("Añadiendo red...");
      const char *cString = WIFI[i].c_str();
      id = new char[strlen(cString) + 1];
      strcpy(id, cString);
      Serial.println(id);
      char *menuItemText = strdup(id);
      delete[] id;
      id = nullptr;

      WifiScanItems[menuIndex++] = new ItemCommand(menuItemText, cback);
    }
  }

  WifiScanItems[menuIndex] = nullptr;

  WifiScanScreen = new MenuScreen(WifiScanItems);
}
