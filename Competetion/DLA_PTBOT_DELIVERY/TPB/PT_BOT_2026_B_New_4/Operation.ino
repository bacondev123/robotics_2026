// #### Foward (FF) ------------------
// Chunk || speed || timer
//   1   ||   40  ||  800
//   2   ||   40  ||  1400
//   3   ||   40  ||  1900
//-----------------------
// #### Backward (BB) ---------------
// Chunk || speed || timer
//   1   ||   40  ||  700 (old val 850)
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
// #### Highway (FF)
// speed || timer
//   25  ||  2400 (BB filler)
//-----------------------
// #### Highway (BB)
// speed || timer
//   25  ||  2400
//-----------------------


void Operation(){
  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
}
void Mission_1(){
  // BB(40, 1850);
  // SetBack(25,515, 'R');
  // BB(40,1200);
  // spinDegree(90);
  // BB(40,700);
  // spinDegree(-90);
  // FF(40, 800);
  // SetFront(25, 400, 'L');
  // FF(40,700);
  // spinDegree(90);
  // SetFront(25, 400);
  // BB(40, 2400);
  // spinDegree(90);
  // FF(40,800);
  // spinDegree(90);
  // FF(40,800);
  // spinDegree(90);
  // BB(40,700);
  // SetBack(25,485, 'L');
  // pickCanRehydrated(0,NO_SWITCH_LR);
  // SetBack(25,475, 'R');
  // FF(40,800);
  // SetFront(25,400,' L');
  // placeCan1_J(5,SonarDis, 'l', 'c');

  // BB(40,700);
  // SetBack(25,485);
  // spinDegree(-90);
  // BB(40,700);
  // spinDegree(-90);
  // BB(40,1250);
  // SetBack(25,515,'L');
  // placeCan1_J(10, SonarDis, 'r', 'c');
  // STOP();
}
void Mission_2(){
  FF(15,200);
  spinDegree(90);
  FF(40,1400);
  spinDegree(-90);
  BB(40,1250);
  SetBack(25,435,'R');
  FF(40,800);
  pickCanRehydrated(5,NO_SWITCH_LR);
  STOP();
  BB(40,700);
  // SetBack(25,515,'L');
  spinDegree(-90);
  FF(40,800);
  spinDegree(-90);
  FF(40,800);
  spinDegree(90);
  SetFront(25,515,'L');
  placeCan1_J(10,SonarDis, 'r', 'r');
  BB(40,700);
  spinDegree(-90);
  BB(40,700);
  spinDegree(-90);
  BB(40,1250);
  SetBack(25,565,'L');
  placeCan1_J(10,SonarDis,'l', 'l');

}
void Mission_3(){
  
}
void Mission_4(){
  
}
/* -- Archives
  BB(40,700);
  // SetBack(25,515,'L');
  spinDegree(90);
  BB(40,0);
  SetBack(25,515,'R');
  FF(40,800);


  BB(40,850);
  SetBack(25,515,'L');
  FF(40,1400);
  spinDegree(90);
  BB(40,1250);
  SetBack(25,515,'L');
*/