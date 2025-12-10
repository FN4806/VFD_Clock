#include <Arduino.h>
#include <RTClib.h>
#include <Temperature_LM75_Derived.h>
#include <string.h>

#include "config/config.h"
#include "modules/display.h"
#include "modules/clock.h"
#include "utils/date_time_helper.h"

using namespace display;
using namespace ClockFunctionality;

int Mode = 0; // 0 = time, 1 = date, 2 = temp, 3 = time setup mode, 10 = Fatal Error

// Future implementation: use enum instead of int value to store the mode
enum class Modes {
  time = 0,
  date,
  temp,
  time_setup
};
Modes mode = Modes::time;

int MaxMode = 2; // The highest mode available for the microcontroller

void IncrementInterrupt() {
  static bool first_press = true;
  static unsigned long last_pressed = millis();

  if (first_press or (millis() - last_pressed >= 200)) {
    first_press = false;
    last_pressed = millis();

    if (mode == Modes::time and config::time_setting.flash_mode == 0) { // Time setting hour
      if (config::time_setting.hh >= 24) config::time_setting.hh = 0; else config::time_setting.hh++;

    } else if (mode == Modes::time and config::time_setting.flash_mode == 1) { // Time setting minute
      if (config::time_setting.mm >= 59) config::time_setting.mm = 0; else config::time_setting.mm++;

    } else if (mode == Modes::date and config::time_setting.flash_mode == 0) { // Date setting day
      if (config::time_setting.DD >= DateTimeHandler::CheckDays(config::time_setting.MM, config::time_setting.YYYY)) config::time_setting.DD = 0; else config::time_setting.DD++;
      
    } else if (mode == Modes::date and config::time_setting.flash_mode == 1) { // Date setting month
      if (config::time_setting.MM >= 12) config::time_setting.MM = 0; else config::time_setting.MM++;

    } else if (mode == Modes::date and config::time_setting.flash_mode == 2) { // Date setting year
      // DS1307 RTC Chip has a date range of 00-99 (preceeded by 20 for 2000-2099)
      if (config::time_setting.YYYY >= 2099) config::time_setting.YYYY = 2000; else config::time_setting.YYYY++;
    }
  }
}

void DecrementInterrupt() {
  static bool first_press = true;
  static unsigned long last_pressed = millis();

  if (first_press or (millis() - last_pressed >= 200)) {
    first_press = false;
    last_pressed = millis();

    if (mode == Modes::time and config::time_setting.flash_mode == 0) { // Time setting hour
      if (config::time_setting.hh <= 0) config::time_setting.hh = 24; else config::time_setting.hh--;

    } else if (mode == Modes::time and config::time_setting.flash_mode == 1) { // Time setting minutes
      if (config::time_setting.mm <= 0) config::time_setting.mm = 59; else config::time_setting.mm--;

    } else if (mode == Modes::date and config::time_setting.flash_mode == 0) { // Date setting day
      if (config::time_setting.DD <= 0) config::time_setting.DD = DateTimeHandler::CheckDays(config::time_setting.MM, config::time_setting.YYYY); else config::time_setting.DD--;

    } else if (mode == Modes::date and config::time_setting.flash_mode == 1) { // Date setting month
      if (config::time_setting.MM <= 0) config::time_setting.MM = 12; else config::time_setting.MM--;

    } else if (mode == Modes::date and config::time_setting.flash_mode == 2) { // Date setting year
      // DS1307 RTC Chip has a date range of 00-99 (preceeded by 20 for 2000-2099)
      if (config::time_setting.YYYY <= 2000) config::time_setting.YYYY = 2099; else config::time_setting.YYYY--;

    }
  }
}

void ModeButtonInterrupt() {
  static bool first_press = true;
  static unsigned long last_pressed = millis();

  if ((config::global_flags.mode_changed == 0) and (first_press or (millis() - last_pressed >= 200)) and (config::global_flags.adjust_active == 0)) {
    first_press = false;
    last_pressed = millis();
    config::global_flags.mode_changed = 1;

    if (Mode < MaxMode) {
      Mode++;
    } else {
      Mode = 0;
    }
  } else if ((config::global_flags.adjust_active == 1) and (first_press or (millis() - last_pressed >= 200))) {
    first_press = false;
    last_pressed = millis();

    if (Mode == 1) {
      config::time_setting.flash_mode++;
      if (config::time_setting.flash_mode > 3) {
        config::time_setting.flash_mode = 0;
      }
    } else {
      if (config::time_setting.flash_mode == 0) config::time_setting.flash_mode = 1; else config::time_setting.flash_mode = 0;
    }
  }
}

void SetTimeInterrupt() {
  int pinState = digitalRead(config::pins.kSetButton);
  static unsigned long first_pressed = millis();

  int seconds_pressed = (millis() - first_pressed) / 1000;

  if (pinState == 0) {
    first_pressed = millis();
  } else if (millis() - first_pressed > 2000) {
    
    Serial.print("Button held for ");
    Serial.print(seconds_pressed);
    Serial.println("s!");

    if (config::global_flags.adjust_active == 0) config::global_flags.adjust_active = 1; else config::global_flags.time_set = 1;
    
    first_pressed = millis();
  }
}

void setup() {
  Serial.begin(115200);

  if (!InitialiseClock()) {
    config::global_flags.rtc_error = 1;
  }

  attachInterrupt(digitalPinToInterrupt(config::pins.kModeButton), ModeButtonInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(config::pins.kSetButton), SetTimeInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(config::pins.kUpButton), IncrementInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(config::pins.kDownButton), DecrementInterrupt, FALLING);
  config::InitialisePins();
}

void setDisplay() {
  switch (Mode) 
  {
  case 0:
    SetTime();
    break;

  case 1:
    SetDate();
    break;

  case 2:
    SetTemp();
    break;
  }
}

void loop() {
  if (config::global_flags.mode_changed == 1) config::global_flags.mode_changed = 0; 
  
  setDisplay();
}