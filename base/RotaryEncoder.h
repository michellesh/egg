#define MAX_CLICKS 40

struct RotaryEncoder {
  int pinCLK;
  int pinDT;
  int pinSW;
  int angle;
  int clicks;
  int prevCLK;

  void update() {
    int currentCLK = digitalRead(pinCLK);

    // A pulse occurs if the previous and the current state differ
    if (currentCLK != prevCLK) {
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
      angle = map(clicks, 0, MAX_CLICKS, 0, 360);
    }

    prevCLK = currentCLK;
  }
};

// bool isButtonPressed() { return digitalRead(ENCODER_SW) == LOW; }
