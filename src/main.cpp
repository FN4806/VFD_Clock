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
  if (config::global_flags.mode_changed == 0) {
    config::global_flags.mode_changed = 1;

    if (Mode <= (MaxMode - 1)) {
      Mode++;
    } else {
      Mode = 0;
    }
  }
}

void setup() {
  if (!InitialiseClock()) {
    Mode = 10;
  }

  attachInterrupt(digitalPinToInterrupt(config::pins.kModeButton), ModeButtonInterrupt, FALLING);
  config::InitialisePins();
}

void setDisplay() {
  if (Mode == 0) {
    Serial.println("Clock Mode");
    SetTime();
  }

  if (Mode == 1) {
    Serial.println("Date Mode");
    SetDate();
  }

  if (Mode == 2) {
    Serial.println("Temp Mode");
    SetTemp();
  }

  if (Mode == 10) {
    Serial.println("Critial Error!");
    DisplayError();
  }
}

void loop() {
  config::global_flags.mode_changed = 0;
  setDisplay();
}