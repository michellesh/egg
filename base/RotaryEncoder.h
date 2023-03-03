#define MAX_CLICKS                                                             \
  40 // number of clicks to do one full revolution around the rotary encoders
#define BUTTON_CLICK_THRESHOLD                                                 \
  300 // milliseconds to wait before the button is held instead of just clicked

struct RotaryEncoder {
  int pinCLK;
  int pinDT;
  int pinSW;
  int angle;
  int clicks;
  int prevCLK;
  int prevSW;
  bool angleChanged;
  bool buttonClicked;
  bool buttonHeld;
  unsigned long buttonPushedAtMillis;

  CRGB *led;

  void setLED(CHSV color) { led[0] = color; }

  void update() {
    int currentCLK = digitalRead(pinCLK);
    int currentSW = digitalRead(pinSW);

    // If the button was clicked, store the millis time when it was clicked
    if (prevSW == HIGH && currentSW == LOW) {
      buttonPushedAtMillis = millis();
    }
    buttonClicked = prevSW == LOW && currentSW == HIGH &&
                    timeSincePushed() < BUTTON_CLICK_THRESHOLD;
    buttonHeld = prevSW == LOW && currentSW == LOW &&
                 timeSincePushed() >= BUTTON_CLICK_THRESHOLD;

    // A pulse occurs if the previous and the current CLK state differ
    angleChanged = currentCLK != prevCLK;
    if (angleChanged) {
      if (digitalRead(pinDT) != currentCLK) {
        clicks++;
        if (clicks >= MAX_CLICKS) {
          clicks = 0;
        }
      } else {
        clicks--;
        if (clicks < 0) {
          clicks = MAX_CLICKS;
        }
      }

      // Set the rotation angle in degrees 0-360
      angle = map(clicks, 0, MAX_CLICKS, 0, KNOB_MAX);
    }

    prevCLK = currentCLK;
    prevSW = currentSW;
  }

  unsigned long timeSincePushed() { return millis() - buttonPushedAtMillis; }
};
