void SelectPlace()
{
  autoplace=false;
  motorStop();
  lcdSetTextSize(1);
  tft.fillScreen(ST77XX_BLACK);
  // SelectColor();
  
  // CanL[0]='g';
  // CanR[0]='r';
  // CanL[1]='y';
  // CanR[1]='r';
  // STOP();

  lcdClear();
  while(1){delay(100);if(switchRead(A)==1 || switchRead(B)==1){MenuTEST();break;}}
  // beep(100);
  delay(200);
}
void ReadCan()
{
  lcdSetTextSize(2);
  if(X==0){
    lcdPrintText(0, 20,"A Green         ", 0xffff);
    lcdPrintText(0, 40,"B Yellow        ", 0xffff);
  }
  else if(X==1){
    lcdPrintText(0, 20,"A Red           ", 0xffff);
    lcdPrintText(0, 40,"B undifined     ", 0xffff);
  }
}
void SelectColor()
{
  //CanL1
  while(1){
    int raw = readKnob2();
    raw = constrain(raw, 1230, 2590); // ป้องกันค่าออกนอกช่วง
    X = map(raw, 1230, 2590, 0, 3);
    lcdPrintText(0, 0,"CanL1", 0xffff);
    ReadCan();
    delay(100);
    if(switchRead(A)==1 || switchRead(B)==1)
    {
         if(X==0){if(switchRead(A)==1){CanL[0]='g';}else if(switchRead(B)==1){CanL[0]='y';} }
    else if(X==1){if(switchRead(A)==1){CanL[0]='r';}else if(switchRead(B)==1){CanL[0]='u';} }
    break;
    }
  }

  //CanR1
  lcdClear();
  delay(100);
  while(1){
    int raw = readKnob2();
    raw = constrain(raw, 1230, 2590); // ป้องกันค่าออกนอกช่วง
    X = map(raw, 1230, 2590, 0, 3);
    lcdPrintText(0, 0,"CanR1", 0xffff);
    ReadCan();
    delay(100);
    if(switchRead(A)==1 || switchRead(B)==1)
    {
         if(X==0){if(switchRead(A)==1){CanR[0]='g';}else if(switchRead(B)==1){CanR[0]='y';}}
    else if(X==1){if(switchRead(A)==1){CanR[0]='r';}else if(switchRead(B)==1){CanR[0]='u';}}
    break;
    }
  }

  //CanL2
  lcdClear();
  delay(100);
  while(1){
    int raw = readKnob2();
    raw = constrain(raw, 1230, 2590); // ป้องกันค่าออกนอกช่วง
    X = map(raw, 1230, 2590, 0, 3);
    lcdPrintText(0, 0,"CanL2", 0xffff);
    ReadCan();
    delay(100);
    if(switchRead(A)==1 || switchRead(B)==1)
    {
         if(X==0){if(switchRead(A)==1){CanL[1]='g';}else if(switchRead(B)==1){CanL[1]='y';}}
    else if(X==1){if(switchRead(A)==1){CanL[1]='r';}else if(switchRead(B)==1){CanL[1]='u';}}
    break;
    }
  }

  //CanR2
  lcdClear();
  delay(100);
  while(1){
    int raw = readKnob2();
    raw = constrain(raw, 1230, 2590); // ป้องกันค่าออกนอกช่วง
    X = map(raw, 1230, 2590, 0, 3);
    lcdPrintText(0, 0,"CanR2", 0xffff);
    ReadCan();
    delay(100);
    if(switchRead(A)==1 || switchRead(B)==1)
    {
         if(X==0){if(switchRead(A)==1){CanR[1]='g';}else if(switchRead(B)==1){CanR[1]='y';}}
    else if(X==1){if(switchRead(A)==1){CanR[1]='r';}else if(switchRead(B)==1){CanR[1]='u';}}
    break;
    }
  }

  //CanL3
  lcdClear();
  delay(100);
  while(1){
    int raw = readKnob2();
    raw = constrain(raw, 1230, 2590); // ป้องกันค่าออกนอกช่วง
    X = map(raw, 1230, 2590, 0, 3);
    lcdPrintText(0, 0,"CanL3", 0xffff);
    ReadCan();
    delay(100);
    if(switchRead(A)==1 || switchRead(B)==1)
    {
         if(X==0){if(switchRead(A)==1){CanL[2]='g';}else if(switchRead(B)==1){CanL[2]='y';}}
    else if(X==1){if(switchRead(A)==1){CanL[2]='r';}else if(switchRead(B)==1){CanL[2]='u';}}
    break;
    }
  }

  //CanR3
  lcdClear();
  delay(100);
  while(1){
    int raw = readKnob2();
    raw = constrain(raw, 1230, 2590); // ป้องกันค่าออกนอกช่วง
    X = map(raw, 1230, 2590, 0, 3);
    lcdPrintText(0, 0,"CanR3", 0xffff);
    ReadCan();
    delay(100);
    if(switchRead(A)==1 || switchRead(B)==1)
    {
         if(X==0){if(switchRead(A)==1){CanR[2]='g';}else if(switchRead(B)==1){CanR[2]='y';} }
    else if(X==1){if(switchRead(A)==1){CanR[2]='r';}else if(switchRead(B)==1){CanR[2]='u';} }
    break;
    }
  }
  delay(200);lcdClear();delay(200);
  lcdSetTextSize(1);
  lcdPrintText(0, 0,"Result", 0xffff);
  lcdPrintText(0, 10,"L1 = "+String(CanL[0]), 0xffff);lcdPrintText(40, 10,"R1 = "+String(CanR[0]), 0xffff);
  lcdPrintText(0, 20,"L2 = "+String(CanL[1]), 0xffff);lcdPrintText(40, 20,"R2 = "+String(CanR[1]), 0xffff);
  lcdPrintText(0, 30,"L3 = "+String(CanL[2]), 0xffff);lcdPrintText(40, 30,"R3 = "+String(CanR[2]), 0xffff);
  lcdSetTextSize(1);
  // STOP();
}