# **Vacuum Flourecent Display Clock Project**

![PlatformIO](https://img.shields.io/badge/PlatformIO-F5822A?logo=platformio&logoColor=white)
![Language](https://img.shields.io/badge/C++-00599C?logo=cplusplus)
![Microcontroller](https://img.shields.io/badge/Arduino_Nano_Every-00878F?logo=arduino)
![CAD](https://img.shields.io/badge/KiCad-314CB0?logo=kicad)

## Features

#### Current: 
- Date and Time Viewing
- Date and Time Setting 
- Temperature Sensing Mode
- Day of the Week Indicator
- RTC Module for Accurate Timekeeping

#### Planned:
- Alarm 
- Custom PCB
- Custom Enclosure

## Hardware

#### Equipment Used:
- 2x Standard Breadboards
- Bench Power Supply
- Bench Oscilloscope for Debugging
- Handheld Multimeter for Debugging
- Various Hand tools
  - Wire Stripper
  - Pliars
  - Tweezers
  - Flathead Screwdriver


#### Components Used: 
- Arduino Nano Every Microcontroller
- Unknown Origin VFD
- Real-Time Clock Module
- LM75 Temperature Sensing Module
- Custom BCD to Hexidecimal Segment Decoder
  - Using 1x AT28C64B-15PU EEPROM IC
- SPI Interfacing
  - Using 2x SN74HC595N Shift Registers
- Discrete Segement Control Logic
  - 2x SN74HC08N AND ICs
  - 1x SN74LS04N NOT IC
- Segment Voltage Control Chips
  - 3x AN6118 ICs
- Voltage Converters for Segment and Filament Volatges
  - ~2.6V Buck Comverter for Filament Voltage 
  - ~18V Boost Comverter for Segement Voltage

## Firmware

## Circuit & Design   
