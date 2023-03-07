#include <FastLED.h>

#include "Ring.h"
#include "utils.h"

#define LED_PIN_1 13
#define LED_PIN_2 14
#define NUM_LEDS_PIN_1 124
#define NUM_LEDS_PIN_2 128
#define NUM_LEDS 252

#define NUM_RINGS 13
#define MAX_BRIGHTNESS 50 // 255 uses too much power for all LEDs
#define CURSOR_SIZE 10

CRGB leds[NUM_LEDS];
Ring rings[NUM_RINGS];

int angle = 0;

void setup() {
  setupLEDs();

  Serial.begin(115200);
  delay(500);

  setupRings();
}

void loop() {
  FastLED.clear();

  twinkle();
  // testAllLEDsOn();

  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.show();
}

void testAllLEDsOn() {
  for (int r = 0; r < NUM_RINGS; r++) {
    int hue = map(r, 0, NUM_RINGS, 0, 255);
    for (int i = 0; i < rings[r].numLEDs; i++) {
      rings[r].leds[i] = CHSV(hue, 100, 255);
    }
  }
}
