#include <Arduino.h>
#include "modules/display.h"
#include "config/config.h"

namespace display
{

  /// @brief  Flips the inputted BCD number
  /// @param digit - The digit to be flipped 
  /// @return flipped digit
  int FlipDigit(int digit) {
    int flipped_digit = 0;
    int check_digit = 0;

    for (int i=0; i<4; i++) {
      check_digit = 1 << i;
      if ((digit & check_digit) > 0) {
        flipped_digit = flipped_digit << 1;
        flipped_digit = flipped_digit | 1;
      } else {
        flipped_digit = flipped_digit << 1;
      }
    }
    return flipped_digit;
  }

  void OutputData(int data1, int data2) {
    digitalWrite(config::pins.kDisplayChipEnable, LOW);
    digitalWrite(config::pins.kSerialClock, LOW);

    shiftOut(config::pins.kSerialData, config::pins.kSerialClock, LSBFIRST, data2);
    shiftOut(config::pins.kSerialData, config::pins.kSerialClock, LSBFIRST, data1);

    digitalWrite(config::pins.kSerialClock, LOW);
    digitalWrite(config::pins.kDisplayChipEnable, HIGH);
  }  

  void SetDigit(int digit, int segment, int extras_1, int extras_2) {
    int output1 = 0;
    int output2 = 0;
    if (segment >= 1) { 
        output1 = ((segment - 1) << 6) | 0b00100000 | extras_1;
        output2 = (extras_2 << 4) | FlipDigit(digit);
    }
    else {
        output1 = 0b00000000 | extras_1;
        output2 = 0b00000000 | (extras_2 << 4);
    }

    OutputData(output1, output2);
  }
} 
