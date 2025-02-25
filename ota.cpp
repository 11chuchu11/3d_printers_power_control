#include "ota.h"

void setupOTA() {
    ArduinoOTA.onStart([]() {
        Serial.println("Inicio de actualización OTA...");
    });

    ArduinoOTA.onEnd([]() {
        Serial.println("\nActualización completa.");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progreso: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error OTA [%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Error de autenticación");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Error al iniciar");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Error de conexión");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Error al recibir");
        else if (error == OTA_END_ERROR) Serial.println("Error al finalizar");
    });

    ArduinoOTA.begin();
}
