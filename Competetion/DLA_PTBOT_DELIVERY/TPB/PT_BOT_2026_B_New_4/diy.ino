void PickCan(int pick_height){ // ระยะแท่น 5 10 15 
  servoWrite(chanal_Swing_Left, Swing_Left - 3);
  servoWrite(chanal_Swing_Right, Swing_Right - 3);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) moveToCan(pick_can_distance); //float pick_can_distance = 7.5;  // ค่าระยะจอดหน้าแท่นหยิบ
  else moveToCan0(can_distance);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
  delay(200);
  lift(pick_height + 3); // ยกเผื่อไว้อีก 1 cm
  delay(300);
}
void set_clos_open(){
  STOP();servoCloseLeft();
  STOP();servoCloseRight();
  STOP();servoOpenLeft();
  STOP();servoOpenRight();
}
void get_b(int lif){  // จับกระป๋อง (ยก lif)
  servoCloseLeft();
  servoCloseRight();
  lift(lif);
}
void drop_b(int open){  // กางแขน คู่  
  servoWrite(chanal_Gripper_Left, Close_Left - open); //S2 หุบมือ ชุดมือจับมือซ้ายค่าน้อยยิ่งอ้า เลย -
  servoWrite(chanal_Gripper_Right, Close_Right - open);
  delay(1000);
  servoOpenLeft();
  servoOpenRight();
}
void setCan1(int open) {
  lift(0);
  delay(150);
  // servoWrite(chanal_Gripper_Left, Open_Left);
  // servoWrite(chanal_Gripper_Right, Open_Right);
  servoWrite(chanal_Gripper_Left, Close_Left - open); //S2 หุบมือ ชุดมือจับมือซ้ายค่าน้อยยิ่งอ้า เลย -
  servoWrite(chanal_Gripper_Right, Close_Right - open);
  delay(1000);
  FF(10);delay(200); motorStop();
  lift(0);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(150);
  lift(3);
  delay(150);
}

void set_close_open(){
  STOP();servoCloseLeft();
  STOP();servoOpenLeft();
  STOP();servoCloseRight();
  STOP();servoOpenRight();
}

void pickCanRehydrated(int pick_height, bool switch_lr) {
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  SetArm();
  lift(pick_height);
  if (pick_height != 0) moveToCan(SonarDis);
  else moveToCan0(CanZeroDistance);
  if (pick_height != 0) {lift(pick_height - 5);}
  delay(100);
  // servoCloseLeft();
  // servoCloseRight();
  servoWrite(chanal_Gripper_Left, Close_Left + 30);
  servoWrite(chanal_Gripper_Right, Close_Right + 30);
  delay(200);
  lift(pick_height + 2);
  delay(200);
  if (switch_lr == 1) {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    swingGripper('l', Swing_Left - (switch_degree + 13));
    delay(200);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(200);
    swingGripper('l', Swing_Left - switch_degree);
    delay(300);
    BB(30, 400);
    switchGripper('r', 'l');
    delay(1200);
    servoWrite(chanal_Gripper_Right, Open_Right);
    swingGripper('r', Swing_Right - (switch_degree + 10));
    lift(pick_height + 4);
    moveToCan(SonarDis);
    lift(pick_height + 2);
    delay(400);
    servoCloseRight();
    delay(200);
    vTaskSuspend(switchGripperTaskHandle);
  }
  BB(30, 500);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);

  setCan1(30);

  BB(30,575);
}

