void DoMenu()
{
  setAngleOffset();
  current_degree = 0;
  lcdSetTextSize(1);
  delay(300);
  if(X==0)
  {
    beep(0);
  }
  else if(X==1)
  {
    if(switchRead(A)==1){calibrateCanColor();}
    else if(switchRead(B)==1){CheckColLoop();}
  }
  else if(X==2)
  {
    if(switchRead(A)==1){ShowValue_Sensor();}
    else if(switchRead(B)==1){ShowDistanceSensorLCD();}
  }
  else if(X==3)
  {
    if(switchRead(A)==1){FullMap();}
    else if(switchRead(B)==1){ReTry2();}
  }
  else if(X==4)
  {
    if(switchRead(A)==1){ReTry3();}
    else if(switchRead(B)==1){Finish();}
  }
  else if(X==5)
  {
    if(switchRead(A)==1){CheckColGrip();}
    else if(switchRead(B)==1){Line_Serial();}
  }
  else if(X==6)
  {
    if(switchRead(A)==1){Block1_1();Block1_2();}
    else if(switchRead(B)==1){setAngleOffset();current_degree = 0;pickcan(5,2,1);Block2_2();}
  }
  else if(X==7)
  {
    if(switchRead(A)==1)
    {setAngleOffset();current_degree = 0;
      lift(2);SetWall();
      SetFront(25,250u);
      SetFront(25,300,'R');
      SetBack(25,400);
      SetArm();pickcan(0,3);Block3_2();}
    else if(switchRead(B)==1){BlockFinish();}
  }
  else if(X==8)
  {
    if(switchRead(A)==1){
      lift(2); SetWall();
      SetFront(20,100);SetFront(15, 380,'R');delay(100);pickcan(5,1);
      delay(300);
      BB(60,420,'R');delay(100);FF(60,500);
      SetFront(20,150);SetFront(15,600,'L');
      // SetBack(20,350);
      autoPlaceCan(10);
    } //yellow
    
    else if(switchRead(B)==1){
      lift(2); SetWall();
      SetFront(20,100);SetFront(15, 380,'R');delay(100);pickcan(5,1);
      delay(300);
      BB(60,420,'R');delay(100);FF(60,500);
      SetFront(20,150);SetFront(15,600,'L');
      // SetBack(20,350);
      autoPlaceCan(5);
      } //green
  }
  else if(X==9)
  {
    if(switchRead(A)==1){
      lift(2); SetWall();
      SetFront(20,100);SetFront(15, 380,'R');delay(100);pickcan(5,1);
      delay(300);
      spinDegree(90); delay(100);FF(60,500);
      SetFront(20,150);SetFront(15,550,'L');
      // SetBack(20,350);
      autoPlaceCan(15);
      } //red
    else if(switchRead(B)==1){lift(5);}
  }
  else if(X==10)
  {
    if(switchRead(A)==1){MoveBlock60(1);}
    else if(switchRead(B)==1){SetFront(25,350);}
  }
  else if(X==11)
  {
    if(switchRead(A)==1){spinDegree(-90);}
    else if(switchRead(B)==1){spinDegree(90);}
  }
  else if(X==12)
  {
    if(switchRead(A)==1){servoCloseLeft(); servoCloseRight(); delay(300); spinDegree(-90);}
    else if(switchRead(B)==1){servoCloseLeft(); servoCloseRight(); delay(300); spinDegree(90);}
  }
  else if (X==13)
  {
    if (switchRead(A)==1) {beep(50); delay(300); calibrateIMU();}
    else if (switchRead(B)==1) {MoveBlock(1);}
  }
  else if (X==14) {
    if (switchRead(A)==1) {turnDegreeFront(-90);}
    else if (switchRead(B)==1) {turnDegreeFront(-180);}
  }
  else if (X==15) {
    if (switchRead(A)==1) {turnDegreeBack(-90);}
    else if (switchRead(B)==1) {turnDegreeBack(90);}
  }

  motorStop();delay(100);
}