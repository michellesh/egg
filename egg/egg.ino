#include <FastLED.h>

// Pins
#define ENCODER_CLK 5 // D1
#define ENCODER_DT 4  // D2
#define ENCODER_SW 0  // D3
#define LED_PIN 2     // D4

#define MAX_CLICKS 40 // total clicks around the rotary encoders
#define NUM_LEDS 150  // TODO this is only the number glued so far
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];
int knobAngle = 0;

void setup() {
  setupRotaryEncoders();
  setupLEDs();

  Serial.begin(115200);
  delay(500);
}

void loop() {
  FastLED.clear();
  updateKnobAngle();

  int maxIndex = map(knobAngle, 0, 360, 0, NUM_LEDS);
  for (int i = 0; i < maxIndex; i++) {
    int hue = map(i, 0, NUM_LEDS, 0, 255);
    leds[i] = CHSV(hue, 100, 255);
  }

  EVERY_N_MILLISECONDS(500) {
    Serial.print("isButtonPressed: ");
    Serial.println(isButtonPressed());
    Serial.print("knobAngle: ");
    Serial.println(knobAngle);
  }

  FastLED.setBrightness(isButtonPressed() ? MAX_BRIGHTNESS : 100);
  FastLED.show();
}
