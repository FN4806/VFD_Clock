#include <Arduino.h>
#include <RTClib.h>
#include <Temperature_LM75_Derived.h>

#include "config/config.h"
#include "modules/display.h"

RTC_DS1307 rtc;
Generic_LM75 tempSensor;

using namespace config;
using namespace display;

// min, circle, time, centre dash, right dash
int segs1 = 0b10000;

// heating, sec, mode, left dash
int segs2 = 0b0100;

unsigned long waitLoop;

int mode = 0; // 0 = time, 1 = date, 2 = temp, 3 = time setup mode

int m1;
int m2;
int h1;
int h2;
int d1;
int d2;
int y1;
int y2;
int y3;
int y4;
int t1;
int t2;

// Temperatue Sensor Pin
int tempPin = 0;

// true when the time is being set
bool settingStatus = false;

// 0 = Sunday, 1 = Monday, ..., 5 = Friday, 6 = Saturday 
int daySegs1[7] = {0b00011, 0b00001, 0b00010, 0b00011, 0b00000, 0b00001, 0b00010};
int daySegs2[7] = {0b0001, 0b0000, 0b0000, 0b0000, 0b0001, 0b0001, 0b0001};

void displayDDMM() {
  SetDigit(d1, 1, segs1, segs2);
  delay(2);
  SetDigit(d2, 2, segs1, segs2);
  delay(2);
  SetDigit(m1, 3, segs1, segs2);
  delay(2);
  SetDigit(m2, 4, segs1, segs2);
  delay(2); 
}

void displayYYYY() {
  SetDigit(y1, 1, segs1, segs2);
  delay(2);
  SetDigit(y2, 2, segs1, segs2);
  delay(2);
  SetDigit(y3, 3, segs1, segs2);
  delay(2);
  SetDigit(y4, 4, segs1, segs2);
  delay(2);   
}

bool checkButtons() {
  bool pressedState = false;
  
  if (digitalRead(pins.kModeButton) != 1) {
    pressedState = true;
  }
  
  if (digitalRead(pins.kSetButton) != 1) {
    pressedState = true;
  }
  
  return pressedState;
}

void Date() {
  //Serial.println(" --- Date Function --- ");
  segs1 = segs1 & 0b01011;
  segs2 = segs2 & 0b0011;
  segs2 = segs2 | 0b0010;

  DateTime now = rtc.now();

  y1 = now.year() / 1000;
  y2 = (now.year() / 100) - (y1 * 10);
  y3 = (now.year() / 10) - ((y1 * 100) + (y2 * 10));
  y4 = now.year() % 10;

  m1 = now.month() / 10;
  m2 = now.month() - (m1 * 10);

  d1 = now.day() / 10;
  d2 = now.day() - (d1*10);

  if (digitalRead(pins.kModeButton) != 1) {
    goto QuickExit;
  }

  waitLoop = millis();
  Serial.println("Starting display waits");
  while (millis() - waitLoop <= 10000) {
    //Serial.println(digitalRead(MODE_BTN));
    displayDDMM();

    if (checkButtons()) {
      goto QuickExit;
  }
  }

  waitLoop = millis();
  while (millis() - waitLoop <= 10000) {
    //Serial.println(digitalRead(MODE_BTN));
    displayYYYY();

    if (checkButtons()) {
      goto QuickExit;
    }
  }  

  QuickExit:
    return;
}

void Clock() {
  //Serial.println("--- Clock Function: ---");
  segs1 = segs1 | 0b10100;
  segs2 = segs2 | 0b0100;
  segs2 = segs2 & 0b0101;
  
  DateTime now = rtc.now();
  
  h1 = now.hour() / 10;
  h2 = now.hour() - (h1*10);

  m1 = now.minute() / 10;
  m2 = now.minute() - (m1*10);

  //Serial.print("Attempting to display digit: ");
  //Serial.println(h1);
  SetDigit(h1, 1, segs1, segs2);
  delay(2);
  //Serial.print("Attempting to display digit: ");
  //Serial.println(h2);
  SetDigit(h2, 2, segs1, segs2);
  delay(2);
  //Serial.print("Attempting to display digit: ");
  //Serial.println(m1);
  SetDigit(m1, 3, segs1, segs2);
  delay(2);
  //Serial.print("Attempting to display digit: ");
  //Serial.println(m2);
  SetDigit(m2, 4, segs1, segs2);
  delay(2); 
}

void day() {
  DateTime now = rtc.now();
  int day = now.dayOfTheWeek();

  segs1 = segs1 & 0b11100;
  segs2 = segs2 & 0b1110;

  segs1 = segs1 | daySegs1[day];
  segs2 = segs2 | daySegs2[day];
}

void temp() {
  segs1 = segs1 & 0b01011;
  segs2 = segs2 & 0b1001;
  segs2 = segs2 | 0b1000;

  // int tempReading = analogRead(tempPin);
  // double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  // tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
  // float tempC = tempK - 273.15;
  // float tempF = (tempC * 9.0)/ 5.0 + 32.0;

  // int intTempC = tempC;

  // t1 = intTempC / 10;
  // t2 = intTempC - (t1*10);

  int tempC = tempSensor.readTemperatureC();
  t1 = tempC / 10;
  t2 = tempC - (t1*10);

  //Serial.print("Temperature: ");
  //Serial.print(tempC);
  //Serial.println("C");

  SetDigit(t1, 2, segs1, segs2);
  delay(2);
  SetDigit(t2, 3, segs1, segs2);
  delay(2);
}

