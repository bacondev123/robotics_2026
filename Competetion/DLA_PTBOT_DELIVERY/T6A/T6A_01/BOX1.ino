// S 40 D 700 = 1Box
  // S 60 D 535 = 1Box
  // S 60 D 840 = 2Box
  // S 60 D 1220 = 3Box
  ///////--> motorTimeDegree_Enhanced( 30, 60, 840, 'L');
  // 1 Box = 250
  // 2 Box = 600
  // 3 Box = 950
  // 4 Box = 1250
  ///////--> motorTimeDegree_Enhanced( 30, 80, 840, 'L');
  // 1 Box = 200
  // 2 Box = 450
  // 3 Box = 700
  // 4 Box = 950
  ///////--> motorTimeBackDegree_Enhanced( 30, 60, 840, 'L');
  // --> เซ็ตหน้า/หลัง
  // --> 330
  // --> ตอนคีบแล้วจะถอยหลังมากลางบล็อก
  // --> -150
  // SetBack(20, 315);
  // SetFront(20, 315, 'L');
  // SetFront_Wall(20, 315, 'R');
void Box1()
{
//Box1
  motorTimeDegree_Enhanced( 30, 60, 950, 'R');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 920, 'R');SetBack(20, 315);
  pickCan(5, NO_SWITCH_LR);

  SetBack(20, 315, 'R');
  motorTimeDegree_Enhanced( 30, 60, 250, 'L');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 235, 'R');
  motorTimeDegree_Enhanced( 30, 60, 150);SetFront(20, 315, 'L');
  motorTimeDegree_Enhanced( 30, 60, 200, 'L');SetBack(20, 315, 'R');
  placeCan1_NoShake(10, 4, 'l', 'l');

  motorTimeDegree_Enhanced( -30, -60, 150, 'L');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 1250, 'L');
  motorTimeDegree_Enhanced( 30, 60, 250, 'R');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 265, 'L');
  motorTimeDegree_Enhanced( 30, 60, 200);SetFront_Wall(20, 315, 'R');
  placeCan1_NoShake(15, 4, 'r', 'r');delay(1000);

  SetBack(20, 315, 'R');
  motorTimeDegree_Enhanced( 30, 60, 250);SetFront(20, 315, 'L');
  pickCan(0, NO_SWITCH_LR);

  motorTimeDegree_Enhanced( -30, -60, 125, 'L');
  motorTimeDegree_Enhanced( 30, 60, 200);SetFront_Wall(20, 315, 'R');
  placeCan1_NoShake(15, 4, 'r', 'c');delay(1000);

  SetBack(20, 315, 'R');
  motorTimeDegree_Enhanced( 30, 60, 250, 'R');
  motorTimeDegree_Enhanced( 30, 60, 250, 'L');
  motorTimeDegree_Enhanced( 30, 60, 500);SetFront_Wall(20, 315, 'R');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 600, 'L');SetFront_Wall(20, 315, 'R');
  placeCan1_NoShake(5, 4, 'l', 'l');

  motorTimeDegree_Enhanced( -30, -60, 650);SetBack(20, 315, 'R');
  motorTimeDegree_Enhanced( 30, 60, 250, 'R');
  motorTimeDegree_Enhanced( 30, 60, 450);SetFront_Wall(20, 315, 'R');
  pickCan(5, NO_SWITCH_LR);

  SetBack(20, 315, 'R');
  SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 600, 'L');
  motorTimeDegree_Enhanced( 30, 60, 200);SetFront_Wall(20, 315, 'R');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 600, 'L');SetFront_Wall(20, 315, 'R');
  placeCan1_NoShake(5, 4, 'l', 'c');

  motorTimeDegree_Enhanced( -30, -60, 650);
  SetBack(20, 315, 'R');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 250, 'L');
  motorTimeDegree_Enhanced( 30, 60, 1200);SetFront(20, 315, 'L');
  placeCan1_NoShake(10, 4, 'r', 'c');

  motorTimeDegree_Enhanced( -30, -60, 300);SetBack(20, 315, 'L');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 230, 'L');
  motorTimeDegree_Enhanced( 30, 60, 250, 'L');
  motorTimeDegree_Enhanced( 30, 60, 450);SetFront_Wall(20, 315, 'L');SetBack(20, 315);
  motorTimeDegree_Enhanced( 30, 60, 950);
//-->> END
}