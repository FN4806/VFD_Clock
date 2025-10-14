#include <Arduino.h>
#include "modules/display.h"
#include "config/config.h"

using namespace config;

namespace display
{
  void display::OutputData(int data1, int data2) {
    digitalWrite(pins.kDisplayChipEnable, LOW);
    digitalWrite(pins.kSerialClock, LOW);
    shiftOut(pins.kSerialData, pins.kSerialData, LSBFIRST, data2);
    shiftOut(pins.kSerialData, pins.kSerialData, LSBFIRST, data1);

    digitalWrite(pins.kSerialClock, LOW);
    digitalWrite(pins.kDisplayChipEnable, HIGH);
  }  

  void display::SetDigit(int digit, int segment, int extras_1, int extras_2) {
    int output1 = 0;
    int output2 = 0;
    if (segment >= 1) { 
        output1 = ((segment - 1) << 6) | 0b00100000 | extras_1;
        output2 = (extras_2 << 4) | digit;
    }
    else {
        output1 = 0b00000000 | extras_1;
        output2 = 0b00000000 | (extras_2 << 4);
    }

    OutputData(output1, output2);
  }
} 
