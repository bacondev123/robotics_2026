void pickcan(int pick_height,int WhatCan)
{
  SetArm();
  if(autoplace==true){autoPickCan(pick_height);}
  else if(autoplace==false){
         if(WhatCan==1){PickManual(pick_height,CanL[0],CanR[0]); ShowColor(0); }
    else if(WhatCan==2){PickManual(pick_height,CanL[1],CanR[1]); ShowColor(1);}
    else if(WhatCan==3){PickManual(pick_height,CanL[2],CanR[2]); ShowColor(2);}
  }
}

void pickcan(int pick_height,int WhatCan,int swap)
{
  SetArm();
  if(autoplace==true){autoPickCan(pick_height,swap);}
  else if(autoplace==false){
         if(WhatCan==1){PickManual(pick_height,CanL[0],CanR[0],swap); ShowColor(0); }
    else if(WhatCan==2){PickManual(pick_height,CanL[1],CanR[1],swap); ShowColor(1);}
    else if(WhatCan==3){PickManual(pick_height,CanL[2],CanR[2],swap); ShowColor(2);}
  }
}

void ShowColor(int number)
{
    if (CanL[number] =='y') {
      tft.fillRect(0, 0, 80, 128, 0xffc0);
    }
    else {
      if (CanL[number]=='r') {
        tft.fillRect(0, 0, 80, 128, 0xf800);
      }
      else if (CanL[number]=='g') {
        tft.fillRect(0, 0, 80, 128, 0x1d40);
      }
      else {
        tft.fillRect(0, 0, 80, 128, 0x0000);
      }
    }

    if (CanR[number] =='y') {
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    }
    else {
      if (CanR[number]=='r') {
        tft.fillRect(80, 0, 80, 128, 0xf800);
      }
      else if (CanR[number]=='g') {
        tft.fillRect(80, 0, 80, 128, 0x1d40);
      }
      else {
        tft.fillRect(80, 0, 80, 128, 0x0000);
      }
    }

}