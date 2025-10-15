#ifndef CLOCK_H
#define CLOCK_H

namespace clock {
    // minutes, circle, time, centre dash, right dash
    extern int segs_1;
    // temperature, seconds, mode, left dash
    extern int segs_2;
    bool InitialiseClock();
    void SetTime();
    void SetDate();
    void SetTemp();
    void SetDayOfWeek(int day);
    void DisplayError();
}

#endif