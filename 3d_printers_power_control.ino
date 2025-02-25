#include "config.h"
#include "relay.h"
#include "server.h"
#include "ota.h"

void setup() {
    Serial.begin(115200);
    setupRelays();

    WiFi.begin(ssid, password);
    Serial.println("Conectando a WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nConectado a WiFi");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("miimpresora")) {
        Serial.println("mDNS iniciado como miimpresora.local");
    }

    setupServer();
    setupOTA();
}

void loop() {
    MDNS.update();
    ArduinoOTA.handle();
}
