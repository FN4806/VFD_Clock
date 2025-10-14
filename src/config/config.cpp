#include <Arduino.h>
#include "config/config.h"

using namespace config;

void config::initialisePins() {
    pinMode(pins.kSerialData, OUTPUT);
    digitalWrite(pins.kDisplayChipEnable, LOW);
    pinMode(pins.kDisplayChipEnable, OUTPUT);
    pinMode(pins.kDisplayChipEnable, OUTPUT);

    pinMode(pins.kModeButton, INPUT_PULLUP);
    pinMode(pins.kSetButton, INPUT_PULLUP);
    pinMode(pins.kUpButton, INPUT_PULLUP);
    pinMode(pins.kDownButton, INPUT_PULLUP);
}