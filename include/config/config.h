#ifndef CONFIG_H
#define CONFIG_H

namespace config {
    struct Pins {
        const int kSerialData = 11;
        const int kDisplayChipEnable = 10;
        const int kSerialClock = 13;
        const int kModeButton = 2;
        const int kSetButton = 3;
        const int kUpButton = 4;
        const int kDownButton = 5;
    };

    void initialisePins();

    extern Pins pins;
}

#endif