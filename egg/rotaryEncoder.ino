bool isButtonPressed() { return digitalRead(ENCODER_SW) == LOW; }

void updateKnobAngle() {
  static int clicks = 0;
  static int prevCLK = digitalRead(ENCODER_CLK);
  int currentCLK = digitalRead(ENCODER_CLK);

  // A pulse occurs if the previous and the current state differ
  if (currentCLK != prevCLK) {
    if (digitalRead(ENCODER_DT) != currentCLK) {
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
    knobAngle = map(clicks, 0, MAX_CLICKS, 0, 360);
  }

  prevCLK = currentCLK;
}
