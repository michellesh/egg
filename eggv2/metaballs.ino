struct Blob {
  float radius;
  float angle;
  float height;
  int speedHorizontal;
  int speedVertical;

  void update() {
    angle += speedHorizontal;
    height += speedVertical;
    if (angle > 360 || angle < 0) {
      speedHorizontal *= -1;
    }
    if (height > MAX_RING_HEIGHT || angle < 0) {
      speedVertical *= -1;
    }
  }
};

Blob b = {20, 180, 50, 1, 1};
Blob b2 = {20, 90, 100, 1, 1};

void metaballs() {
  for (int r = 0; r < NUM_RINGS; r++) {
    for (int i = 0; i < rings[r].numLEDs; i++) {
      float dist =
          distance(rings[r].angle[i], rings[r].height, b.angle, b.height);
      float dist2 =
          distance(rings[r].angle[i], rings[r].height, b2.angle, b2.height);
      int brightness = 100 * b.radius / dist;
      brightness += 100 * b2.radius / dist2;
      brightness = constrain(brightness, 0, 255);
      rings[r].leds[i] = CHSV(HUE_BLUE, 100, brightness);
    }
  }
  b.update();
  b2.update();
}
