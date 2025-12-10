#ifndef CONFIG_H
#define CONFIG_H

namespace config {
    // Future Implementation: Switch to Enums
    enum class time_setting_modes {
        time_hh = 0,
        time_mm = 1,
        date_dd = 2,
        date_mm = 3,
        date_yyyy = 4
    };

    struct Pins {
        const int kSerialData{11};
        const int kDisplayChipEnable{10};
        const int kSerialClock{13};
        const int kModeButton{2};
        const int kSetButton{3};
        const int kUpButton{4};
        const int kDownButton{5};
    };

    struct GlobalFlags {
        volatile int mode_changed{0};
        volatile int adjust_active{0};
        volatile int time_set{0};
        int rtc_error{0};
    };

    struct TimeSetting {
        volatile int flash_mode{0};
        volatile int mode{0};
        int hh{0};
        int mm{0};
        int DD{0};
        int MM{0};
        int YYYY{0};
    };

    void InitialisePins();

    extern GlobalFlags global_flags;
    extern Pins pins;
    extern TimeSetting time_setting;
}

#endif