const byte SEG_A = 2;
const byte SEG_B = 3;
const byte SEG_C = 4;
const byte SEG_D = 5;
const byte SEG_E = 6;
const byte SEG_F = 7;
const byte SEG_G = 8;
const byte SEG_DP = 9;
const byte DIGIT_1 = 10;
const byte DIGIT_2 = 11;
const byte DIGIT_3 = 12;
const byte DIGIT_4 = 13;
const byte DIGIT_5 = 14;
const byte DIGIT_ALL_OFF= 0;

const byte SEG_ON = 0;
const byte SEG_OFF = 1;
const byte DIGIT_ON = 0;
const byte DIGIT_OFF = 1;
const byte SEG_PATTERN_OFF= 0;

const byte SCAN_DELAY= 500;

static byte cnt= 0;
static byte show= 0;

void display_SetupDigit(byte digitPin) {
  pinMode(digitPin, OUTPUT);
  digitalWrite(digitPin, DIGIT_OFF);
}

void display_SetupSegment(byte segmentPin) {
  pinMode(segmentPin, OUTPUT);
  digitalWrite(segmentPin, SEG_OFF);
}

void display_Setup() {
  display_SetupDigit(DIGIT_1);
  display_SetupDigit(DIGIT_2);
  display_SetupDigit(DIGIT_3);
  display_SetupDigit(DIGIT_4);
  display_SetupDigit(DIGIT_5);
  
  display_SetupSegment(SEG_A);
  display_SetupSegment(SEG_B);
  display_SetupSegment(SEG_C);
  display_SetupSegment(SEG_D);
  display_SetupSegment(SEG_E);
  display_SetupSegment(SEG_F);
  display_SetupSegment(SEG_G);
  display_SetupSegment(SEG_DP);
}

void display_DigitOn(byte digitPin) {
  digitalWrite(DIGIT_1, digitPin == DIGIT_1 ? DIGIT_ON : DIGIT_OFF);
  digitalWrite(DIGIT_2, digitPin == DIGIT_2 ? DIGIT_ON : DIGIT_OFF);
  digitalWrite(DIGIT_3, digitPin == DIGIT_3 ? DIGIT_ON : DIGIT_OFF);
  digitalWrite(DIGIT_4, digitPin == DIGIT_4 ? DIGIT_ON : DIGIT_OFF);
  digitalWrite(DIGIT_5, digitPin == DIGIT_5 ? DIGIT_ON : DIGIT_OFF);
}

void display_SetSegments(byte pattern) {
  digitalWrite(SEG_A, pattern & 0x01 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_B, pattern & 0x02 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_C, pattern & 0x04 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_D, pattern & 0x08 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_E, pattern & 0x10 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_F, pattern & 0x20 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_G, pattern & 0x40 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_DP, pattern & 0x80 ? SEG_ON : SEG_OFF);
}

void display_Refresh(byte pattern) {
  display_SetSegments(SEG_PATTERN_OFF);
  display_DigitOn(DIGIT_1);
  display_SetSegments(pattern);
  delay(SCAN_DELAY);

  display_SetSegments(SEG_PATTERN_OFF);
  display_DigitOn(DIGIT_2);
  display_SetSegments(pattern);
  delay(SCAN_DELAY);

  display_SetSegments(SEG_PATTERN_OFF);
  display_DigitOn(DIGIT_3);
  display_SetSegments(pattern);
  delay(SCAN_DELAY);

  display_SetSegments(SEG_PATTERN_OFF);
  display_DigitOn(DIGIT_4);
  display_SetSegments(pattern);
  delay(SCAN_DELAY);

}

void setup() {
  display_Setup();
}

void loop() {
  display_Refresh(show);
  cnt++;
  
  //if(cnt > 50) {
    cnt= 0;
    //show++;
  //}
}
