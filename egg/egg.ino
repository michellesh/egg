#include <FastLED.h>

#include "Ring.h"
#include "utils.h"

// Pins
#define ENCODER_CLK 5 // D1
#define ENCODER_DT 4  // D2
#define ENCODER_SW 0  // D3
#define LED_PIN 2     // D4

#define MAX_CLICKS 40 // total clicks around the rotary encoders
#define NUM_LEDS 150  // TODO this is only the number glued so far
#define NUM_RINGS 13
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];
Ring rings[NUM_RINGS];
int knobAngle = 0;

void setup() {
  setupRotaryEncoders();
  setupLEDs();

  Serial.begin(115200);
  delay(500);
  setupRings();
}

bool closeDeg(float f1, float f2) { return int(abs(f2 - f1)) % 360 < 10; }
bool closeHeight(float f1, float f2) { return abs(f2 - f1) < 10; }

void loop() {
  FastLED.clear();
  updateKnobAngle();

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

  FastLED.setBrightness(isButtonPressed() ? MAX_BRIGHTNESS : 100);
  FastLED.show();
}
