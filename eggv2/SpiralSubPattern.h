struct TransitionRange {
  int16_t currentMin;
  int16_t targetMin;
  int16_t currentMax;
  int16_t targetMax;
  void transition() {
    // Min
    if (currentMin == targetMin) {
      return;
    } else if (currentMin < targetMin) {
      currentMin++;
    } else if (currentMin > targetMin) {
      currentMin--;
    }
    // Max
    if (currentMax == targetMax) {
      return;
    } else if (currentMax < targetMax) {
      currentMax++;
    } else if (currentMax > targetMax) {
      currentMax--;
    }
  }
};

class SpiralSubPattern : public SubPattern {
private:
  Spiral _spirals[MAX_SPIRALS];
  uint8_t _numSpirals = MAX_SPIRALS;
  uint8_t _activeSubPattern = 0;
  unsigned long _offsetWaveLength = 5000;
  unsigned long _speedWaveLength = 5000;
  unsigned long _widthWaveLength = 5000;
  unsigned long _targetOffsetWaveLength = 5000;
  unsigned long _targetSpeedWaveLength = 5000;
  unsigned long _targetWidthWaveLength = 5000;
  TransitionRange _offset = {0, 0, 360, 360};
  TransitionRange _width = {30, 30, 180, 180};
  TransitionRange _speed = {0, 0, 5, 5};

  void _showRandomOrganic() {
    //int16_t offset = sawtooth(0, 360, _offsetWaveLength);
    //int16_t width = sinwave(30, 180, _widthWaveLength);
    //int16_t speed = sinwave(0, 5, _speedWaveLength);
    int16_t offset = sawtooth(_offset.currentMin, _offset.currentMax, _offsetWaveLength);
    int16_t width = sinwave(_width.currentMin, _width.currentMax, _widthWaveLength);
    int16_t speed = sinwave(_speed.currentMin, _speed.currentMax, _speedWaveLength);
    Serial.println(offset);
    _spirals[0].setWidth(width);
    _spirals[0].setSpeed(speed);
    for (uint8_t i = 0; i < NUM_RINGS; i++) {
      _spirals[0].setRingOffset(i, i * offset);
    }
    _spirals[0].show();
  }

  void _showRubberBandWorm() {
    int16_t offset = sinwave(-90, 90, 500);
    int16_t width = sinwave(-180, 180, 500);
    int16_t speed = sinwave(1, 4, 400);

    for (uint8_t i = 0; i < NUM_RINGS; i++) {
      _spirals[0].setSpeed(speed);
      _spirals[0].setRingOffset(i, i * offset);
      _spirals[0].setWidth(abs(width));
    }
    _spirals[0].show();
  }

  void _showRubberBandNoAnchor() {
    int16_t angle = sinwave(0, 200, 400);
    int16_t offset = sinwave(-30, 30, 400);
    int16_t width = sinwave(-180, 180, 400);

    for (uint8_t i = 0; i < NUM_RINGS; i++) {
      _spirals[0].setAngle(angle);
      _spirals[0].setRingOffset(i, i * offset);
      _spirals[0].setWidth(abs(width));
    }
    _spirals[0].show();
  }

  void _showRubberBandAnchored() {
    int toMin = square(8, 0, 300);
    int toMax = square(0, 8, 300);

    // int16_t offset = sinwave(-360, 360, 100);
    // int16_t offset = sawtooth(-360, 360, 100); // swapping effect
    int16_t offset = cosSawtooth(-360, 360, 300);

    for (uint8_t i = 0; i < NUM_RINGS; i++) {
      int16_t ringOffset = mapf(i, toMin, toMax, 0, offset);
      _spirals[0].setRingOffset(i, ringOffset);
    }
    _spirals[0].show();
  }

  void _showGrowingSpirals() {
    unsigned long w = 300;  // waveLength
    unsigned long wo = 100; // waveLengthOffset
    _spirals[0].setHeightRangePercent(sawtooth(-50, 150, w, wo),
                                      sawtooth(-50, 150, w));
    _spirals[0].show();
    _spirals[1].setHeightRangePercent(sawtooth(-50, 150, w, wo * 2),
                                      sawtooth(-50, 150, w, wo));
    _spirals[1].show();
    _spirals[2].setHeightRangePercent(sawtooth(-50, 150, w, w),
                                      sawtooth(-50, 150, w, wo * 2));
    _spirals[2].show();
  }

  void _showBasicSpiralRotation() {
    _spirals[0].show();
    _spirals[1].show();
  }

