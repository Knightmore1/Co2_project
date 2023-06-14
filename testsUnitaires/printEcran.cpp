#include <Arduino.h>
#include "SSD1306Wire.h"

SSD1306Wire display(0x3c, SDA, SCL);

void setup()
{
  Serial.begin(9600);
  display.init();
  display.clear();
  display.drawString(0, 0, "Hello World");
  display.display();
}

void loop(){}
