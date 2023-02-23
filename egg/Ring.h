// number of LEDs in each ring
int ringNumLEDs[] = {7, 11, 15, 19, 21, 23, 25, 25, 25, 25, 23, 19, 15};

// height (z index) of each ring
// float ringHeight[] = {119.978,  110.52,  98.0201, 83.8016, 68.496,
//                      52.4351,  35.8279, 18.9098, 1.91173, -14.8137,
//                      -30.7232, -45.036, -56.8221};
float ringHeight[] = {176.8, 167.3, 154.8, 140.6, 125.3, 109.3, 92.7,
                      75.7,  58.7,  42.1,  26.1,  11.8,  0};

// diameter of each ring
float ringDiameter[] = {33.0401,  61.2911,  84.3618,  102.988, 117.7806,
                        128.9127, 136.2106, 139.6347, 138.668, 132.5939,
                        120.6395, 102.3022, 77.7783};

struct Ring {
  int ringIndex;
  int numLEDs;
  float height;
  float diameter;

  CRGB *leds; // array of LEDs in this ring
  float *deg; // array of LEDs positions around the ring in degrees
};
