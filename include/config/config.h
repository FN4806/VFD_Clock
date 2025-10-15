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

    struct GlobalFlags {
        volatile int mode_changed = 0;
        int rtc_error = 0;
    };

    void InitialisePins();

    extern GlobalFlags global_flags;
    extern Pins pins;
}

#endif