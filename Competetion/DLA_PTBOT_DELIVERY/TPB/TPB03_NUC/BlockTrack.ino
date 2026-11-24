//spd 40 timer 2280 for bridge


//Before Place\
Set Front or Back and then use delay and spinDegree

//AfterPlace\
- spd60 & 180ms to middle block\
- delay
void test() {
  // PickCanTest(0);
  SetBack(25,200);
  SetBack(25,300,'L');
  autoPickCan(5);
  // SetFront(25,420,'L');//Red
  // SetFront(25,420,'L');//green
  // SetArm();
  // delay(200);
  // autoPlaceCan(5);
}

void Quest1() {
  //Edit Here
  setAngleOffset();
  current_degree = 0;
  SetBack(25,300);
  SetBack(25,300,'L');
  delay(150);
  SetArm();
  //Edit Pick
  autoPickCan(5);
  Diy();
  lift(3);
  SetArm();
  SetBack(25,350,'R');
  SetFront(25,200);
  SetFront(25,510,'L');
  autoPlaceCan(5);
  // PickCanTest(0);
  /*25/7/2025*/
  //SetFront(25,500,'L'); //Green
  // SetFront(25,420,'L'); //Yellow
  // SetFront(25,390,'R'); //Red
}
void reBlock2() {
  //Edit Here
  //go yellow//
  SetBack(25, 320);
  spinDegree(90);
  MoveBlock40(1);
  pickcan(5, 2);
  BB(60, 450);
  delay(500);
  spinDegree(90);
  SetWall();
  SetFront(25, 450);
  SetArm();
  spinDegree(-90);
  MoveBlock60(1);
  spinDegree(90);
  SetWall();
  SetFront(25, 200);
  SetFront(25, 420, 'L');  //Yellow
  SetArm();
  delay(200);
  autoPlaceCan(10);
}
void reBlock3() {
  BackBlock60(1);
  BB(60, 100);
  spinDegree(-90);
  SetBack(25, 320);
  MoveBlock60(1);
  spinDegree(-90);
  MoveBlock60(1);
  spinDegree(90);
  SetBack(25, 350);
  MoveBlock60(1);
  spinDegree(90);
  SetWall();
  SetFront(25, 200);
  SetFront(25, 400, 'R');
  MoveBlock40(1);
  SetFront(25, 200);
  SetFront(25, 350, 'R');
  SetArm();
  autoPickCan(0);
  BackBlock60(1);
  BB(60, 380);
  spinDegree(-90);
  SetWall();
  SetFront(25, 200);
  SetFront(25, 420, 'R');
  MoveBlock60(1);
  spinDegree(-90);
  SetWall();
  SetFront(25, 200);
  SetFront(25, 390, 'R');  //Red
  SetArm();
  delay(200);
  autoPlaceCan(15);
}
void Block1_1() {
  //Edit Here
  setAngleOffset();
  current_degree = 0;
  KeepArm();
  delay(150);
  SetBack(25, 300);
  MoveBlock60(2);
  spinDegree(90);
  SetBack(25, 350);
  spinDegree(-90);
  //Edit Pick
  pickcan(5, 1);
  BB(25, 620);
  spinDegree(90);
  SetBack(25, 320);
  spinDegree(90);
  MoveBlock60(1);
  spinDegree(90);
  MoveBlock60(1);
  spinDegree(90);
  MoveBlock60(1);
  spinDegree(90);
  // PickCanTest(0);
  SetWall();
  SetFront(25, 200);
  //SetFront(25,460,'L'); //Green //480สีไม่ซ้ำ
  SetFront(25, 420, 'L');
  // SetFront(25,420,'L'); //Yellow
  // SetFront(25,390,'R'); //Red
  SetArm();
  delay(200);
  autoPlaceCan(5);
}
void Block1_2() {
  //Edit Here
  //go yellow//
  SetBack(25, 320);
  spinDegree(90);
  MoveBlock60(1);
  pickcan(5, 2);
  BB(60, 450);
  spinDegree(90);
  SetWall();
  SetFront(25, 500);
  SetArm();
  spinDegree(-90);
  MoveBlock60(1);
  spinDegree(90);
  SetWall();
  SetFront(25, 200);
  SetFront(25, 420, 'L');  //Yellow
  SetArm();
  delay(200);
  autoPlaceCan(10);
  //Edit Place
  //autoPlaceCan(10);
}
void Block1_3() {
  BB(25, 300);
  BackBlock60(1);
  spinDegree(-90);
  SetBack(25, 320);
  MoveBlock60(1);
  spinDegree(-90);
  MoveBlock60(1);
  pickcan(0, 3);
  BackBlock60(1);
  spinDegree(-90);
  SetWall();
  SetFront(25, 200);
  SetFront(25, 420, 'R');
  FF(60, 400);
  spinDegree(-90);
}
void BlockCK1() {
}
void BlockCK2() {
}
void Block2_1() {
  //Edit Here
  delay(500);
  KeepArm();
  BB(40, 150);
  BackBlock40(1, 'R');
  MoveBlock40(1, 'L');
  SetBack(25, 400);
  MoveBlock60(1, 'L');
  SetWall();
  SetFront(25, 400, 'R');
  SetArm();
  delay(100);

  //Edit Pick
  pickcan(5, 2);
}

