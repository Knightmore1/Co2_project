#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN  18
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void noProblem(){
  // Change la couleur de la LED en vert
  leds[0] = CRGB::Green;
  FastLED.show();
}

void warning(){    // fait clignoter la LED en orange
  // Change la couleur de la LED en vert
  leds[0] = CRGB::Orange;
  FastLED.show();
  delay(1000);
  // Etteint la LED
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
}

void danger(){    // fait clignoter la LED en rouge
  // Change la couleur de la LED en rouge
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Etteint la LED
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
}

void turnOff(){
  // Etteint la LED
  leds[0] = CRGB::Black;
  FastLED.show();
}

void loop() {

  //noProblem();

  //warning();

  //danger();

  turnOff();
}
