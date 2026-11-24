//Put this in first tab
#define No 0
#define Yes 1

long Timer, Timer2;
int SW_A_Status;     //Button A status, exit if over hold time
int RobotMode = 0;   //Current mode
int MaxMenu = 9;     //Max menu
int LowMenu = 0;     //always set to 0
int HoldTime = 300;  //ms

void StartTimer() {
  Timer = millis();
}

long int ReadTimer() {
  return (millis() - Timer);
}

char Read_Sw_A() {
  if (switchRead(A)) return (1);
  else {
    delay(10);
    if (switchRead(A)) return (1);
    else return (0);
  }
}

char Read_Sw_B() {
  if (switchRead(B)) return (1);
  else {
    delay(10);
    if (switchRead(B)) return (1);
    else return (0);
  }
}

void sw_A_unpress() {
  while (Read_Sw_A()) { delay(10); }
}
void Wait_Sw_A_press() {
  while (Read_Sw_A() == 0) { delay(10); }
}

void DisplayMode() {
  switch (RobotMode) {
    case 0:
      //insert your function bellow
      lcdPrintText(0, 10, "Full Map" + String("                                   "), 0xffff);
      break;

    case 1:
      //insert your function bellow
      lcdPrintText(0, 10, "Retry 2" + String("                                   "), 0xffff);
      break;

    case 2:
      //insert your function bellow
      lcdPrintText(0, 10, "Retry 3" + String("                                   "), 0xffff);
      break;

    case 3:
      //insert your function bellow
      lcdPrintText(0, 10, "Finish" + String("                                   "), 0xffff);
      break;
    case 4:
      //insert your function bellow
      lcdPrintText(0, 10, "Check Cans Color" + String("                                   "), 0xffff);
      break;

    case 5:
      //insert your function bellow
      lcdPrintText(0, 10, "Show Analogs" + String("                                   "), 0xffff);
      break;

    case 6:
      //insert your function bellow
      lcdPrintText(0, 10, "Show Sonar" + String("                                   "), 0xffff);
      break;

    case 7:
      //insert your function bellow
      lcdPrintText(0, 10, "Calibrate Color Sensor" + String("                                   "), 0xffff);
      break;

    case 8:
      //insert your function bellow
      lcdPrintText(0, 10, "GripColor              " + String("                                   "), 0xffff);
      break;

    case 9:
      //insert your function bellow
      lcdPrintText(0, 10, "Empty" + String("                                   "), 0xffff);
      break;

    case 10:
      //insert your function bellow
      lcdPrintText(0, 10, "Empty" + String("                                   "), 0xffff);
      break;
  }
}

void RunMode() {
  switch (RobotMode) {
    case 0:
      //insert your function bellow
      FullMap();
      break;

    case 1:
      //insert your function bellow
      ReTry2();
      break;

    case 2:
      //insert your function bellow
      ReTry3();
      break;

    case 3:
      //insert your function bellow
      Finish();
      break;
    case 4:
      //insert your function bellow
      CheckColLoop();
      break;

    case 5:
      //insert your function bellow
      ShowValue_Sensor();
      break;

    case 6:
      //insert your function bellow
      ShowDistanceSensorLCD();
      break;

    case 7:
      //insert your function bellow
      calibrateCanColor();
      break;

    case 8:
      //insert your function bellow
      CheckColGrip();
      break;

    case 9:
      //insert your function bellow
      break;

    case 10:
      //insert your function bellow
      break;
  }
}

void MenuTrack() {
  //   while(1){
  tft.fillScreen(ST77XX_BLACK);
  setAngleOffset();
  current_degree = 0;
  SW_A_Status = No;
  while (SW_A_Status == No) {
    if (Read_Sw_A()) {
      beep(5, 4090);
      StartTimer();
      while (Read_Sw_A()) {
        lcdPrintText(0, 30, "Holding", 0xffff);
        if (ReadTimer() >= HoldTime) {
          lcdPrintText(0, 30, "Running", 0xffff);
          beep(100);
          RunMode();
          SW_A_Status = Yes;
          break;
        }
      }
      lcdPrintText(0, 30, String("              "), 0xffff);
      if (RobotMode > LowMenu && SW_A_Status == No) {
        RobotMode--;
      }
    } else if (Read_Sw_B()) {
      beep(5, 4090);
      if (RobotMode < MaxMenu) {
        RobotMode++;
      }
      while (Read_Sw_B());
    }
    DisplayMode();
    lcdPrintText(0, 0, "You select Mode: " + String(RobotMode) + "     ", 0xffff);
  }
  //   lcdPrintText(0,30,"SW_A || SW_B again ",0xffff);
  STOP();
  //   }
}

void beep(int duration, int Freqency)
{
  pca_1.setPWM(5, 0, Freqency);
  delay(duration);
  pca_1.setPWM(5, 0, 0);
}