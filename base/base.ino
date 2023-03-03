#include <FastLED.h>
#include <WiFi.h>
#include <esp_now.h>

#include "RotaryEncoder.h"
#include "egg_shared.h"

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
#define SATURATION 100
#define BRIGHTNESS 255

#define ACTION_CHANGE_COLOR 0
#define ACTION_MOVE_HORIZONTAL 1
#define ACTION_MOVE_VERTICAL 2
#define ACTION_TOGGLE_CURSOR 3

bool cursorOn = true;
CHSV color = CHSV(0, SATURATION, BRIGHTNESS);

RotaryEncoder leftKnob = {
    LEFT_KNOB_CLK, LEFT_KNOB_DT, LEFT_KNOB_SW, 0, 0, 0, 0};
RotaryEncoder rightKnob = {
    RIGHT_KNOB_CLK, RIGHT_KNOB_DT, RIGHT_KNOB_SW, 0, 0, 0, 0};
RotaryEncoder swivel = {SWIVEL_CLK, SWIVEL_DT, SWIVEL_SW, 0, 0, 0, 0};

CRGB leds[2];

msg changeColor = {ACTION_CHANGE_COLOR};
msg moveHorizontal = {ACTION_MOVE_HORIZONTAL};
msg moveVertical = {ACTION_MOVE_VERTICAL};
msg toggleCursor = {ACTION_TOGGLE_CURSOR};

esp_now_peer_info_t peerInfo;

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

  leftKnob.led = &leds[0];
  rightKnob.led = &leds[1];

  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddressEgg, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void send(msg m) {
  esp_err_t result =
      esp_now_send(broadcastAddressEgg, (uint8_t *)&m, sizeof(m));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
}

void loop() {
  leftKnob.update();
  rightKnob.update();
  swivel.update();

  if (anyButtonClicked()) {
    Serial.print("Cursor toggled ");
    cursorOn = !cursorOn;
    if (cursorOn) {
      Serial.println("ON");
    } else {
      Serial.println("OFF");
    }
    toggleCursor.value = cursorOn;
    send(toggleCursor);
  }

  if (anyButtonHeld() && anyAngleChanged()) {
    Serial.println("Color changed");
    if (leftKnob.angleChanged) {
      color = CHSV(leftKnob.angle, SATURATION, BRIGHTNESS);
      changeColor.value = leftKnob.angle;
    } else if (rightKnob.angleChanged) {
      color = CHSV(rightKnob.angle, SATURATION, BRIGHTNESS);
      changeColor.value = rightKnob.angle;
    }
    send(changeColor);
  } else if (leftKnob.angleChanged) {
    Serial.println("Cursor moved horizontally");
    moveHorizontal.value = leftKnob.angle;
    send(moveHorizontal);
  } else if (rightKnob.angleChanged) {
    Serial.println("Cursor moved vertically");
    moveVertical.value = rightKnob.angle;
    send(moveVertical);
  }

  FastLED.clear();
  if (cursorOn || anyButtonHeld()) {
    leftKnob.setLED(color);
    rightKnob.setLED(color);
  }
  FastLED.show();
}

bool anyAngleChanged() {
  return leftKnob.angleChanged || rightKnob.angleChanged;
}

bool anyButtonClicked() {
  return leftKnob.buttonClicked || rightKnob.buttonClicked;
}

bool anyButtonHeld() { return leftKnob.buttonHeld || rightKnob.buttonHeld; }
