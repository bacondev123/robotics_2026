#include <ATX2.h>
int Ref_LL = 593;
int Ref_L = 573;

int Ref_R = 541;
int Ref_RR = 528;
int LL = analog(0);
int L = analog(1);

int R = analog(2);
int RR = analog(3);
void setup() {
  XIO();
  servo(1, 90);  // หมุนไปที่ 90 องศา
  OK();
  beep();
  delay(1000);
  glcdMode(2);
  glcdClear();
}
void loop(){
  // trackline_PID(20,8,0.02,3);
}
void Slide_Calibration() {
  // 1. Initialize Display
  glcdMode(0);
  glcdClear();
  setTextSize(1);


  // 2. Initialize Min/Max variables
  // Min starts high (4095), Max starts low (0)
  int min_LL = 4095, max_LL = 0;
  int min_L = 4095, max_L = 0;
  int min_R = 4095, max_R = 0;
  int min_RR = 4095, max_RR = 0;


  unsigned long timerStart;


  // 3. User Instruction
  glcdClear();
  glcd(0, 0, "Slide Robot...");


  // 4. Scanning Loop (5 Seconds)
  timerStart = millis();
  while (millis() - timerStart < 5000) {


    // Read current values into named variables
    int LL = analog(0);
    int L = analog(1);
    int R = analog(2);
    int RR = analog(3);


    // --- Update Sensors ---
    if (LL > max_LL) max_LL = LL;
    if (LL < min_LL) min_LL = LL;


    if (L > max_L) max_L = L;
    if (L < min_L) min_L = L;


    if (R > max_R) max_R = R;
    if (R < min_R) min_R = R;


    if (RR > max_RR) max_RR = RR;
    if (RR < min_RR) min_RR = RR;


    // Show countdown
    glcd(1, 0, "Wait: %d Sec", 5 - (millis() - timerStart) / 1000);
    delay(5);
  }


  // 5. Calculate Averages into the Global Reference Variables
  // Formula: (Minimum + Maximum) / 2
  Ref_LL = (min_LL + max_LL) / 2;
  Ref_L = (min_L + max_L) / 2;
  Ref_R = (min_R + max_R) / 2;
  Ref_RR = (min_RR + max_RR) / 2;


  // 6. Display Data
  beep();
  glcdClear();


  // Show Calculated References
  glcd(0, 0, "Reference: Value");
  glcd(1, 0, "Ref_LL:%d Ref_L :%d", Ref_LL, Ref_L);
  glcd(2, 0, "Ref_R :%d Ref_RR:%d", Ref_R, Ref_RR);


  // Show Min/Max ranges
  glcd(4, 0, "Raw: Min .. Max");
  glcd(5, 0, "LL : %d .. %d", min_LL, max_LL);
  glcd(6, 0, "L  : %d .. %d", min_L, max_L);
  glcd(7, 0, "R  : %d .. %d", min_R, max_R);
  glcd(8, 0, "RR : %d .. %d", min_RR, max_RR);


  sw_ok_press();
}
