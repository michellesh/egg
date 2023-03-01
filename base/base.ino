#include <FastLED.h>

#include "RotaryEncoder.h"

// Pins
#define LEFT_KNOB_CLK 25
#define LEFT_KNOB_DT 26
#define LEFT_KNOB_SW 27
#define RIGHT_KNOB_CLK 5
#define RIGHT_KNOB_DT 18
#define RIGHT_KNOB_SW 19
#define SWIVEL_CLK 21
#define SWIVEL_DT 22
#define SWIVEL_SW 23
#define LEFT_LED_PIN 13
#define RIGHT_LED_PIN 14

#define MAX_CLICKS 40

int leftKnobAngle = 0;
int rightKnobAngle = 0;
int swivelAngle = 0;

RotaryEncoder leftKnob = {LEFT_KNOB_CLK, LEFT_KNOB_DT, LEFT_KNOB_SW, 0, 0, 0};
RotaryEncoder rightKnob = {
    RIGHT_KNOB_CLK, RIGHT_KNOB_DT, RIGHT_KNOB_SW, 0, 0, 0};
RotaryEncoder swivel = {SWIVEL_CLK, SWIVEL_DT, SWIVEL_SW, 0, 0, 0};

CRGB leds[2];

void setup() {
  pinMode(LEFT_KNOB_CLK, INPUT);
  pinMode(LEFT_KNOB_DT, INPUT);
  pinMode(LEFT_KNOB_SW, INPUT);
  pinMode(RIGHT_KNOB_CLK, INPUT);
  pinMode(RIGHT_KNOB_DT, INPUT);
  pinMode(RIGHT_KNOB_SW, INPUT);
  pinMode(SWIVEL_CLK, INPUT);
  pinMode(SWIVEL_DT, INPUT);
  pinMode(SWIVEL_SW, INPUT);

  FastLED.addLeds<WS2812B, LEFT_LED_PIN, GRB>(leds, 1);
  FastLED.addLeds<WS2812B, RIGHT_LED_PIN, GRB>(leds, 1, 1);

  Serial.begin(115200);
  delay(500);
}

void loop() {
  FastLED.clear();

  leftKnob.update();
  rightKnob.update();
  swivel.update();

  EVERY_N_MILLISECONDS(500) {
    Serial.print("Left knob angle: ");
    Serial.println(leftKnob.angle);
    Serial.print("Right knob angle: ");
    Serial.println(rightKnob.angle);
    Serial.print("Swivel angle: ");
    Serial.println(swivel.angle);
  }

  leds[0] = CRGB::Green;
  leds[1] = CRGB::Blue;
  FastLED.show();
}
