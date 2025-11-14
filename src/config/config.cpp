#include <Arduino.h>
#include "config/config.h"

namespace config {
    Pins pins{};
    GlobalFlags global_flags{};
    TimeSetting time_setting{};

    void InitialisePins() {
        pinMode(pins.kSerialData, OUTPUT);
        digitalWrite(pins.kDisplayChipEnable, LOW);
        pinMode(pins.kDisplayChipEnable, OUTPUT);
        digitalWrite(pins.kDisplayChipEnable, HIGH);
        pinMode(pins.kSerialClock, OUTPUT);

        pinMode(pins.kModeButton, INPUT_PULLUP);
        pinMode(pins.kSetButton, INPUT_PULLUP);
        pinMode(pins.kUpButton, INPUT_PULLUP);
        pinMode(pins.kDownButton, INPUT_PULLUP);
    }
}