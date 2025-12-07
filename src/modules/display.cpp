#include <Arduino.h>
#include "modules/display.h"
#include "config/config.h"

namespace display
{

  /// @brief Flips the inputted positive binary integer 
  /// @param digit The digit to be flipped, should be within the specified range of bits
  /// @param length The maximum number of bits in the binary number, e.g. for a byte, 8
  /// @return Returns the mirrored bits of the input
  int FlipDigit(int digit, int length) {
    int flipped_digit = 0;
    int check_digit = 0;
    
    for (int i=0; i<length; i++) {
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

  /// @brief Output data through the shift registers with LSB first using bitbanged SPI. This function is designed to work with two bytes of data.
  /// @param data1 The first byte of the data to be outputted, higher byte
  /// @param data2 The second byte of the data to be outputted, lower byte
  void OutputData(int data1, int data2) {
    digitalWrite(config::pins.kDisplayChipEnable, LOW);
    digitalWrite(config::pins.kSerialClock, LOW);

    shiftOut(config::pins.kSerialData, config::pins.kSerialClock, LSBFIRST, data2);
    shiftOut(config::pins.kSerialData, config::pins.kSerialClock, LSBFIRST, data1);

    digitalWrite(config::pins.kSerialClock, LOW);
    digitalWrite(config::pins.kDisplayChipEnable, HIGH);
  }  

  /// @brief Set one of the display's digits to a certain value
  /// @param digit The number you want to display, one byte max e.g. 0x0 - 0xF
  /// @param segment The segment you want to display the digit on, 1 - 4
  /// @param extras_1 5 bits = min | circle | time | mid dash | right dash 
  /// @param extras_2 4 bits = heating | sec | mode | left dash
  void SetDigit(int digit, int segment, int extras_1, int extras_2) {
    int output1 = 0;
    int output2 = 0;
    if (segment >= 1) { 
        output1 = ((segment - 1) << 6) | 0b00100000 | extras_1;
        output2 = (extras_2 << 4) | FlipDigit(digit, 4);
    }
    else {
        output1 = 0b00000000 | extras_1;
        output2 = 0b00000000 | (extras_2 << 4);
    }

    OutputData(output1, output2);
  }
} 
