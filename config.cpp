#include "config.h"
#include "enviroment.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PSSW;
const char* secret_token = ACCESS_TOKEN;

AsyncWebServer server(80);
