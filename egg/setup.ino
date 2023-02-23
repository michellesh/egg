void setupRotaryEncoders() {
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT);
}

void setupLEDs() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
}

void setupRings() {
  int offset = 0;
  for (int i = 0; i < NUM_RINGS; i++) {
    Ring ring = {i, ringNumLEDs[i], ringHeight[i], ringDiameter[i],
                 &leds[offset]};

    // Set the degree position 0-360 for each LED in this ring
    ring.deg = new float[ringNumLEDs[i]];
    float degreeStep = 360 / (float)ring.numLEDs;
    float degreeStart = i % 2 == 0 ? 0 : degreeStep / 2;
    //Serial.print("Ring ");
    //Serial.println(i);
    for (int j = 0; j < ring.numLEDs; j++) {
      ring.deg[j] = degreeStart + j * degreeStep;
      //Serial.print(ring.deg[j]);
      //Serial.print(" ");
    }
    //Serial.println();

    rings[i] = ring;
    offset += ring.numLEDs;
  }
}
