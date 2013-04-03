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

const byte SEG_PATTERN_DASH = 0x0A;
const byte SEG_PATTERN_H = 0x0B;
const byte SEG_PATTERN_L = 0x0C;
const byte SEG_PATTERN_C = 0x0D;
const byte SEG_PATTERN_F = 0x0E;
const byte SEG_PATTERN_OFF= 0x0F;
const byte segmentPatterns[16]= {
  0x3F,  // 0
  0x03,  // 1
  0x6D,  // 2
  0x67,  // 3
  0x53,  // 4
  0x76,  // 5
  0x7E,  // 6
  0x23,  // 7
  0x7F,  // 8
  0x77,  // 9
  0x40,  // -
  0x5B,  // H
  0x1C,  // L
  0x3c,  // C
  0x78,  // F
  0x00   // SEG_ALL_OFF
};

static byte digitPatterns[4];
static byte cnt;
static int show;

void display_SetupDigit(byte segmentPin) {
  pinMode(segmentPin, OUTPUT);
  digitalWrite(segmentPin, DIGIT_OFF);
}

void display_SetupSegment(byte digitPin) {
  pinMode(digitPin, OUTPUT);
  digitalWrite(digitPin, SEG_OFF);
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
  pattern &= 15;
  digitalWrite(SEG_A, segmentPatterns[pattern] & 0x01 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_B, segmentPatterns[pattern] & 0x02 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_C, segmentPatterns[pattern] & 0x04 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_D, segmentPatterns[pattern] & 0x08 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_E, segmentPatterns[pattern] & 0x10 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_F, segmentPatterns[pattern] & 0x20 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_G, segmentPatterns[pattern] & 0x40 ? SEG_ON : SEG_OFF);
  //digitalWrite(SEG_DP, segmentPatterns[pattern] & 0x80 ? SEG_ON : SEG_OFF);
  digitalWrite(SEG_DP, cnt == 0 ? SEG_ON : SEG_OFF);
}

void display_Refresh() {
  display_SetSegments(SEG_PATTERN_OFF);
  display_DigitOn(DIGIT_1);
  display_SetSegments(digitPatterns[0]);

  display_SetSegments(SEG_PATTERN_OFF);
  display_DigitOn(DIGIT_2);
  display_SetSegments(digitPatterns[1]);

  display_SetSegments(SEG_PATTERN_OFF);
  display_DigitOn(DIGIT_3);
  display_SetSegments(digitPatterns[2]);

  display_SetSegments(SEG_PATTERN_OFF);
  display_DigitOn(DIGIT_4);
  display_SetSegments(digitPatterns[3]);
}

void display_Show(int value) {
  if ((value < 0) || (value > 9999)) return;
  
  bool leadingZero;
  byte placeValue;
  
  placeValue= value / 1000;
  leadingZero= (placeValue == 0);
  digitPatterns[0]= leadingZero ? SEG_PATTERN_OFF : placeValue;
  value -= placeValue*1000;
  
  placeValue= value / 100;
  leadingZero &= (placeValue == 0);
  digitPatterns[1]= leadingZero ? SEG_PATTERN_OFF : placeValue;
  value -= placeValue*100;

  placeValue= value / 10;
  leadingZero &= (placeValue == 0);
  digitPatterns[2]= leadingZero ? SEG_PATTERN_OFF : placeValue;
  value -= placeValue*10;

  digitPatterns[3]= value;
}

void setup() {
  display_Setup();
}

void loop() {
  display_Refresh();
  cnt++;
  
  if(cnt > 100) {
    cnt= 0;
    show++;
    display_Show(show);
  }
}
