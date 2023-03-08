#define MAX_SPIRALS 3

class SpiralSubPattern : public SubPattern {
private:
  Spiral _spirals[MAX_SPIRALS];
  uint8_t _numSpirals = MAX_SPIRALS;
  uint8_t _activeSubPattern = 0;

  void _showContinuousSpiral() {
    unsigned long w = 1000;         // waveLength
    //unsigned long wo = w * 3 / 4;  // waveLengthOffset
    int offset = sawtooth(0, 360, w);
    //int16_t width = sinwave(30, 180, w / 2, wo);
    //int16_t speed = sinwave(0, 5, w / 2, wo);
    for (uint8_t i = 0; i < NUM_RINGS; i++) {
      _spirals[0].setRingOffset(i, i * offset);
      //_spirals[0].setWidth(width);
      //_spirals[0].setSpeed(speed);
    }
    _spirals[0].show();
  }

public:
  //static const uint8_t RUBBER_BAND_WORM = 0;
  //static const uint8_t RUBBER_BAND_NO_ANCHOR = 1;
  //static const uint8_t RUBBER_BAND_ANCHORED = 2;
  //static const uint8_t GROWING_SPIRALS = 3;
  //static const uint8_t BASIC_SPIRAL_ROTATION = 4;
  static const uint8_t CONTINUOUS_SPIRAL = 5;

  SpiralSubPattern(uint8_t activeSubPattern = 0) {
    _activeSubPattern = activeSubPattern;
    switch (_activeSubPattern) {
    case CONTINUOUS_SPIRAL:
      _numSpirals = 1;
      _spirals[0] = Spiral();
      _spirals[0].setSpeed(1);
      _spirals[0].setWidth(120);
      break;
    default:
      break;
    }
  }

  virtual void show() {
    switch (_activeSubPattern) {
    case CONTINUOUS_SPIRAL:
      _showContinuousSpiral();
      break;
    default:
      break;
    }
  }
};
