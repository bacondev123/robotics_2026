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
    else if(switchRead(B)==1){Block1_1();Block1_2();}
  }
  else if(X==4)
  {
    if(switchRead(A)==1){Block2_1();}
    else if(switchRead(B)==1){Finish();}
  }
  else if(X==99)
  {
    if(switchRead(A)==1){CheckColGrip();}
    else if(switchRead(B)==1){Line_Serial();}
  }
  else if(X==99)
  {
    if(switchRead(A)==1){Block1_1();Block1_2();}
    else if(switchRead(B)==1){setAngleOffset();current_degree = 0;pickcan(5,2,1);Block2_2();}
  }
  else if(X==7)
  {
    if(switchRead(A)==1)
    {setAngleOffset();current_degree = 0;
      lift(2);SetWall();
      SetFront(25,200);
      SetFront(25,300,'R');
      SetBack(25,400);
      SetArm();pickcan(0,3);Block3_2();}
    else if(switchRead(B)==1){BlockFinish();}
  }
  else if(X==8)
  {
    if(switchRead(A)==1){PickCanTest(0);delay(300);SetWall();SetFront(25,100);delay(100);SetFront(25,350,'R');SetArm();autoPlaceCan(10);} //yellow
    else if(switchRead(B)==1){PickCanTest(0);delay(300);SetWall();SetFront(25,100);delay(100);SetFront(25,350,'R');SetArm();autoPlaceCan(5);BB(40,150);STOP();} //green
  }
  else if(X==9)
  {
    if(switchRead(A)==1){PickCanTest(0);delay(300);SetWall();SetFront(25,100);delay(100);SetFront(25,370,'L');SetArm();autoPlaceCan(15);BB(40,150);STOP();} //red
    else if(switchRead(B)==1){}
  }
  else if(X==10)
  {
    if(switchRead(A)==1){MoveBlock60(1);}
    else if(switchRead(B)==1){MoveBlock40(1);}
  }
  else if(X==11)
  {
    if(switchRead(A)==1){BackBlock60(1);}
    else if(switchRead(B)==1){BackBlock40(1);}
  }
  else if(X==5)
  {
    if(switchRead(A)==1){pickcan(5,2);BB(40,150,'R');delay(100);spinDegree(90);delay(100);SetWall();SetFront(25,350,'R');SetArm();autoPlaceCan(5);} //pickcan0 ol
    else if(switchRead(B)==1){pickcan(5,1);BB(40,150,'R');delay(100);spinDegree(90);delay(100);SetWall();SetFront(25,350,'R');SetArm();autoPlaceCan(5);BB(40,150,'R');
    spinDegree(90);delay(100);SetWall();SetFront(25,350,'L');pickcan(5,2);BB(40,150,'R');delay(100);spinDegree(90);delay(100);SetWall();SetFront(25,350,'R');SetArm();autoPlaceCan(5);} //pickcan5 il
  }
  else if(X==6)
  {
    if(switchRead(A)==1){pickcan(5,2);BB(40,150,'R');delay(100);spinDegree(90);delay(100);SetWall();SetFront(25,350,'R');SetArm();autoPlaceCan(15);} //pickcan5 ol
    else if(switchRead(B)==1){}
  }

  motorStop();delay(100);
}