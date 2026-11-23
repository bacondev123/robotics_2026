void Operation() {
  // Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
}
void Mission_1() {
  skip_Line(1); // initial start
  spinRight_SkipLine(30,2,1);
  skip_Line(1);
  spinLeft_SkipLine(30,1,1);
  skip_Line(1);
  b2();
  fowardCross();
  fowardDelay(100);
  spinRight_SkipLine(30,2,1);
  skip_Line(1);
  keep_down();

  /* return base */

  spinRight_SkipLine(30,2,2);
  skip_Line(1);
  spinLeft_SkipLine(30,1,1);
  b2();
  fowardCross();
  spinRight_SkipLine(30,2,1);
  skip_Line(1);
  spinLeft_SkipLine(30,1,1);
  skip_Line(1);
  fowardCross();

  keep_up();
  backwardDelay(750);
  spinRight_Delay(900);
  spinRight_SkipLine(30,1,1);

}
void Mission_2() {
  skip_Line(1);
  spinLeft_SkipLine(30,1,1);
  skip_Line(1);
  spinRight_SkipLine(30,2,1);
  spinRight_Delay(300);
  b1();
}
void Mission_3() {
}
void Mission_4() {
}