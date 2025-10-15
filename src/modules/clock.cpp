#include <Arduino.h>
#include <RTClib.h>
#include <Temperature_LM75_Derived.h>

#include "modules/clock.h"
#include "config/config.h"
#include "modules/display.h"
#include "utils/date_time_helper.h"

RTC_DS1307 rtc;
Generic_LM75 tempSensor;

using namespace clock;

config::GlobalFlags global_flags{};

// 0 = Sunday, 1 = Monday, ..., 5 = Friday, 6 = Saturday 
int day_segs_1[7] = {0b00011, 0b00001, 0b00010, 0b00011, 0b00000, 0b00001, 0b00010};
int day_segs_2[7] = {0b0001, 0b0000, 0b0000, 0b0000, 0b0001, 0b0001, 0b0001};

int clock::segs_1 = 0;
int clock::segs_2 = 0;

bool clock::InitialiseClock() {

    if (rtc.begin()) {
        Serial.println("---- RTC Module Connected! ----");
        return true;
    } else {
        Serial.println("---- Failed to find RTC Module ----");
        return false;
    }
}

void clock::SetTime() {
    Serial.println("ClockTime function");
    segs_1 = segs_1 | 0b10100;
    segs_2 = segs_2 | 0b0100;
    segs_2 = segs_2 & 0b0101;

    DateTime now = rtc.now();
    DateTimeHandler dateTimeHandler;
    dateTimeHandler.GetDigits(now);

    SetDayOfWeek(now.dayOfTheWeek());

    display::SetDigit(dateTimeHandler.hour_1, 1, segs_1, segs_2);
    delay(2);
    display::SetDigit(dateTimeHandler.hour_2, 2, segs_1, segs_2);
    delay(2);
    display::SetDigit(dateTimeHandler.minute_1, 3, segs_1, segs_2);
    delay(2);
    display::SetDigit(dateTimeHandler.minute_2, 4, segs_1, segs_2);
    delay(2);
}

void clock::SetDate() {        
    segs_1 = segs_1 & 0b01011;
    segs_2 = segs_2 & 0b0011;
    segs_2 = segs_2 | 0b0010;

    DateTime now = rtc.now();
    DateTimeHandler dateTimeHandler;
    dateTimeHandler.GetDigits(now);

    SetDayOfWeek(now.dayOfTheWeek());

    // Delay that also checks the sate of the global interrupt mode flag, ensuring that if the mode is changed, the MCU doesnt get stuck in a delay and cause lag for the user
    unsigned long start_time = millis();
    while ((millis() - start_time < 10000) and (global_flags.mode_changed != 1)) {
        display::SetDigit(dateTimeHandler.day_1, 1, segs_1, segs_2);
        delay(2);
        display::SetDigit(dateTimeHandler.day_2, 2, segs_1, segs_2);
        delay(2);
        display::SetDigit(dateTimeHandler.month_1, 3, segs_1, segs_2);
        delay(2);
        display::SetDigit(dateTimeHandler.month_2, 4, segs_1, segs_2);
        delay(2);
    }

    start_time = millis();
    while ((millis() - start_time < 10000) and (global_flags.mode_changed != 1)) {
        display::SetDigit(dateTimeHandler.year_1, 1, segs_1, segs_2);
        delay(2);
        display::SetDigit(dateTimeHandler.year_2, 2, segs_1, segs_2);
        delay(2);
        display::SetDigit(dateTimeHandler.year_3, 3, segs_1, segs_2);
        delay(2);
        display::SetDigit(dateTimeHandler.year_4, 4, segs_1, segs_2);
        delay(2);
    }
}

void clock::SetTemp() {
    DateTime now = rtc.now();
    SetDayOfWeek(now.dayOfTheWeek());

    // Bitmasks to set certain miscilaneous segments of the display
     segs_1 = segs_1 & 0b01011;
    segs_2 = segs_2 & 0b1001;
    segs_2 = segs_2 | 0b1000;

    int temp_c = tempSensor.readTemperatureC();
    int temp_1 = floor(temp_c/10);
    int temp_2 = temp_c % 10;

    display::SetDigit(temp_1, 2, segs_1, segs_2);
    delay(2);
    display::SetDigit(temp_2, 3, segs_1, segs_2);
    delay(2);
}

void clock::SetDayOfWeek(int day) {
    segs_1 = segs_1 & 0b11100;
    segs_2 = segs_2 & 0b1110;
    segs_1 = segs_1 | day_segs_1[day];
    segs_2 = segs_2 | day_segs_2[day];
}

void clock::DisplayError() {
    display::SetDigit(13, 1, segs_1, segs_2);
    delay(2);
    display::SetDigit(14, 2, segs_1, segs_2);
    delay(2);
    display::SetDigit(10, 3, segs_1, segs_2);
    delay(2);
    display::SetDigit(13, 4, segs_1, segs_2);
    delay(2);
}