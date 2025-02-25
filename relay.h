#ifndef RELAY_H
#define RELAY_H

#include <map>
#include <Arduino.h>
#include "config.h"

extern std::map<String, int> relays;


void setupRelays();
bool getRelayState(const String& relayName);
void setRelayState(const String& relayName, bool state);


#endif
