//spd 40 timer 2280 for bridge
// _1 = Get, _2 = Place
//Before Place\
Set Front or Back and then use delay and spinDegree

//AfterPlace\
- spd60 & 180ms to middle block\
- delay

void NBlock1_1() {
  lift(2);
  KeepArm();
  MoveBlock(3);
  SetWall(); SetFront(25,330,'R');
  KeepArm();
  MoveBlock(2);
  SetFront(25,430,'L');
  BackBlock60(0.8, 'L');
  MoveBlock60(0.8, 'L');
  SetBack(25,300);
  MoveBlock60(0.875, 'R');
  SetFront(20,100); SetFront(15, 380,'L');
  pickcan(5, 1);
}

void NBlock1_2() {
  spinDegree(90);
  BackBlock60(5);
  BackBlock(0.75); SetBack(20, 100); SetBack(15, 380, 'L');
  MoveBlock60(0.8); BackBlock60(0.8, 'R');
  MoveBlock(1, 'L');
  SetBack(20,100); SetBack(15, 380,'R');
  autoPlaceCan(5);
}

void NBlock2_1() {

}

void NBlock2_2() {

}

void NBlock3_1() {

}

void NBlock3_2() {

}

void NFinish() {
  lift(2);
 
  for(int i=0;i<=2;i++){beep(100);delay(50);}
}

void Block1_1(){
    //Edit Here
  setAngleOffset();
  current_degree = 0;
  KeepArm();
  lift(2);
  MoveBlock(3);
  SetWall();
  SetFront(25,350,'R');
  SetArm();
  MoveBlock(2);
  SetFront(25,400,'L');
  BB(60,490,'L');
  MoveBlock(1,'L');
  SetBack(25,350);
  MoveBlock(1,'R');
  SetFront(25,200);
  SetFront(25,420,'L');

  //Edit Pick
  pickcan(0,1);
}

void Block1_2(){
  //Edit Here
  //go yellow//
  BB(60,450,'R');
  delay(200);
  SetFront(25,350);
  delay(200);
  BB(40,1350,'L');
  SetFront(25,350);
  BB(40,1300,'L');
  SetBack(25,350);

  MoveBlock(2);
  SetFront(25,350,'R');
  FF(60,500,'L');
  SetBack(25,400);
  MoveBlock(1,'L');

  lift(2);
  SetWall();
  SetFront(25,100);delay(100);
  SetFront(25,100);delay(100);
  SetFront(25,360,'R');delay(200);
  SetArm();


  //Edit Place
  autoPlaceCan(10);
}

void BlockCK1()
{

}
void BlockCK2()
{

}
void Block2_1(){
  //Edit Here
  delay(500);
  KeepArm();
  SetBack(25,350,'R');
  delay(300);
  SetFront(25,350,'L');
  SetArm();
  //Edit Pick
  pickcan(5,2);
}

void Block2_2(){
  //Edit Here
  //go red//
  delay(300);
  BB(60,350,'L');
  SetBack(25,150);delay(100);
  SetBack(25,330,'L');
  MoveBlock(1);SetFront(25,420,'L');
  MoveBlock(1,'L');
  MoveBlock(1,'L');
  SetFront(25,100);delay(100);
  SetFront(25,100);delay(100);
  SetFront(25,440,'L');
  //Edit Place
  autoPlaceCan(15);

}
void Block3_1(){
  //Edit Here
  //
  delay(1000);
  KeepArm();
  BB(60,200,'L');
  SetWall();
  SetFront(25,340,'R');
  MoveBlock(2,'L');

  SetWall();
  SetFront(25,100);
  delay(100);
  SetFront(25,330);
  SetArm();
  delay(500);
  spinDegree(90);
  delay(500);

  // Edit Pick
  pickcan(5,3,1);
  //
}

