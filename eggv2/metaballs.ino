#define NUM_BLOBS 2

struct Blob {
  float radius;
  float angle;
  float height;
  float speedHorizontal;
  float speedVertical;

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

Blob b = {20, 180, 50, 0.5, 0.5};
Blob b2 = {20, 90, 100, 0.5, 0.5};
Blob blobs[NUM_BLOBS] = {b, b2};

void metaballs() {
  for (int r = 0; r < NUM_RINGS; r++) {
    for (int i = 0; i < rings[r].numLEDs; i++) {

      int sum = 0;
      float dist;

      for (int k = 0; k < NUM_BLOBS; k++) {
        dist = distance(rings[r].angle[i], rings[r].height, blobs[k].angle,
                        blobs[k].height);
        sum += 100 * blobs[k].radius / dist;
      }

      sum = constrain(sum, 0, 255);
      rings[r].leds[i] = CHSV(HUE_BLUE, 100, sum);
    }
  }
  blobs[0].update();
  blobs[1].update();
}
