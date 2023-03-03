#include <FastLED.h>
#include <esp_now.h>
#include <WiFi.h>

#include "Ring.h"
#include "utils.h"
#include "egg_shared.h"

#define LED_PIN_1 14
#define LED_PIN_2 13
#define NUM_LEDS_PIN_1 124
#define NUM_LEDS_PIN_2 128
#define NUM_LEDS 252

#define NUM_RINGS 13
#define MAX_BRIGHTNESS 100 // 255 uses too much power for all LEDs

CRGB leds[NUM_LEDS];
Ring rings[NUM_RINGS];
//int knobAngle = 0;
float degree = 0;
float height = 0;
int hue = 0;
msg data;

void setup() {
  setupLEDs();

  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onDataRecv);

  setupRings();
}

// callback function that will be executed when data is received
void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
  switch(data.action) {
    case ACTION_CHANGE_COLOR:
      Serial.print("Change color: ");
      Serial.println(data.value);
      hue = data.value;
      break;
    case ACTION_MOVE_HORIZONTAL:
      Serial.print("Move horizontal: ");
      Serial.println(data.value);
      degree = data.value;
      break;
    case ACTION_MOVE_VERTICAL:
      Serial.print("Move vertical: ");
      Serial.println(data.value);
      height = data.value;
      break;
    case ACTION_TOGGLE_CURSOR:
      Serial.print("Toggle cursor: ");
      Serial.println(data.value);
      break;
  }
  Serial.println();
}

bool closeDeg(float f1, float f2) { return int(abs(f2 - f1)) % KNOB_MAX < 10; }
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
  */

  for (int r = 0; r < NUM_RINGS; r++) {
    if (closeHeight(rings[r].height, height)) {
      for (int i = 0; i < rings[r].numLEDs; i++) {
        if (closeDeg(rings[r].deg[i], degree)) {
          rings[r].leds[i] = CHSV(hue, 100, 255);
        }
      }
    }
  }

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
