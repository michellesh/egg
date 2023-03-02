#include <FastLED.h>

#include "Ring.h"
#include "utils.h"

#define LED_PIN_1 14
#define LED_PIN_2 13
#define NUM_LEDS_PIN_1 124
#define NUM_LEDS_PIN_2 128
#define NUM_LEDS 252

#define NUM_RINGS 13
#define MAX_BRIGHTNESS 100 // 255 uses too much power for all LEDs

CRGB leds[NUM_LEDS];
Ring rings[NUM_RINGS];
int knobAngle = 0;

void setup() {
  setupLEDs();

  Serial.begin(115200);
  delay(500);

  setupRings();
}

bool closeDeg(float f1, float f2) { return int(abs(f2 - f1)) % 360 < 10; }
bool closeHeight(float f1, float f2) { return abs(f2 - f1) < 10; }

void loop() {
  FastLED.clear();

  /*
  // Knob controls degrees
  float degree = knobAngle;
  float height = ringHeight[3];

  // Knob controls height
  //float degree = 0;
  //float height = mapf(knobAngle, 0, 180, 0, maxRingHeight);

  for (int r = 0; r < NUM_RINGS; r++) {
    if (closeHeight(rings[r].height, height)) {
      for (int i = 0; i < rings[r].numLEDs; i++) {
        if (closeDeg(rings[r].deg[i], degree)) {
          rings[r].leds[i] = CHSV(i, 100, 255);
        }
      }
    }
  }
  */
  // for (int i = 0; i < NUM_LEDS; i++) {
  //   leds[i] = CHSV(i, 100, 255);
  // }
  for (int r = 0; r < NUM_RINGS; r++) {
    int hue = map(r, 0, NUM_RINGS, 0, 255);
    for (int i = 0; i < rings[r].numLEDs; i++) {
      rings[r].leds[i] = CHSV(hue, 100, 255);
    }
  }

  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.show();
}
