#ifndef CONFIG_H
#define CONFIG_H

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>

#define MAX_RELAYS 4  // Número de relés permitidos
extern const char* ssid;
extern const char* password;
extern const char* secret_token;
extern AsyncWebServer server;

#endif
