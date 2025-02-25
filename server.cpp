#include "server.h"
#include "relay.h"
#include <ArduinoJson.h>

// Verifica si la petición tiene el token de autorización correcto
bool isAuthorized(AsyncWebServerRequest* request) {
    if (!request->hasHeader("Authorization")) return false;
    return request->header("Authorization") == secret_token;
}

// Configura el servidor con las nuevas rutas
void setupServer() {
    // Obtener estado de un relé
    server.on("^/status/([a-zA-Z0-9]+)$", HTTP_GET, [](AsyncWebServerRequest* request) {
        if (!isAuthorized(request)) {
            request->send(403, "application/json", "{\"error\":\"Unauthorized\"}");
            return;
        }

        String relayName = request->pathArg(0);

        // Verificar si el relé existe en el mapa
        if (relays.find(relayName) == relays.end()) {
            request->send(400, "application/json", "{\"error\":\"Invalid relay name\"}");
            return;
        }

        DynamicJsonDocument doc(128);
        doc["relay"] = relayName;
        doc["state"] = getRelayState(relayName) ? "on" : "off";

        String jsonString;
        serializeJson(doc, jsonString);
        request->send(200, "application/json", jsonString);
    });

    // Encender/apagar un relé
    server.on("^/power/([a-zA-Z0-9]+)/([a-zA-Z]+)$", HTTP_GET, [](AsyncWebServerRequest* request) {
        if (!isAuthorized(request)) {
            request->send(403, "application/json", "{\"error\":\"Unauthorized\"}");
            return;
        }

        String relayName = request->pathArg(0);
        String state = request->pathArg(1);

        if (relays.find(relayName) == relays.end()) {
            request->send(400, "application/json", "{\"error\":\"Invalid relay name\"}");
            return;
        }

        if (state != "on" && state != "off") {
            request->send(400, "application/json", "{\"error\":\"Invalid state\"}");
            return;
        }

        setRelayState(relayName, state == "on");
        request->send(200, "application/json", "{\"message\":\"Relay updated\"}");
    });

    server.begin();
}
