// #### Foward (FF) ------------------
// Chunk || speed || timer
//   1   ||   40  ||  800
//   2   ||   40  ||  1400
//   3   ||   40  ||  1900
//-----------------------
// #### Backward (BB) ---------------
// Chunk || speed || timer
//   1   ||   40  ||  850
//   2   ||   40  ||  -
//   3   ||   40  ||  -
//-----------------------
// #### SetFront (FF)
// speed || timer
//   25  ||  400
//-----------------------
// #### SetBack (BB)
// speed || timer
//   25  ||  515
//-----------------------


void Experiment(){
  Lab_01();
  Lab_02();
  Lab_03();
  Lab_04();
}
void Lab_01(){
  // testFF(40, 1600, 200);
  // testFF(40,300, 100);
  // FF(40,800);
  // STOP();
  // FF(40,1400);
  // STOP();
  // FF(40,1900);
  // pickCanRehydrated(0, NO_SWITCH_LR);
  // delay(300);
  // servoWrite(chanal_Gripper_Left, Open_Left);
  // servoWrite(chanal_Gripper_Right, Open_Right);
  // STOP();

  pickCanRehydrated(5, NO_SWITCH_LR);
  delay(300);
  STOP();

  placeCan1_J(15,SonarDis, 'l', 'c');
  placeCan1_J(15,SonarDis, 'l', 'l');


}
void Lab_02(){
  // testBB(40,700,50);
  // TSB(25,400,25);
}
void Lab_03(){
  // SetBack(25,515, 'L');
  // pickCanRehydrated(0, NO_SWITCH_LR);
  // spinDegree(90);
  // FF(40,800);
  // placeCan1Rehydrated(5,SonarDis,'l', 'c');
  // placeCan1Rehydrated(10,SonarDis, 'r', 'c');
  
}
void Lab_04(){
  // placeCanJ(5, SonarDis, 'l', 'c');
  // SetWall();
  // SetFrontWall(25,400);
  // SetBack(25,515);
}