  void _showContinuousSpiral() {
    unsigned long w = 10000; // waveLength
    // unsigned long wo = w * 3 / 4;  // waveLengthOffset
    int offset = sawtooth(0, 360, w);
    int16_t width = sinwave(30, 180,5000);//, w / 2, wo);
    // int16_t speed = sinwave(0, 5, w / 2, wo);
    _spirals[0].setWidth(width);
    for (uint8_t i = 0; i < NUM_RINGS; i++) {
      _spirals[0].setRingOffset(i, i * offset);
      //_spirals[0].setSpeed(speed);
    }
    _spirals[0].show();
  }

public:
  static const uint8_t RUBBER_BAND_WORM = 0;
  static const uint8_t RUBBER_BAND_NO_ANCHOR = 1;
  static const uint8_t RUBBER_BAND_ANCHORED = 2;
  static const uint8_t GROWING_SPIRALS = 3;
  static const uint8_t BASIC_SPIRAL_ROTATION = 4;
  static const uint8_t CONTINUOUS_SPIRAL = 5;
  static const uint8_t RANDOM_ORGANIC = 6;

  SpiralSubPattern(uint8_t activeSubPattern = 0) {
    _activeSubPattern = activeSubPattern;
    switch (_activeSubPattern) {
    case RUBBER_BAND_WORM:
      _numSpirals = 1;
      _spirals[0] = Spiral();
      break;
    case RUBBER_BAND_NO_ANCHOR:
      _numSpirals = 1;
      _spirals[0] = Spiral();
      _spirals[0].setSpeed(0);
      break;
    case RUBBER_BAND_ANCHORED:
      _numSpirals = 1;
      _spirals[0] = Spiral();
      _spirals[0].setAngle(0);
      _spirals[0].setSpeed(0);
      break;
    case GROWING_SPIRALS:
      _numSpirals = 3;
      for (int i = 0; i < _numSpirals; i++) {
        _spirals[i] = Spiral(i + 1);
        _spirals[i].setSpeed(0);
        _spirals[i].setAngle(i * 120);
        for (uint8_t j = 0; j < NUM_RINGS; j++) {
          _spirals[i].setRingOffset(j, j * 30);
        }
      }
      break;
    case BASIC_SPIRAL_ROTATION:
      _numSpirals = 2;
      _spirals[0] = Spiral(1);
      _spirals[1] = Spiral(2);
      _spirals[0].setSpeed(2);
      _spirals[1].setSpeed(-2);
      for (uint8_t i = 0; i < NUM_RINGS; i++) {
        _spirals[0].setRingOffset(i, (NUM_RINGS - 1 - i) * 30);
        _spirals[1].setRingOffset(i, i * 30);
      }
      break;
    case CONTINUOUS_SPIRAL:
      _numSpirals = 1;
      _spirals[0] = Spiral();
      _spirals[0].setSpeed(1);
      _spirals[0].setWidth(120);
      break;
    case RANDOM_ORGANIC:
      _numSpirals = 1;
      _spirals[0] = Spiral();
      break;
    default:
      break;
    }
  }

  void setTargetOffsetWaveLength(unsigned long waveLength) {
    _targetOffsetWaveLength = waveLength;
  }

  void setTargetWidthWaveLength(unsigned long waveLength) {
    _targetWidthWaveLength = waveLength;
  }

  void setTargetSpeedWaveLength(unsigned long waveLength) {
    _targetSpeedWaveLength = waveLength;
  }

  void transitionWaveLengths() {
    // offset
    if (_offsetWaveLength < _targetOffsetWaveLength) {
      _offsetWaveLength++;
    }
    if (_offsetWaveLength > _targetOffsetWaveLength) {
      _offsetWaveLength--;
    }

    // width
    if (_widthWaveLength < _targetWidthWaveLength) {
      _widthWaveLength++;
    }
    if (_widthWaveLength > _targetWidthWaveLength) {
      _widthWaveLength--;
    }

    // speed
    if (_speedWaveLength < _targetSpeedWaveLength) {
      _speedWaveLength++;
    }
    if (_speedWaveLength > _targetSpeedWaveLength) {
      _speedWaveLength--;
    }
  }

  void newOffsetRange() {
    int16_t v1 = random(0, 360);
    int16_t v2 = random(0, 360);
    _offset.targetMin = min(v1, v2);
    _offset.targetMax = max(v1, v2);
  }
  void newSpeedRange() {
    int16_t v1 = random(-2, 2);
    int16_t v2 = random(-2, 2);
    _speed.targetMin = min(v1, v2);
    _speed.targetMax = max(v1, v2);
  }
  void newWidthRange() {
    int16_t v1 = random(30, 180);
    int16_t v2 = random(30, 180);
    _width.targetMin = min(v1, v2);
    _width.targetMax = max(v1, v2);
  }

  virtual void show() {
    switch (_activeSubPattern) {
    case RUBBER_BAND_WORM:
      _showRubberBandWorm();
      break;
    case RUBBER_BAND_NO_ANCHOR:
      _showRubberBandNoAnchor();
      break;
    case RUBBER_BAND_ANCHORED:
      _showRubberBandAnchored();
      break;
    case GROWING_SPIRALS:
      _showGrowingSpirals();
      break;
    case BASIC_SPIRAL_ROTATION:
      _showBasicSpiralRotation();
      break;
    case CONTINUOUS_SPIRAL:
      _showContinuousSpiral();
      break;
    case RANDOM_ORGANIC:
      _showRandomOrganic();
      break;
    default:
      break;
    }
  }
};