void setup() {
  //Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    
    segs1 = segs1 | 0b01000;
    SetDigit(8, 1, segs1, segs2);
    while (true) {
      Serial.println("Setting Display");
      SetDigit(13, 1, segs1, segs2);
      delay(2);
      SetDigit(14, 2, segs1, segs2);
      delay(2);
      SetDigit(10, 3, segs1, segs2);
      delay(2);
      SetDigit(13, 4, segs1, segs2);
      delay(2);
    }
  } 
  else {
    Serial.println(" --- RTC Module Connected --- ");
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  initialisePins();
}

void timeSet() {
  while (digitalRead(pins.kModeButton) != 1) {

    int setMode = 0; // 0 = hours, 1 = minutes

    // Change the set mode when the set button is pressed
    if ((digitalRead(pins.kSetButton) != 1) & ((millis() - waitLoop) > 500)) {
      if (setMode = 0) {
        setMode = 1;
      }
      else {
        setMode = 0;
      }

      waitLoop = millis();
    }

    // Define Minutes and Seconds Variable
    int setMins = rtc.now().minute();
    int setHours = rtc.now().hour();

    // Handle Additions and Subtractions to Minutes or Seconds 
    
    if ((digitalRead(pins.kUpButton) != 1) & ((millis() - waitLoop) > 500)) {
      if (setMode = 0) {
        if (setMins < 59) {
          setMins++;
        }
        else {
          setMins = 0;
        }
      }
      else {
        if (setHours < 23) {
          setHours++;
        }
        else {
          setHours = 0;
        }
      }
      waitLoop = millis();
    }

    if ((digitalRead(pins.kDownButton) != 1) & ((millis() - waitLoop) > 500)) {
      if (setMode = 0) {
        if (setMins > 0) {
          setMins--;
        }
        else {
          setMins = 59;
        }
      }
      else {
        if (setHours > 0) {
          setHours--;
        }
        else {
          setHours = 23;
        }
      }
      waitLoop = millis();
    }

    // Flash Digits on Screen Starting with Minutes
    unsigned long flashTimer;
    segs1 = segs1 | 0b10100;
    segs2 = segs2 | 0b0100;
    segs2 = segs2 & 0b0101;

    h1 = setHours / 10;
    h2 = setHours - (h1*10);

    m1 = setMins / 10;
    m2 = setMins - (m1*10);

    if (setMode = 0) {
      // flash hours
      if ((millis() - flashTimer) < 500) {
        SetDigit(h1, 1, segs1, segs2);
        delay(2);
        SetDigit(h2, 2, segs1, segs2);
        delay(2);
        SetDigit(m1, 3, segs1, segs2);
        delay(2);
        SetDigit(m2, 4, segs1, segs2);
        delay(2); 
      }
      else if ((millis() - flashTimer) < 1000) {
        SetDigit(m1, 3, segs1, segs2);
        delay(2);
        SetDigit(m2, 4, segs1, segs2);
        delay(2); 
      }
      else {
        flashTimer = millis();
      }
    }
    else {
      // flash minutes 
      if ((millis() - flashTimer) < 500) {
        SetDigit(h1, 1, segs1, segs2);
        delay(2);
        SetDigit(h2, 2, segs1, segs2);
        delay(2);
        SetDigit(m1, 3, segs1, segs2);
        delay(2);
        SetDigit(m2, 4, segs1, segs2);
        delay(2); 
      }
      else if ((millis() - flashTimer) < 1000) {
        SetDigit(h1, 1, segs1, segs2);
        delay(2);
        SetDigit(h2, 2, segs1, segs2);
        delay(2); 
      }
      else {flashTimer = millis();}
    }

    // Commit Changes after every loop
    DateTime stored = rtc.now();
    rtc.adjust(DateTime(stored.year(), stored.month(), stored.day(), setMins, setHours, 0)); // DateTime Format = DateTime(YYYY, MM, DD, hh, mm, ss)
  }
  mode = 0;
}

void setDisplay() {
  if (mode == 0) {
    Serial.println("Clock Mode");
    Clock();
  }

  if (mode == 1) {
    Serial.println("Date Mode");
    Date();
  }

  if (mode == 2) {
    Serial.println("Temp Mode");
    temp();
  }

  if (mode == 3) {
    Serial.println("Set Mode");
    timeSet();
  }

  day();
}

void loop() {
  //Serial.println(" --- Loop Tick --- ");
  Serial.println("Main Loop Begining:");
  Serial.print("Button State = ");
  Serial.println(digitalRead(pins.kModeButton));
  if (digitalRead(pins.kModeButton) != 1) {
    Serial.println("Button Pressed");
    if (mode < 2) {
      mode++;
    }
    else {
      mode = 0;
    }
    
    Serial.println("Looping display set for button debounce");
    waitLoop = millis();
    while (millis() - waitLoop < 500) {
      setDisplay();
    }
  }

  if (digitalRead(pins.kSetButton) != 1) {
    Serial.println("Set Button Pressed");
    mode = 3;
    while (millis() - waitLoop < 500) {
      Clock();
    }
    setDisplay();
  }

  Serial.println("Setting Display");
  setDisplay();
}
