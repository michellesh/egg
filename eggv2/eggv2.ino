#include <FastLED.h>

// Incremented once per iteration of the loop
unsigned long ticks = 0;

// clang-format off
#include "Ring.h"
#include "Timer.h"
#include "utils.h"
#include "colors.h"

#define LED_PIN_1 13
#define LED_PIN_2 14
#define NUM_LEDS_PIN_1 124
#define NUM_LEDS_PIN_2 128
#define NUM_LEDS 252

#define NUM_RINGS 13
#define MAX_BRIGHTNESS 100 // 255 uses too much power for all LEDs
#define SECONDS_PER_PATTERN 60
#define SECONDS_PER_PALETTE 30

Ring rings[NUM_RINGS];
CRGB leds[NUM_LEDS];

#include "Palette.h"
Palette palette;

#include "Pattern.h"
#include "Range.h"
#include "Spiral.h"
#include "Twinkle.h"

#include "SubPattern.h"
#include "SpiralSubPattern.h"
#include "TwinkleSubPattern.h"
// clang-format on

TwinkleSubPattern twinkle;

SpiralSubPattern rubberBandWorm(SpiralSubPattern::RUBBER_BAND_WORM);
SpiralSubPattern rubberBandNoAnchor(SpiralSubPattern::RUBBER_BAND_NO_ANCHOR);
SpiralSubPattern rubberBandAnchored(SpiralSubPattern::RUBBER_BAND_ANCHORED);
SpiralSubPattern growingSpirals(SpiralSubPattern::GROWING_SPIRALS);
SpiralSubPattern basicSpiralRotation(SpiralSubPattern::BASIC_SPIRAL_ROTATION);
SpiralSubPattern continuousSpiral(SpiralSubPattern::CONTINUOUS_SPIRAL);
SpiralSubPattern randomOrganic(SpiralSubPattern::RANDOM_ORGANIC);
SpiralSubPattern seaweed(SpiralSubPattern::SEAWEED);

// clang-format off
SubPattern *activePatterns[] = {
  //&twinkle,
  //&randomOrganic,
  &seaweed,
};
// clang-format on

Timer playPattern = {SECONDS_PER_PATTERN * 1000};
float brightness = MAX_BRIGHTNESS;
float fadeIncrement = 0.2;
uint8_t numPatterns = sizeof(activePatterns) / sizeof(activePatterns[0]);

Timer setOffsetWaveLength = {5000};
Timer setWidthWaveLength = {5000};
Timer setSpeedWaveLength = {5000};

void setup() {
  setupLEDs();

  Serial.begin(115200);
  delay(500);

  randomSeed(analogRead(0));

  setupRings();
  setupBlobs();
  setupStarfield();
}

void loop() {
  // fadeToBlackBy(leds, NUM_LEDS, 1);
  FastLED.clear();
  palette.cycle();

  // lavalamp();
  // starfield();

  static uint8_t activePatternIndex = 0;

  activePatterns[activePatternIndex]->show();
  //continuousSpiral.show();
  //randomOrganic.show();
  //seaweed.show();

  // Pattern transition
  if (brightness > 0 && playPattern.complete()) {
    // Fade out
    brightness -= fadeIncrement;
  } else if (brightness <= 0) {
    // Increment active pattern
    activePatternIndex = (activePatternIndex + 1) % numPatterns;
    playPattern.reset();
    brightness = 1;
  } else if (brightness < MAX_BRIGHTNESS) {
    // Fade in
    brightness += fadeIncrement;
  }

  FastLED.setBrightness(brightness);
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
