int readKnob2(){
  int sum = 0;
  for(int i=0; i<10; i++){
    sum += analogRead(32);
    delay(2);
  }
  return sum / 10;
}
void SelectMenu()
{
  motorStop();
  lcdSetTextSize(1);
  tft.fillScreen(ST77XX_BLACK);
  while(1){
  lcdPrintText(0,20,"A SelectPlace              ",0xffff);
  lcdPrintText(0,40,"B Menu                   ",0xffff);
  delay(100);
  if(switchRead(A)==1){SelectPlace();break;}
  else if(switchRead(B)==1){MenuTEST();break;}
  }
  lcdClear();
  beep(100);
  delay(200);
}
void MenuTEST()
{
  while(1){
  motorStop();
  lcdSetTextSize(2);
  tft.fillScreen(ST77XX_BLACK);
  setAngleOffset();
  current_degree = 0;
  lift(0);
  setupServo();
  while(1){
    int raw = readKnob2();
    raw = constrain(raw, 1230, 2530); // ป้องกันค่าออกนอกช่วง
    X = map(raw, 1230, 2530, 0, 11);
    lcdPrintText(0, 0, String(X), 0xffff);
    ReadMenu();
    delay(50);
    if(switchRead(A)==1 || switchRead(B)==1){DoMenu();Serial.print("You Press!!");break;}
  }
  beep(100);
  delay(200);
  lcdPrintText(0, 60,"SW_A || SW_B again", 0xffff);
  lcdPrintText(0, 70,"You Press " + String(X), 0xffff);
  STOP();
  }
}

void ReadMenu()
{
  if(X==0){
    lcdPrintText(0,20,"A Not Use              ",0xffff);
    lcdPrintText(0,40,"B Not Use                   ",0xffff);
  }
  else if(X==1){
    lcdPrintText(0,20,"A CalibColor               ",0xffff);
    lcdPrintText(0,40,"B readColor                         ",0xffff);
  }
  else if(X==2){
    lcdPrintText(0,20,"A Value_SS                    ",0xffff);
    lcdPrintText(0,40,"B SonarLCD                    ",0xffff);
  }
  else if(X==3){
    lcdPrintText(0,20,"A FullMap                    ",0xffff);
    lcdPrintText(0,40,"B B1                    ",0xffff);
  }
  else if(X==4){
    lcdPrintText(0,20,"A B2                     ",0xffff);
    lcdPrintText(0,40,"B B3                    ",0xffff);
  }
  else if(X==99){
    lcdPrintText(0,20,"A CheckColGrip                    ",0xffff);
    lcdPrintText(0,40,"B Line_Serial                    ",0xffff);
  }
  else if(X==99){
    lcdPrintText(0,20,"A Block1                    ",0xffff);
    lcdPrintText(0,40,"B Block2                    ",0xffff);
  }
  else if(X==7){
    lcdPrintText(0,20,"A Block3                    ",0xffff);
    lcdPrintText(0,40,"B BlockFinish                    ",0xffff);
  }
  else if(X==8){
    lcdPrintText(0,20,"A Yellow                    ",0xffff);
    lcdPrintText(0,40,"B Green                    ",0xffff);
  }
  else if(X==9){
    lcdPrintText(0,20,"A Red                 ",0xffff);
    lcdPrintText(0,40,"B Empty            ",0xffff);
  }
  else if(X==10){
    lcdPrintText(0,20,"A MB60                 ",0xffff);
    lcdPrintText(0,40,"B MB40                 ",0xffff);
  }
  else if(X==11){
    lcdPrintText(0,20,"A BB60                 ",0xffff);
    lcdPrintText(0,40,"B BB40                 ",0xffff);
  }
  else if(X==5){
    lcdPrintText(0,20,"A pick0                 ",0xffff);
    lcdPrintText(0,40,"B pick5 IL                 ",0xffff);
  }
  else if(X==6){
    lcdPrintText(0,20,"A pick5 OL                 ",0xffff);
    lcdPrintText(0,40,"B                  ",0xffff);
  }
}