void Block2_2() {
  //Edit Here
  //go red//
  delay(300);
  BB(40, 450);
  BackBlock40(1);
  SetBack(25, 100);
  delay(100);
  SetBack(25, 400, 'L');
  MoveBlock40(1);
  SetWall();
  SetFront(25, 100);
  SetFront(25, 370, 'L');
  SetArm();
  //Edit Place
  autoPlaceCan(15);
}
void Block3_1() {
  //Edit Here
  //
  delay(1000);
  KeepArm();
  BB(40, 150, 'L');
  MoveBlock60(3);
  SetWall();
  SetFront(25, 350, 'L');
  SetArm();
  MoveBlock40(1, 'R');
  SetWall();
  SetFront(25, 350, 'L');
  SetArm();
  delay(100);

  // Edit Pick
  pickcan(5, 3);
  //
}

void Block3_2() {
  //Edit Here
  //go red//
  delay(500);
  BB(40, 450);
  BackBlock40(1, 'R');
  SetWall();
  SetFront(25, 350, 'R');
  MoveBlock40(1);
  SetWall();
  SetFront(25, 100);
  delay(100);
  SetFront(25, 350, 'R');
  SetArm();
  //edit pick
  autoPlaceCan(5);
}

void Finish() {
  //Retry but all can is place
  MoveBlock(1);
  delay(50);
  BackBlock(1);
  for (int i = 0; i <= 2; i++) {
    beep(100);
    delay(50);
  }
}
void BlockFinish() {
  //Edit Here
  delay(200);
  KeepArm();
  BB(40, 150, 'R');
  MoveBlock40(1, 'L');
  MoveBlock60(3);
  //beep when Finish
  for (int i = 0; i <= 9; i++) {
    beep(100);
    delay(50);
  }
}

void FullMap() {
  Block1_1();
  Block1_2();
  //
  // BlockCK1();
  // BlockCK2();
  //
  Block2_1();
  Block2_2();
  //
  Block3_1();
  Block3_2();
  // Finish();
  //
  BlockFinish();
}
void ReTry2() {
  setAngleOffset();
  current_degree = 0;
  KeepArm();
  lift(2);
  MoveBlock(3);
  SetWall();
  SetFront(25, 330, 'R');
  SetArm();
  KeepArm();
  MoveBlock(2);
  SetFront(25, 420, 'L');
  BB(60, 490, 'L');
  MoveBlock(1, 'L');
  MoveBlock(1, 'R');
  BB(40, 1200, 'L');  //Bridge//
  SetFront(25, 350);
  BB(40, 1200, 'L');
  MoveBlock(2);
  SetFront(25, 350, 'L');
  SetWall();
  SetFront(25, 350);
  SetArm();
  BackBlock(2, 'R');
  MoveBlock(1, 'L');
  BackBlock(1);
  MoveBlock(1);
  SetFront(25, 440, 'R');
  SetWall();
  SetFront(25, 350, 'R');
  pickcan(5, 2);
  delay(200);


  //contunue with this//
  Block2_2();
  Block3_1();
  Block3_2();
  BlockFinish();
}
void ReTry3() {
  setAngleOffset();
  current_degree = 0;
  KeepArm();
  lift(2);
  MoveBlock(3);
  SetWall();
  SetFront(25, 330, 'R');
  SetArm();
  KeepArm();
  MoveBlock(2);
  SetFront(25, 420, 'L');
  BB(60, 490, 'L');
  MoveBlock(1, 'L');
  MoveBlock(1, 'R');
  BB(40, 1200, 'L');  //Bridge//
  SetFront(25, 350);
  BB(40, 1200, 'L');
  MoveBlock(2);
  SetFront(25, 350, 'R');
  MoveBlock(2);
  SetWall();
  SetFront(25, 350, 'R');
  SetBack(25, 350);
  SetArm();
  MoveBlock(2, 'L');
  SetWall();
  delay(300);
  SetFront(25, 200);
  delay(100);
  SetFront(25, 320);
  SetArm();
  delay(400);
  spinDegree(90);
  delay(400);


  // Edit Pick
  pickcan(0, 3);


  //continue with this//
  Block3_2();
  BlockFinish();
}
