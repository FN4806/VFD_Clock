#include <Arduino.h>
#include <RTClib.h>
#include <Temperature_LM75_Derived.h>

#include "config/config.h"
#include "modules/display.h"
#include "modules/clock.h"

using namespace display;
using namespace clock;

int Mode = 0; // 0 = time, 1 = date, 2 = temp, 3 = time setup mode, 10 = Critial Error
int MaxMode = 2; 

void ModeButtonInterrupt() {
  static bool first_press = true;
  static unsigned long last_pressed = millis();

  if ((config::global_flags.mode_changed == 0) and (first_press or (millis() - last_pressed >= 200))) {
    first_press = false;
    last_pressed = millis();
    config::global_flags.mode_changed = 1;

    if (Mode < MaxMode) {
      Mode++;
    } else {
      Mode = 0;
    }
  }
}

void setup() {
  if (!InitialiseClock()) {
    config::global_flags.rtc_error = 1;
  }

  attachInterrupt(digitalPinToInterrupt(config::pins.kModeButton), ModeButtonInterrupt, FALLING);
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

  case 10:
    DisplayError();
    break;
  }
}

void loop() {
  if (config::global_flags.mode_changed == 1) config::global_flags.mode_changed = 0; 
  
  setDisplay();
}