void placeCan1Rehydrated(int drop_height, int distance, char from_gripper, char drop_point) {
  bool switch_can = 0;
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  if (drop_height != 15) {
    lift(drop_height + 3);
  } else {
    lift(drop_height + 5);
  }
  if (from_gripper == 'l' && drop_point == 'l') {
    swingGripper('l', Swing_Left + switch_degree - 20);
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'l' && drop_point == 'c') {
    swingGripper('l', Swing_Left - (switch_degree + 10));
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'r' && drop_point == 'r') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right + switch_degree - 20);  //-10
  } else if (from_gripper == 'r' && drop_point == 'c') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right - (switch_degree + 10));  //+10
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
    switch_can = 1;
  }
  moveToCan(distance);
  // FF(10, MoveTimerPlace);
  motorStop();
  lift(drop_height + 1);
  delay(300);
  if (switch_can == 0) dropCan(from_gripper, drop_height);
  else dropCan(drop_point, drop_height);
  delay(200);
  BB(30, 500);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
  BB(30, 575);
}
void placeCan1_J(int drop_height, int distance, char from_gripper, char drop_point){
  bool switch_can = 0;
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  if (drop_height != 15) {
    lift(drop_height + 3);
  } else {
    lift(drop_height + 5);
  }
  if (from_gripper == 'l' && drop_point == 'l') {
    swingGripper('l', Swing_Left + switch_degree - 20);
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'l' && drop_point == 'c') {
    swingGripper('l', Swing_Left - (switch_degree + 10));
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'r' && drop_point == 'r') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right + switch_degree - 20);  //-10
  } else if (from_gripper == 'r' && drop_point == 'c') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right - (switch_degree + 10));  //+10
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
    switch_can = 1;
  }
  if (drop_height >= 15) {
    moveToCan15(distance);
  } else {
    moveToCan(distance);
  }
  if (from_gripper == 'l') {
    servoWrite(chanal_Gripper_Left, Open_Left - 15);
  }
  if (from_gripper == 'r') {
    servoWrite(chanal_Gripper_Right, Open_Right - 15);
  }
  // FF(10, MoveTimerPlace);
  motorStop();
  lift(drop_height + 0.7);
  delay(300);
  delay(200);
  BB(30, 500);
  lift(2);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
  BB(30, 575);
  SetArm();
}
void grabCanRaw(int pick_height, bool switch_lr) {
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
  delay(200);
  lift(pick_height + 2);
  delay(200);

  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);

  // setCan1(30);

}
// Returns true ONLY ONCE per press (ignores holding)
bool isPressedOnce(int btn) {
  static int lastStateA = 0;
  static int lastStateB = 0;
  static unsigned long lastTimeA = 0;
  static unsigned long lastTimeB = 0;

  int &lastState = (btn == A) ? lastStateA : lastStateB;
  unsigned long &lastTime = (btn == A) ? lastTimeA : lastTimeB;

  int currentState = switchRead(btn);
  bool triggered = false;

  // Trigger only when changing from unpressed (0) to pressed (1)
  if (currentState == 1 && lastState == 0 && (millis() - lastTime > 50)) {
    triggered = true;
    lastTime = millis();
  }

  // Record release time to prevent bounce on release
  if (currentState == 0 && lastState == 1) {
    lastTime = millis();
  }

  lastState = currentState;
  return triggered;
}
void testFF(float speed, float timer, float bonusOffset) {
  int bonus = 0;

  while (1) {
    // Press A once to run FF and add +25 for the next press
    if (isPressedOnce(A)) {
      beep(100);
      Serial.print("Running FF(25, ");
      Serial.print(400 + bonus);
      Serial.println(")");

      FF(speed, timer + bonus);
      motorStop();

      bonus += bonusOffset; // Next press will be +25 more
    }

    // Optional: Press B once to reset bonus back to 0
    if (isPressedOnce(B)) {
      bonus = 0;
      beep(200);
      Serial.println("Reset bonus to 0");
    }
  }
}
void testBB(float speed, float timer, float bonusOffset) {
  int bonus = 0;

  while (1) {
    // Press A once to run FF and add +25 for the next press
    if (isPressedOnce(A)) {
      beep(100);
      Serial.print("Running FF(25, ");
      Serial.print(400 + bonus);
      Serial.println(")");

      BB(speed, timer + bonus);
      motorStop();

      bonus += bonusOffset; // Next press will be +25 more
    }

    // Optional: Press B once to reset bonus back to 0
    if (isPressedOnce(B)) {
      bonus = 0;
      beep(200);
      Serial.println("Reset bonus to 0");
    }
  }
}
void TSF(float speed, float timer, float bonusOffset) {
  int bonus = 0;

  while (1) {
    if (isPressedOnce(A)) {
      beep(100);
      Serial.print("Running FF(25, ");
      Serial.print(400 + bonus);
      Serial.println(")");

      SetFront(speed, timer + bonus);
      motorStop();

      bonus += bonusOffset;
    }

    // Optional: Press B once to reset bonus back to 0
    if (isPressedOnce(B)) {
      bonus = 0;
      beep(200);
      Serial.println("Reset bonus to 0");
    }
  }
}
void TSB(float speed, float timer, float bonusOffset) {
  int bonus = 0;

  while (1) {
    if (isPressedOnce(A)) {
      beep(100);
      Serial.print("Running FF(25, ");
      Serial.print(400 + bonus);
      Serial.println(")");

      SetBack(speed, timer + bonus);
      motorStop();

      bonus += bonusOffset;
    }

    // Optional: Press B once to reset bonus back to 0
    if (isPressedOnce(B)) {
      bonus = 0;
      beep(200);
      Serial.println("Reset bonus to 0");
    }
  }
}

void SetFrontWall(float speed, float timer){
  SetWall();
  lift(3);
  SetFront(speed, timer);
  lift(0);
  SetArm();
}
void testCanImpl(){
//--- Templates/Legacies
  // get_b(5); //คีบ แล้ว(ยก)
  // delay(2000);
  // setCan1(30); // มีระยะกางมือจับเล็กน้อย(open)
  // delay(2000);
  // drop_b(30); //ปล่อยกระป๋อง มีระยะกางมือจับเล็กน้อยก่อน(open)
  // lift(0);
  // STOP();

  // PickCan(5);

  // setCan1(18);
  // delay(2000);
  // STOP();drop_b(18);
  // STOP();lift(0);

  SetBack(25, 400);
  spinDegree(-90);

  pickCanRehydrated(5, NO_SWITCH_LR);STOP(); // Test 5 cm height
  // STOP();pickCanRehydrated(5, SWITCH_LR);STOP();
  // pickCanRehydrated(0, NO_SWITCH_LR);STOP(); // Test Ground height
  // pickCanRehydrated(0, SWITCH_LR);
  placeCan1Rehydrated(5, SonarDis, 'l', 'l');
  placeCan1Rehydrated(10, SonarDis, 'r', 'c');
  

//---
//--- Green
  // servoCloseLeft();
  // servoCloseRight();
  // delay(500);
  // lift(5);
  // STOP();
  // lift(0);
  // servoOpenLeft();
  // servoOpenRight();
//---

}