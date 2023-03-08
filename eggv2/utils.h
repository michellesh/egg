float mapf(float value, float inMin, float inMax, float outMin, float outMax) {
  float percentage = (value - inMin) / (inMax - inMin);
  return outMin + (outMax - outMin) * percentage;
}

float distance(float x1, float y1, float x2, float y2) {
  return (float)sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

bool isBetween(int16_t value, int16_t min, int16_t max,
               bool inclusive = false) {
  return inclusive ? value >= min && value <= max : value > min && value < max;
}

float sinwave(float minValue, float maxValue, unsigned long waveLength = 50,
              unsigned long waveLengthOffset = 0) {
  return mapf(sin((float)(ticks + waveLengthOffset) * PI / waveLength), -1, 1,
              minValue, maxValue);
}

float sawtooth(float minValue, float maxValue, unsigned long waveLength = 50,
               unsigned long waveLengthOffset = 0) {
  float t = (float)(ticks + waveLengthOffset) / waveLength;
  return mapf(t - floor(t), 0, 1, minValue, maxValue);
}
