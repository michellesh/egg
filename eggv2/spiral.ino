#define NUM_SPIRALS 1

struct TestSpiral {
  int spiralSpeed;
  int width;
  int ringOffset;
  int angle;

  void update() {
    // Increment the angle. After 360 degrees, start over at 0 degrees
    angle = (angle + spiralSpeed + 360) % 360;
  }

  int getBrightness(int ringIndex, int pixelIndex) {
    int _ringOffset = ringOffset * ringIndex;
    int targetAngle = (angle + _ringOffset + 360) % 360;
    int pixelAngle = rings[ringIndex].angle[pixelIndex];

    // Calculate distance from the current angle. If angle is near end
    // (360-width < a < 360), also check LEDs near beginning. If angle is near
    // beginning (0 < a < width), also check LEDs near end
    int dist = isBetween(targetAngle - pixelAngle, 0, width)
                   ? targetAngle - pixelAngle
               : targetAngle > 360 - width &&
                       isBetween(targetAngle - 360 - pixelAngle, 0, width)
                   ? targetAngle - 360 - pixelAngle
               : targetAngle < width &&
                       isBetween(targetAngle + 360 - pixelAngle, 0, width)
                   ? targetAngle + 360 - pixelAngle
                   : 0;

    int b = map(dist, 0, width, 0, 255);
    return b < 127 ? b * 2 : 255 - (2 * (b - 128));
  }
};

TestSpiral spirals[NUM_SPIRALS];

void setupSpirals() {
  for (int i = 0; i < NUM_SPIRALS; i++) {
    spirals[i] = {1, 120, 40, 360 / NUM_SPIRALS * i};
  }
}

void spiral(int sinRingOffset) {

  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < rings[i].numLEDs; j++) {
      int sum = 0;
      CRGB color;
      for (int k = 0; k < NUM_SPIRALS; k++) {
        spirals[k].ringOffset = sinRingOffset;
        int brightness = spirals[k].getBrightness(i, j);
        sum += brightness;
        CRGB spiralColor = palette.mapToColor(k, 0, NUM_SPIRALS);
        color = brightness > 0 ? spiralColor : color;
      }
      sum = constrain(sum, 0, 255);
      rings[i].leds[j] = color.nscale8(sum);
    }
  }

  for (int i = 0; i < NUM_SPIRALS; i++) {
    spirals[i].update();
  }
}
