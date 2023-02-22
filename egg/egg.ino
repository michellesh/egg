#define ENCODER_CLK 5 // D1
#define ENCODER_DT 4  // D2
#define ENCODER_SW 0  // D3
#define MAX_CLICKS 40

int angle = 0;
int clicks = 0;
int currentCLK;
int prevCLK;
int currentSW = 0;
int prevSW = 0;

void setup() {
  Serial.begin(9600);

  // Set rotary encoder pins as inputs
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT);

  // Read the initial state of ENCODER_CLK and ENCODER_SW
  prevCLK = digitalRead(ENCODER_CLK);
  prevSW = digitalRead(ENCODER_SW);
}

void loop() {
  // Read the current state of ENCODER_CLK and ENCODER_SW
  currentCLK = digitalRead(ENCODER_CLK);
  currentSW = digitalRead(ENCODER_SW);

  if (currentSW == LOW && prevSW == HIGH) {
    Serial.println("Button pressed!");
  }

  // A pulse occurs if the previous and the current state differ
  if (currentCLK != prevCLK) {
    if (digitalRead(ENCODER_DT) != currentCLK) {
      clicks++;
      if (clicks >= MAX_CLICKS) {
        clicks = 0;
      }
    } else {
      clicks--;
      if (clicks < 0) {
        clicks = MAX_CLICKS;
      }
    }

    // Set the rotation angle, a value from 0-360 degrees
    angle = map(clicks, 0, MAX_CLICKS, 0, 360);

    if (currentSW == LOW) {
      Serial.print("ON! ");
    } else {
      Serial.print("OFF ");
    }
    Serial.println(angle);
  }

  prevCLK = currentCLK;
  prevSW = currentSW;
}
