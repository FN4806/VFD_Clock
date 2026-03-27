# **Vacuum Fluorescent Display Clock Project**

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
  - Pliers
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
- Discrete Segment Control Logic
  - 2x SN74HC08N AND ICs
  - 1x SN74LS04N NOT IC
- Segment Voltage Control Chips
  - 3x AN6118 ICs
- Voltage Converters for Segment and Filament Voltages
  - ~2.6V Buck Converter for Filament Voltage 
  - ~18V Boost Converter for Segment Voltage

## Firmware

## Circuit & Design   

#### Initial Block Diagram:

![Functional Block Diagram](images/VFD-Block-Diagram.png)

#### Current Circuit Diagram:

![Circuit Diagram](images/VFD-circuit-diagram.png)

#### PCB Design:

![PCB Design](images/VFD-PCB-Design.png)
This is the first design for a PCB for this project, and as such it is not without it's bugs! However, the PCB is functional, and the clock still works.
Firstly, the 4-bit address bus connected to the EEPROM is wired in reverse; this was fixed in software using a function to flip the bits around.
Secondly, the footprint used for the 5-pin JST connected was incorrect for the style I had; to rectify this, I simply soldered some wires directly to the pad. 

In the next redesign, I need to fix the two existing hardware bugs, but I would also like to reduce the size of the PCB with some layout optimisation. 

#### New Design!

Following on from the initial PCB, I decided to mount the next PCB directly to the display for greater versatility.
In addition, the new circuit allows 8-stage variable brightness via a comparator-based PWM generator, includes a hardware multiplexer removing the need for software-based multiplexing, and includes both necessary DC-DC voltage converters.
The circuit only requires one external SPI connection!
More details can be found in my [other repository for this project](https://github.com/FN4806/VFD_Driver_PCB_3.0) that contains the KiCad project, including the circuit and PCB design.
