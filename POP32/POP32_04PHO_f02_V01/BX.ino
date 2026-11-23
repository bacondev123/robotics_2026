void b1_legacy() {
  fowardDelay(925);
  delay(300);
  spinLeft_SkipLine(30, 1, 1);
  // waitSW_OK();
  spinLeft_SkipLine(30, 2, 1);
  delay(300);
  fowardDelay(1000);
  delay(300);
  spinRight_SkipLine(30, 2, 1);
  delay(300);
  fowardDelay(800);
  delay(300);
  spinRight_SkipLine(30, 1, 1);
  track_jc(20);


  fowardDelay(1000);
  delay(300);
  spinLeft_Delay(800);
  waitSW_OK();

  delay(300);
  fowardDelay(950);
  waitSW_OK();
  spinLeft_Delay(200);
  spinLeft_SkipLine(30, 1, 0);

  delay(300);
  fowardDelay(900);
  delay(300);
  waitSW_OK();
  spinRight_SkipLine(30, 1, 1);

  delay(300);
  skip_Line(1);
}
void b1() {
  trackPD_Cross(16, 12, 2.75);
}
void b2() {
  trackPD_Cross(18, 13, 2.5);
}
void b3() {
  trackPD_Cross(20, 8, 3);
}
void b4() {
}
void b512() {
  trackPD_Time(16, 6, 2, 1500);
  // waitSW_OK();
  fowardCross();
  delay(1000);
  spinLeft_SkipLine(30, 2, 1);
  // trackPDLeft_Time(16,8,2,100);
  fowardCross();
}
void b513() {
  trackPD_Time(16, 6, 2, 1500);
  fowardCross();
  delay(1000);
  spinRight_SkipLine(30, 2, 1);
  trackPD_Time(16, 8.5, 2, 2000);
}
void b532() {
  trackPD_Time(16, 6, 2, 1500);
  // waitSW_OK();
  fowardCross();
  delay(1000);
  spinRight_SkipLine(30, 2, 1);
  fowardCross();
}
void b531() {
  trackPD_Time(16, 6, 2, 1500);
  fowardCross();
  delay(1000);
  spinLeft_SkipLine(30, 2, 1);
  trackPD_Time(16, 8.5, 2, 2000);
}
void b612() {
  // skip_Line(1);
  // trackPD_Time(20,12,3,2000);
  trackPDLeft_Time(20, 12, 3, 1250);
}

void b623() {
  trackPDLeft_Time(20, 12, 3, 1250);
}
void b634() {
  trackPDLeft_Time(20, 12, 3, 1250);
}
void b641() {
  trackPDLeft_Time(20, 12, 3, 1250);
}
void b613() {
  // trackPDLeft_Time(20, 12, 3, 500, 20, 0, 0.3, 0.4);
  trackPDLeft_Time(20, 12, 3, 750, 5);
  // waitSW_OK();
  trackPDRight_Time(20, 12, 3, 750, 5);
  trackPDLeft_Time(20, 12, 3, 750, 5);
}
void b624() {
  // trackPDLeft_Time(20, 12, 3, 500, 20, 0, 0.3, 0.4);
  trackPDLeft_Time(20, 12, 3, 750, 5);
  trackPDRight_Time(20, 12, 3, 750, 5);
  trackPDLeft_Time(20, 12, 3, 750, 5);
}
void b631() {
  // trackPDLeft_Time(20, 12, 3, 500, 20, 0, 0.3, 0.4);
  trackPDLeft_Time(20, 12, 3, 750, 5);
  trackPDRight_Time(20, 12, 3, 750, 5);
  trackPDLeft_Time(20, 12, 3, 750, 5);
}
void b642() {
  // trackPDLeft_Time(20, 12, 3, 500, 20, 0, 0.3, 0.4);
  trackPDLeft_Time(20, 12, 3, 750, 5);
  trackPDRight_Time(20, 12, 3, 750, 5);
  trackPDLeft_Time(20, 12, 3, 750, 5);
}
void b614() {
  trackPDRight_Time(20, 12, 3, 1250);
}
void b621() {
  trackPDRight_Time(20, 12, 3, 1250);
}
void b632() {
  trackPDRight_Time(20, 12, 3, 1250);
}
void b643() {
  trackPDRight_Time(20, 12, 3, 1250);
}

void b712() {
  trackPDLeft_Time(20, 12, 3, 1000, 5);
}
void b723() {
  trackPDLeft_Time(20, 12, 3, 1000, 5);
}
void b734() {
  trackPDLeft_Time(20, 12, 3, 1000, 5);
}
void b741() {
  trackPDLeft_Time(20, 12, 3, 1000, 5);
}
void b713() { // in experiment
  trackPDLeft_Time(20, 12, 3, 750, 5);
  // delay(500);
  trackPDRight_Time(12, 6, 1.5, 750, 25, 0, 0.5, 0.2);
}