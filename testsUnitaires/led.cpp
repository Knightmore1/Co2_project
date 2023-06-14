#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN  18
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void noProblem(){
    leds[0] = CRGB::Green;
    FastLED.show();  // Temps d'affichage de la couleur verte
    delay(6000);
}

void warning(){
  for (int i = 0; i < 3; i++) {
    leds[0] = CRGB::Orange;
    FastLED.show();
    delay(1000);  // Temps d'affichage de la couleur orange
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(1000);  // Temps d'extinction de la LED
  }
}

void warning(){
  for (int i = 0; i < 6; i++) {
    leds[0] = CRGB::red;
    FastLED.show();
    delay(500);  // Temps d'affichage de la couleur rouge
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(500);  // Temps d'extinction de la LED
  }
}

void turnOff(){
    leds[0] = CRGB::Black;
    FastLED.show();
}

void loop() {
    noProblem();
    warning();
    danger();
    turnOff();
}
