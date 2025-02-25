#include "relay.h"

std::map<String, int> relays = {
    {"rele1", 5},   // GPIO5 (D1)
    {"rele2", 4},   // GPIO4 (D2)
    {"rele3", 0}    // GPIO0 (D3)
};


// Inicializa los pines de los relés como salidas
void setupRelays() {
    for (const auto& pair : relays) {
        pinMode(pair.second, OUTPUT);
        digitalWrite(pair.second, LOW);
    }
}

// Obtiene el estado de un relé
bool getRelayState(const String& relayName) {
    return digitalRead(relays[relayName]) == HIGH;
}

// Cambia el estado de un relé
void setRelayState(const String& relayName, bool state) {
    digitalWrite(relays[relayName], state ? HIGH : LOW);
}