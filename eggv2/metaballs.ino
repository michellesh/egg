#define NUM_BLOBS 15

struct Blob {
  int brightness;
  float size;
  float angle;
  float height;
  float speedHorizontal;
  float speedVertical;

  void reset() {
    brightness = 0;
    size = random(30, 50);
    angle = random(0, 360);
    height = random(0, MAX_RING_HEIGHT);

    speedVertical = _randomBlobSpeed();
    speedHorizontal = _randomBlobSpeed();
  }

  float _randomBlobSpeed() {
    bool reverse = random(0, 1);
    float speed = float(random(3, 7)) / 10;
    return reverse ? speed * -1 : speed;
  }

  void update() {
    brightness = constrain(brightness + 1, 0, 255);

    angle = int(angle + speedHorizontal + 360) % 360;

    height += speedVertical;
    if (height > size + MAX_RING_HEIGHT || height < -size) {
      reset();
    }
  }
};

Blob blobs[NUM_BLOBS];

void setupBlobs() {
  for (int k = 0; k < NUM_BLOBS; k++) {
    Blob b;
    b.reset();
    b.brightness = 255;
    blobs[k] = b;
  }
}

void metaballs() {
  for (int r = 0; r < NUM_RINGS; r++) {
    for (int i = 0; i < rings[r].numLEDs; i++) {

      int sum = 0;
      float dist;

      for (int k = 0; k < NUM_BLOBS; k++) {
        // TODO need to also check angles that wrap all the way around 360
        dist = distance(rings[r].angle[i], rings[r].height, blobs[k].angle,
                        blobs[k].height);
        if (dist < blobs[k].size) {
          int b = map(dist, 0, blobs[k].size, 255, 0);
          sum += constrain(b, 0, blobs[k].brightness);
        }
      }

      sum = constrain(sum, 0, 255);
      rings[r].leds[i] = CHSV(HUE_BLUE, 100, sum);
    }
  }

  for (int k = 0; k < NUM_BLOBS; k++) {
    blobs[k].update();
  }

  EVERY_N_MILLISECONDS(500) {
    Serial.print(blobs[0].angle);
    Serial.print(" ");
    Serial.print(blobs[0].height);
    Serial.println();
  }
}
