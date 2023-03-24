#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN  18
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // Change the color of the LED to red
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(1000);

  // Change the color of the LED to green
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(1000);

  // Change the color of the LED to blue
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(1000);
}