void Block3_2(){
  //Edit Here
  //go red//
  delay(500);
  BB(60,100+520+300);
  SetBack(25,400,'R');
  MoveBlock(1,'R');
  MoveBlock(1,'L');
  BackBlock(1);
  MoveBlock(1);
  SetFront(25,470,'R');
  lift(2);
  SetWall();
  SetFront(25,100);
  delay(100);
  SetFront(25,100);
  delay(300);
  SetFront(25,350,'R');
  delay(200);
  SetArm();

  //edit pick
  autoPlaceCan(5);
}

void Finish(){
  //Retry but all can is place
  MoveBlock(1);delay(50);
  BackBlock(1);
  for(int i=0;i<=2;i++){beep(100);delay(50);}
}
void BlockFinish(){
  //Edit Here
  delay(1000);
  KeepArm();
  BB(60,150,'R');
  MoveBlock(2,'R');
  MoveBlock(1);
  SetWall();
  SetFront(25,350,'L');
  SetArm();
  SetBack(25,350);
  MoveBlock(2);
  SetFront(25,420,'L');
  FF(40,1320);
  SetFront(25,350,'R');
  FF(40,1320);
  SetFront(25,400,'R');

  MoveBlock(1);
  SetFront(25,350,'R');
  SetBack(25,350);
  MoveBlock(1,'L');
  SetWall();
  MoveBlock(1);
  SetFront(25,350,'L');
  SetArm();
  MoveBlock(1);
  SetWall();
  SetFront(25,350,'L');
  SetArm();
  MoveBlock(3);
  //beep when Finish
  for(int i=0;i<=3;i++)
  {
    beep(100);delay(50);
  }
}

void FullMap()
{
  NBlock1_1();
  NBlock1_2();
  NBlock2_1();
  NBlock2_2();
  NBlock3_1();
  NBlock3_2();
  NFinish();

  // Block1_1();
  // Block1_2(); 
  // //
  // // BlockCK1();
  // // BlockCK2();
  // //
  // Block2_1();
  // Block2_2(); 
  // //
  // Block3_1();
  // Block3_2(); 
  // // Finish();
  // //
  // BlockFinish(); 
}
void ReTry2()
{
  setAngleOffset();
  current_degree = 0;
  KeepArm();
  lift(2);
  MoveBlock(3);
  SetWall();
  SetFront(25,330,'R');
  SetArm();
  KeepArm();
  MoveBlock(2);
  SetFront(25,420,'L');
  BB(60,490,'L');
  MoveBlock(1,'L');
  MoveBlock(1,'R');
  BB(40,1200,'L'); //Bridge//
  SetFront(25,350);
  BB(40,1200,'L');
  MoveBlock(2);
  SetFront(25,350,'L');
  SetWall();
  SetFront(25,350);
  SetArm();
  BackBlock(2,'R');
  MoveBlock(1,'L');
  BackBlock(1);
  MoveBlock(1);
  SetFront(25,440,'R');
  SetWall();
  SetFront(25,350,'R');
  pickcan(5,2);
  delay(200);
 

  //contunue with this//
  Block2_2();
  Block3_1();
  Block3_2();
  BlockFinish();
}
void ReTry3()
{
  setAngleOffset();
  current_degree = 0;
  KeepArm();
  lift(2);
  MoveBlock(3);
  SetWall();
  SetFront(25,330,'R');
  SetArm();
  KeepArm();
  MoveBlock(2);
  SetFront(25,420,'L');
  BB(60,490,'L');
  MoveBlock(1,'L');
  MoveBlock(1,'R');
  BB(40,1200,'L'); //Bridge//
  SetFront(25,350);
  BB(40,1200,'L');
  MoveBlock(2);
  SetFront(25,350,'R');
  MoveBlock(2);
  SetWall();
  SetFront(25,350,'R');
  SetBack(25,350);
  SetArm();
  MoveBlock(2,'L');
  SetWall();
  delay(300);
  SetFront(25,200);
  delay(100);
  SetFront(25,320);
  SetArm();
  delay(400);
  spinDegree(90);
  delay(400);

  
  // Edit Pick
  pickcan(0,3);


  //continue with this//
  Block3_2();
  BlockFinish();
}
