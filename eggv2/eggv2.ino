#include <FastLED.h>

// Incremented once per iteration of the loop
unsigned long ticks = 0;

// clang-format off
#include "Ring.h"
#include "utils.h"
// clang-format on

#define LED_PIN_1 13
#define LED_PIN_2 14
#define NUM_LEDS_PIN_1 124
#define NUM_LEDS_PIN_2 128
#define NUM_LEDS 252

#define NUM_RINGS 13
#define MAX_BRIGHTNESS 50 // 255 uses too much power for all LEDs

Ring rings[NUM_RINGS];
CRGB leds[NUM_LEDS];

void setup() {
  setupLEDs();

  Serial.begin(115200);
  delay(500);

  setupRings();
  randomSeed(analogRead(0));
}

void loop() {
  FastLED.clear();

  // spiral();
  // twinkle();
  metaballs();

  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.show();
  ticks++;
}

void testAllLEDsOn() {
  for (int r = 0; r < NUM_RINGS; r++) {
    int hue = map(r, 0, NUM_RINGS, 0, 255);
    for (int i = 0; i < rings[r].numLEDs; i++) {
      rings[r].leds[i] = CHSV(hue, 100, 255);
    }
  }
}
