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
    int working_number = digit;
    for (int i=3; i>=0; i--) {
      // get bit in i position
      flipped_digit |= (working_number >> i);
      working_number -= (working_number & (1 << i));
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
    Serial.print("Digit = ");
    Serial.print(digit);
    Serial.print(" | ");
    Serial.print("Flipped digit = ");
    Serial.println(FlipDigit(digit));
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
