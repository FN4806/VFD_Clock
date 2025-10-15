#include <Arduino.h>
#include "config/config.h"

namespace config {
    Pins pins{};
    GlobalFlags global_flags{};

    void InitialisePins() {
        pinMode(pins.kSerialData, OUTPUT);
        digitalWrite(pins.kDisplayChipEnable, LOW);
        pinMode(pins.kDisplayChipEnable, OUTPUT);
        pinMode(pins.kDisplayChipEnable, OUTPUT);

        pinMode(pins.kModeButton, INPUT_PULLUP);
        pinMode(pins.kSetButton, INPUT_PULLUP);
        pinMode(pins.kUpButton, INPUT_PULLUP);
        pinMode(pins.kDownButton, INPUT_PULLUP);
    }
}

