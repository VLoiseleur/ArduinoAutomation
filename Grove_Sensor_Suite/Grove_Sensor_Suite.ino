#include "rgb_lcd.h"

// Instantiate our RGB LCD screen object
rgb_lcd lcd;

// Starting colors for our LCD screen
const int colorR = 255;
const int colorG = 0;
const int colorB = 255;

// Pin addresses for our temperature sensors
const int pinTemp0 = A0;
const int pinTemp1 = A1;
const int pinTemp2 = A2;
const int pinTemp3 = A3;

// Pin address for our button
const int pinButton = 2;

// State variable for switch statement
int sensorSwitch = 1;

void setup()
{
  // Check for connected temperature sensors
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.setRGB(colorR, colorG, colorB);

  // Print a message to the LCD.
  lcd.print("Starting...");

  delay(1000);
}

void loop()
{
  if (digitalRead(pinButton))
  {
    if (sensorSwitch > 4)
      sensorSwitch++;
    else if (sensorSwitch == 4)
      sensorSwitch = 1;
  }

  switch (sensorSwitch)
  {
    case 1:
      printTemperature(pinTemp1);
      break;
    case 2:
      printTemperature(pinTemp1);
      break;
    case 3:
      printTemperature(pinTemp2);
      break;
    case 4:
      printTemperature(pinTemp3);
      break;
  }
  delay(1000);
}

void printTemperature(int sensorPin)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor");
  lcd.setCursor(7, 0);
  lcd.print(sensorSwitch);

  // Start printing on next line
  lcd.setCursor(0, 1);
  lcd.print(calcTemp(sensorPin));
  lcd.setCursor(3, 1);
  lcd.print("C");
}

int calcTemp(int sensorPin)
{
  // B value of the thermistor
  int B = 3975;

  int val = analogRead(sensorPin);                               // get analog value
  Serial.println(val);
  float resistance = (float)(1023 - val) * 10000 / val;              // get resistance
  int temperature = 1 / (log(resistance / 10000) / B + 1 / 298.15) - 273.15; // calc temperature

  return temperature;
}
