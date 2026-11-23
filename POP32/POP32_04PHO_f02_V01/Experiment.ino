void Experiment() {
  Lab_01();
  // Lab_02();
  // Lab_03();
  // Lab_04();
}
void Lab_01() {
  trackPD(20,8,0);
  trackPD_Time(20,8,2,2500);
  b1();
  // waitSW_OK();
  // b2();
  // b3();
  // waitSW_OK();
}

void Lab_02() {
  // b2();
  b1();
}
void Lab_03() {
  // b2();
  // delay(500);
  // fowardCross();
  // spinLeft_SkipLine(30,1,1);
  // b512();
  // b513();
  // waitSW_OK();
  // b531()
  // b612();
  // waitSW_OK();
  // b614();
  // b613();
  // waitSW_OK();
  // b712();
  b713();
}
void Lab_04() {
}
void Motor_tuning(float L, float R) {
  fd2(L, R);
  delay(1000);
  ao();
}


void test_servo() {
  while (1) {
    oled.text(1, 0, "Knob= %d ", knob(0, 180));
    oled.show();
    servo(1, knob(0, 180));  // servo หมุนไปที่ knob องศา
  }
}