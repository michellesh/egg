int _spiralSpeed = 1;
int _width = 120;
int _ringOffset = 10;

int _getSpiralBrightness(int r, int i) {
  int ringOffset = _ringOffset * r;
  int targetAngle = (angle + ringOffset + 360) % 360;
  int pixelAngle = rings[r].angle[i];

  // Calculate distance from the current angle. If angle is near end
  // (360-width < a < 360), also check LEDs near beginning. If angle is near
  // beginning (0 < a < width), also check LEDs near end
  int dist = isBetween(targetAngle - pixelAngle, 0, _width)
                 ? targetAngle - pixelAngle
             : targetAngle > 360 - _width &&
                     isBetween(targetAngle - 360 - pixelAngle, 0, _width)
                 ? targetAngle - 360 - pixelAngle
             : targetAngle < _width &&
                     isBetween(targetAngle + 360 - pixelAngle, 0, _width)
                 ? targetAngle + 360 - pixelAngle
                 : 0;

  int b = map(dist, 0, _width, 0, 255);
  return b < 127 ? b * 2 : 255 - (2 * (b - 128));
}

void spiral() {
  for (int r = 0; r < NUM_RINGS; r++) {
    for (int i = 0; i < rings[r].numLEDs; i++) {
      int brightness = _getSpiralBrightness(r, i);
      rings[r].leds[i] = CHSV(HUE_BLUE, 100, brightness);
    }
  }

  // Increment the angle. After 360 degrees, start over at 0 degrees
  angle = (angle + _spiralSpeed + 360) % 360;
}
