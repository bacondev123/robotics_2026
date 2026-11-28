void setupServo() {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
}
void SetWall() {
  servoWrite(chanal_Swing_Left, Swing_Left + 90);
  servoWrite(chanal_Swing_Right, Swing_Right + 90);
  //หลังจากเซ็ตหน้าแล้ว seupServo();
}
void SetArm() {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}
void KeepArm() {
  servoWrite(chanal_Swing_Left, Swing_Left - 45);
  servoWrite(chanal_Swing_Right, Swing_Right - 45);
  servoCloseLeft();
  servoCloseRight();
}


void servoOpenLeft() {
  for (int i = Close_Left; i > Open_Left; i--) {
    servoWrite(chanal_Gripper_Left, i);
    delay(10);
  }
}

void servoCloseLeft() {
  servoWrite(chanal_Gripper_Left, Close_Left);
}

void servoOpenRight() {
  for (int i = Close_Right; i > Open_Right-10; i--) {
    servoWrite(chanal_Gripper_Right, i);
    delay(5);
  }
}

void servoCloseRight() {
  servoWrite(chanal_Gripper_Right, Close_Right);
}


void switchGripperLoop(void *pvParameters) {
  // -1 //From Right->Left
  //  1 //From Left-->Right
  while (1) {
    if (switch_flag == -1) {  // From Right->Left
      servoWrite(chanal_Gripper_Left, Open_Left);
      servoWrite(chanal_Swing_Right, Swing_Right + 50);  //45
      delay(200);
      servoWrite(chanal_Swing_Left, Swing_Left - 50);    //45
      servoWrite(chanal_Swing_Right, Swing_Right - 50);  //45
      delay(200);
      servoCloseLeft();
      delay(150);
      servoWrite(chanal_Gripper_Right, Open_Right);
      delay(150);
      swing_current_degree[0] = Swing_Left + switch_degree;
      swing_current_degree[1] = Swing_Right + 50;
      servoWrite(chanal_Swing_Left, swing_current_degree[0]);
      servoWrite(chanal_Swing_Right, swing_current_degree[1]);
      switch_flag = 0;
    } else if (switch_flag == 1) {  //From Left->Right
      servoWrite(chanal_Gripper_Right, Open_Right);
      servoWrite(chanal_Swing_Left, Swing_Left + 50);  //45
      delay(200);
      servoWrite(chanal_Swing_Left, Swing_Left - 50);    //45
      servoWrite(chanal_Swing_Right, Swing_Right - 50);  //45
      delay(200);
      servoCloseRight();
      delay(150);
      servoWrite(chanal_Gripper_Left, Open_Left);
      delay(150);
      swing_current_degree[0] = Swing_Left + 50;
      swing_current_degree[1] = Swing_Right + switch_degree;
      servoWrite(chanal_Swing_Left, swing_current_degree[0]);
      servoWrite(chanal_Swing_Right, swing_current_degree[1]);
      switch_flag = 0;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void switchGripper(char from_gripper, char to_gripper) {
  if (from_gripper == 'l' && to_gripper == 'r') switch_flag = 1;
  else if (from_gripper == 'r' && to_gripper == 'l') switch_flag = -1;
}


void swingGripper(char gripper, int degree) {
  if (gripper == 'l') {
    swing_current_degree[0] = degree;
    servoWrite(chanal_Swing_Left, swing_current_degree[0]);
  } else if (gripper == 'r') {
    swing_current_degree[1] = degree;
    servoWrite(chanal_Swing_Right, swing_current_degree[1]);
  }
}

void liftLoop(void *pvParameters) {
  const int CLK = 39;
  const int DT = 36;
  float error, previous_error = 0, integral = 0, derivative;
  float p_value, i_value, d_value, motor_speed;
  float Kp = 3.0, Ki = 0.001, Kd = 0.05;

  ESP32Encoder encoder;
  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(0);

  long last_encoder_count = 0;
  unsigned long last_change_time = millis();
  const unsigned long timeout_ms = 500;

  int last_lift_target = lift_target;
  bool stopped_due_to_timeout = false;

  while (1) {
    long current_count = encoder.getCount() / 2;
    error = current_count - lift_target;

    // ตรวจจับการเปลี่ยนแปลงของ encoder
    if (abs(abs(current_count) - abs(last_encoder_count)) > 5) {
      last_change_time = millis();
      last_encoder_count = current_count;
    }

    // ตรวจสอบว่ามีการเปลี่ยนแปลง lift_target หรือไม่
    if (lift_target != last_lift_target) {
      // หากเคยหยุดจาก timeout ให้เริ่มใหม่
      stopped_due_to_timeout = false;
      last_change_time = millis();
      integral = 0;
      previous_error = 0;
      last_lift_target = lift_target;
    }

    // หยุดหาก encoder ไม่ขยับเป็นระยะเวลาหนึ่ง
    if (!stopped_due_to_timeout && millis() - last_change_time > timeout_ms) {
      motorStop();
      stopped_due_to_timeout = true;
    }

    // หากอยู่ในสถานะหยุดจาก timeout ให้รอจน lift_target เปลี่ยนก่อนจะกลับมาทำงาน
    if (stopped_due_to_timeout) {
      vTaskDelay(10 / portTICK_PERIOD_MS);
      continue;
    }

    // PID control
    p_value = Kp * error;
    integral += error;
    i_value = Ki * integral;
    derivative = error - previous_error;
    d_value = Kd * derivative;
    motor_speed = p_value + i_value + d_value;

    motor_speed = constrain(motor_speed, -255, 100);

    if (abs(error) >= 5)
      motorWrite(3, motor_speed);
    else
      motorStop();

    previous_error = error;
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void lift(int position) {
  if (position > 19) position = 19;
  lift_target = position * 30;
  if (lift_target > 900) lift_target = 900;
}

void moveToCan(int distance) {
  vTaskResume(sonarTaskHandle);
  delay(10);
  unsigned long int timer = millis();
  while (readSonar() > distance || millis() - timer <= 500) FF(20);
  FF(15,50);
  motorStop();
  // delay(200);
  // BB(20,50);
  // motorStop();
  vTaskSuspend(sonarTaskHandle);
}
void moveToCan15(int distance) {
  vTaskResume(sonarTaskHandle);
  delay(10);
  unsigned long int timer = millis();
  while (readSonar() > distance || millis() - timer <= 500) FF(14);
  FF(12,50);
  motorStop();
  // delay(200);
  // BB(20,50);
  // motorStop();
  vTaskSuspend(sonarTaskHandle);
}

void moveToCan0(int distance) {
  unsigned long int timer = millis();
  int current_distance = 0;
  while (current_distance == -1 || current_distance > distance || millis() - timer <= 500) { current_distance = readCanDistance(); FF(20);}
  FF(15, MoveCanZeroTimer);
  motorStop();
}
void moveToCanTime(int time) {
  unsigned long int timer = millis();
  while (millis() - timer < time) FF(15);
  motorStop();
}

void shakeGripper(char gripper) {
  int increment = 1;
  int delayTime = 5;
  int swingRange = 25;
  for (int i = 0; i < 3; i++) {
    if (gripper == 'l' || gripper == 'a') {
      for (int i = 0; i <= swingRange; i += increment) {
        servoWrite(chanal_Swing_Left, swing_current_degree[0] - i);
        if (gripper == 'a') servoWrite(chanal_Swing_Right, swing_current_degree[1] - i);
        delay(delayTime);
      }
      for (int i = 0; i <= swingRange * 2; i += increment) {
        servoWrite(chanal_Swing_Left, swing_current_degree[0] - swingRange + i);
        if (gripper == 'a') servoWrite(chanal_Swing_Right, swing_current_degree[1] - swingRange + i);
        delay(delayTime);
      }
      for (int i = 0; i <= swingRange; i += increment) {
        servoWrite(chanal_Swing_Left, swing_current_degree[0] + swingRange - i);
        if (gripper == 'a') servoWrite(chanal_Swing_Right, swing_current_degree[1] + swingRange - i);
        delay(delayTime);
      }
    }
    if (gripper == 'r' || gripper == 'a') {
      for (int i = 0; i <= swingRange; i += increment) {
        servoWrite(chanal_Swing_Right, swing_current_degree[1] - i);
        if (gripper == 'a') servoWrite(chanal_Swing_Left, swing_current_degree[0] - i);
        delay(delayTime);
      }
      for (int i = 0; i <= swingRange * 2; i += increment) {
        servoWrite(chanal_Swing_Right, swing_current_degree[1] - swingRange + i);
        if (gripper == 'a') servoWrite(chanal_Swing_Left, swing_current_degree[0] - swingRange + i);
        delay(delayTime);
      }
      for (int i = 0; i <= swingRange; i += increment) {
        servoWrite(chanal_Swing_Right, swing_current_degree[1] + swingRange - i);
        if (gripper == 'a') servoWrite(chanal_Swing_Left, swing_current_degree[0] + swingRange - i);
        delay(delayTime);
      }
    }
  }
}

void dropCan(char gripper) {
  delay(50);
  if (gripper == 'l') {
    for(int i=Close_Left;i>=Close_Left-10;i--){servoWrite(chanal_Gripper_Left, i);delay(10);}
    shakeGripper('l');
    delay(200);
    //servoOpenLeft();
    for(int i=Close_Left-10;i>=Open_Left-10;i--){servoWrite(chanal_Gripper_Left, i);delay(5);}
    delay(100);
  } else if (gripper == 'r') {
    for(int i=Close_Right;i>=Close_Right-10;i--){servoWrite(chanal_Gripper_Right, i);delay(10);}
    delay(100);
    shakeGripper('r');
    delay(200);
    //servoOpenRight();
    for(int i=Close_Right-10;i>=Open_Right-10;i--){servoWrite(chanal_Gripper_Right, i);delay(15);}
    delay(100);
  } else if (gripper == 'a') {
    for(int i=Close_Right;i>=Close_Right-10;i--){servoWrite(chanal_Gripper_Right, i);delay(15);}
    for(int i=Close_Left;i>=Close_Left-10;i--){servoWrite(chanal_Gripper_Left, i);delay(15);}
    shakeGripper('a');
    delay(200);
    //servoOpenLeft();
    for (int i = Close_Left-10; i > Open_Left-10; i--) {
      servoWrite(chanal_Gripper_Left, i);
      delay(15);
    }
    //servoOpenRight();
    for (int i = Close_Right-10; i > Open_Right-10; i--) {
      servoWrite(chanal_Gripper_Right, i);
      delay(15);
    }
    delay(100);
  }
}

void dropCan(char gripper, int PrevDrop) {
  delay(50);
  if (gripper == 'l') {
    for(int i=Close_Left;i>=Close_Left-9;i--){servoWrite(chanal_Gripper_Left, i);delay(10);}
    delay(100);
    lift(PrevDrop + 2);
    delay(200);
    shakeGripper('l');
    delay(200);
    //servoOpenLeft();
    for(int i=Close_Left-10;i>=Open_Left-10;i--){servoWrite(chanal_Gripper_Left, i);delay(5);}
    delay(100);
  } else if (gripper == 'r') {
    for(int i=Close_Right;i>=Close_Right-10;i--){servoWrite(chanal_Gripper_Right, i);delay(10);}
    delay(100);
    lift(PrevDrop + 4);
    delay(200);
    shakeGripper('r');
    delay(200);
    //servoOpenRight();
    for(int i=Close_Right-10;i>=Open_Right-10;i--){servoWrite(chanal_Gripper_Right, i);delay(15);}
    delay(100);
  } else if (gripper == 'a') {
    for(int i=Close_Right;i>=Close_Right-10;i--){servoWrite(chanal_Gripper_Right, i);delay(15);}
    for(int i=Close_Left;i>=Close_Left-9;i--){servoWrite(chanal_Gripper_Left, i);delay(15);}
    lift(PrevDrop + 2);
    shakeGripper('a');
    delay(200);
    //servoOpenLeft();
    for (int i = Close_Left-10; i > Open_Left-10; i--) {
      servoWrite(chanal_Gripper_Left, i);
      delay(15);
    }
    //servoOpenRight();
    for (int i = Close_Right-10; i > Open_Right-10; i--) {
      servoWrite(chanal_Gripper_Right, i);
      delay(15);
    }
    delay(100);
  }
}

void pickCan(int pick_height, bool switch_lr) {
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) moveToCan(4);
  else moveToCan0(CanZeroDistance);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
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
    moveToCan(4);
    lift(pick_height + 2);
    delay(400);
    servoCloseRight();
    delay(200);
    vTaskSuspend(switchGripperTaskHandle);
  }
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}


void autoPickCan(int pick_height) {  //swap=1 คือแท่นวางสลับสี r-y-g  ///swap=0 คือแท่นวางปกติ g-y-r
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) {
    moveToCan(SonarDis);
  } else moveToCan0(CanZeroDistance);
  delay(100);
  // // while(1);
  servoCloseLeft();
  servoCloseRight();
  delay(300);  //200
  can_in_gripper[0] = readColor('l');
  can_in_gripper[1] = readColor('r');


  if (can_in_gripper[0] == 'u') {  //แขนซ้ายเจอ u
    for (int i = 0; i < 2; i++) {
      for (int i = Close_Left; i > Open_Left+30; i--) {
        servoWrite(chanal_Gripper_Left, i);
        delay(5);
      }
      delay(300);
      servoCloseLeft();
      delay(300);
      can_in_gripper[0] = readColor('l');
      if (can_in_gripper[0] != 'u') break;
    }
  }


  if (can_in_gripper[1] == 'u') {  //แขนขวาเจอ u
    for (int i = 0; i < 2; i++) {
      for (int i = Close_Right; i > Open_Right+30; i--) {
        servoWrite(chanal_Gripper_Right, i);
        delay(5);
      }
      delay(300);
      servoCloseRight();
      delay(300);
      can_in_gripper[1] = readColor('r');
      if (can_in_gripper[1] != 'u') break;
    }
  }


  if (can_in_gripper[0] == 'u') {  //แขนซ้ายเป็น u
    if (can_in_gripper[1] == 'r') {
      can_in_gripper[0] = 'y';
      tft.fillRect(0, 0, 80, 128, 0xffc0);
    }  //yellow
    else if (can_in_gripper[1] == 'y') {
      can_in_gripper[0] = 'g';
      tft.fillRect(0, 0, 80, 128, 0x1d40);
    }  //green
    else if (can_in_gripper[1] == 'g') {
      can_in_gripper[0] = 'r';
      tft.fillRect(0, 0, 80, 128, 0xf800);
    }  //red
  }


  if (can_in_gripper[1] == 'u') {  //แขนขวาเป็น u
    if (can_in_gripper[0] == 'r') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    } else if (can_in_gripper[0] == 'y') {
      can_in_gripper[1] = 'r';
      tft.fillRect(80, 0, 80, 128, 0xf800);
    } else if (can_in_gripper[0] == 'g') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    }
  }

  if (can_in_gripper[0] == can_in_gripper[1] && pick_height >= 0) {  //สีซ้ำกัน

    if (can_in_gripper[0] == 'r') {  //วางแดงขวาก่อน และ เก็บ เหลือเหลืองไว้มือซ้าย
      can_in_gripper[0] = 'p';       //repeat
      can_in_gripper[1] = 'r';       //place right
      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว
      servoOpenLeft();
      // swingGripper('l', Swing_Left + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Left, Open_Left);
      // delay(200);
      // swingGripper('l', Swing_Left + switch_degree);
      // delay(300);
      // can_in_gripper[0] = 'u';
      // can_in_gripper[1] = 'r';

    } else if (can_in_gripper[1] == 'g') {  //วางเขียวซ้ายก่อน และ เหลือเขียวไว้มือขวา
      can_in_gripper[0] = 'l';              //place left
      can_in_gripper[1] = 'p';              //repeat
      servoOpenRight();
      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว
      // swingGripper('r', Swing_Right + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Right, Open_Right);
      // delay(200);
      // swingGripper('r', Swing_Right + switch_degree);
      // delay(300);
      // can_in_gripper[0] = 'l';
      // can_in_gripper[1] = 'u';
    } else if (can_in_gripper[1] == 'y') {  //วางเหลืองซ้ายก่อน และ เหลือเหลืองไว้มือขวา
      can_in_gripper[0] = 'p';              //place center
      can_in_gripper[1] = 'c';              //repeat
      servoOpenLeft();

      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว
      // swingGripper('r', Swing_Right + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Right, Open_Right);
      // delay(200);
      // swingGripper('r', Swing_Right + switch_degree);
      // delay(300);
      // can_in_gripper[0] = 'c';
      // can_in_gripper[1] = 'u';
    }
  } else {  //ถ้าสีด้านซ้าย != ด้านขวา แสดงว่าสีไม่ซ้ำ
    // can in gripper / 0 = LEFT , 1 = Right
    if ((can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') ||  // L:RED / R:GREEN
        (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') ||  // L:YELLOW / R:GREEN
        (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y')) {  // L:RED / R:YELLOW
      delay(200);
      lift(pick_height + 2);
      delay(400);
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      swingGripper('l', Swing_Left - (switch_degree + 13));
      delay(200);
      // servoWrite(chanal_Gripper_Left, Open_Left);
      servoOpenLeft();
      delay(200);
      swingGripper('l', Swing_Left - (switch_degree));
      delay(200);
      BB(30, 400);
      switchGripper('r', 'l');
      delay(1200);
      servoWrite(chanal_Gripper_Right, Open_Right);
      swingGripper('r', Swing_Right - (switch_degree + 10));
      lift(pick_height + 4);
      if (pick_height != 0) {
      moveToCan(SonarDis);
      }else{FF(30,400);}
      lift(pick_height + 2);
      delay(400);
      servoCloseRight();
      delay(200);
      vTaskSuspend(switchGripperTaskHandle);
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'r';
      }
      if (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'c';
      }
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y') {
        can_in_gripper[0] = 'c';
        can_in_gripper[1] = 'r';
      }
    } else {  //ถ้าไม่ซ้ำทั้งสองข้างและไม่สลับ จะแทนตัวแปรลงไปในมือ ซ้าย ขวา เลย
      //Left
      if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'r';
      else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
      else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
      //Right
      if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'r';
      else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'l';
      else if (can_in_gripper[1] == 'y') can_in_gripper[1] = 'c';
    }
  }
  delay(200);
  lift(pick_height + 2);
  delay(400);
  // delay(10000000);
  // while(1);
  BB(30, 790);
  lift(2);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(300);
  servoOpenLeft();
  servoOpenRight();
  delay(delayALL);
  lift(0);
  delay(delayALL);
  FF(15, 250);
  delay(delayALL);
  servoCloseRight();
  servoCloseLeft();
  delay(delayALL);
  lift(2);
  delay(delayALL);
  BB(15, 250);
}


void PickCanTest(int pick_height) {  //swap=1 คือแท่นวางสลับสี r-y-g  ///swap=0 คือแท่นวางปกติ g-y-r
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);

  servoCloseLeft();
  servoCloseRight();
  delay(300);  //200

  can_in_gripper[0] = readColor('l');
  can_in_gripper[1] = readColor('r');
  if (can_in_gripper[0] == 'u') {  //แขนซ้ายเจอ u
    for (int i = 0; i < 2; i++) {
      servoOpenLeft();
      delay(300);
      servoCloseLeft();
      delay(300);
      can_in_gripper[0] = readColor('l');
      if (can_in_gripper[0] != 'u') break;
    }
  }
  if (can_in_gripper[1] == 'u') {  //แขนขวาเจอ u
    for (int i = 0; i < 2; i++) {
      servoOpenRight();
      delay(300);
      servoCloseRight();
      delay(300);
      can_in_gripper[1] = readColor('r');
      if (can_in_gripper[1] != 'u') break;
    }
  }
  if (can_in_gripper[0] == 'u') {  //แขนซ้ายเป็น u
    if (can_in_gripper[1] == 'r') {
      can_in_gripper[0] = 'y';
      tft.fillRect(0, 0, 80, 128, 0xffc0);
    }  //yellow
    else if (can_in_gripper[1] == 'y') {
      can_in_gripper[0] = 'g';
      tft.fillRect(0, 0, 80, 128, 0x1d40);
    }  //green
    else if (can_in_gripper[1] == 'g') {
      can_in_gripper[0] = 'r';
      tft.fillRect(0, 0, 80, 128, 0xf800);
    }  //red
  }
  if (can_in_gripper[1] == 'u') {  //แขนขวาเป็น u
    if (can_in_gripper[0] == 'r') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    } else if (can_in_gripper[0] == 'y') {
      can_in_gripper[1] = 'r';
      tft.fillRect(80, 0, 80, 128, 0xf800);
    } else if (can_in_gripper[0] == 'g') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    }
  }

  if (can_in_gripper[0] == can_in_gripper[1] && pick_height >= 0) {  //สีซ้ำกัน

    if (can_in_gripper[0] == 'r') {  //วางแดงขวาก่อน และ เก็บ เหลือเหลืองไว้มือซ้าย
      can_in_gripper[0] = 'p';       //repeat
      can_in_gripper[1] = 'r';       //place right
      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว
      servoOpenLeft();
      // swingGripper('l', Swing_Left + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Left, Open_Left);
      // delay(200);
      // swingGripper('l', Swing_Left + switch_degree);
      // delay(300);
      // can_in_gripper[0] = 'u';
      // can_in_gripper[1] = 'r';

    } else if (can_in_gripper[1] == 'g') {  //วางเขียวซ้ายก่อน และ เหลือเขียวไว้มือขวา
      can_in_gripper[0] = 'l';              //place left
      can_in_gripper[1] = 'p';              //repeat
      servoOpenRight();
      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว
      // swingGripper('r', Swing_Right + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Right, Open_Right);
      // delay(200);
      // swingGripper('r', Swing_Right + switch_degree);
      // delay(300);
      // can_in_gripper[0] = 'l';
      // can_in_gripper[1] = 'u';
    } else if (can_in_gripper[1] == 'y') {  //วางเหลืองซ้ายก่อน และ เหลือเหลืองไว้มือขวา
      can_in_gripper[0] = 'p';              //place center
      can_in_gripper[1] = 'c';              //repeat
      servoOpenLeft();

      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว
      // swingGripper('r', Swing_Right + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Right, Open_Right);
      // delay(200);
      // swingGripper('r', Swing_Right + switch_degree);
      // delay(300);
      // can_in_gripper[0] = 'c';
      // can_in_gripper[1] = 'u';
    }
  } else {  //ถ้าสีด้านซ้าย != ด้านขวา แสดงว่าสีไม่ซ้ำ
    // can in gripper / 0 = LEFT , 1 = Right
    if ((can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') ||  // L:RED / R:GREEN
        (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') ||  // L:YELLOW / R:GREEN
        (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y')) {  // L:RED / R:YELLOW
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      swingGripper('l', Swing_Left - (switch_degree + 13));
      delay(200);
      servoWrite(chanal_Gripper_Left, Open_Left);
      delay(200);
      swingGripper('l', Swing_Left - (switch_degree));
      delay(200);
      BB(30, 400);
      switchGripper('r', 'l');
      delay(1200);
      servoWrite(chanal_Gripper_Right, Open_Right);
      swingGripper('r', Swing_Right - (switch_degree + 10));
      lift(pick_height + 4);
      moveToCan(3);
      lift(pick_height + 2);
      delay(400);
      servoCloseRight();
      delay(200);
      vTaskSuspend(switchGripperTaskHandle);
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'r';
      }
      if (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'c';
      }
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y') {
        can_in_gripper[0] = 'c';
        can_in_gripper[1] = 'r';
      }
    } else {  //ถ้าไม่ซ้ำทั้งสองข้างและไม่สลับ จะแทนตัวแปรลงไปในมือ ซ้าย ขวา เลย
      //Left
      if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'r';
      else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
      else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
      //Right
      if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'r';
      else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'l';
      else if (can_in_gripper[1] == 'y') can_in_gripper[1] = 'c';
    }
  }

  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(400);
}



void autoPickCan(int pick_height,int swap) {  //swap=1 คือแท่นวางสลับสี r-y-g  ///swap=0 คือแท่นวางปกติ g-y-r
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) {
    moveToCan(SonarDis);
  } else moveToCan0(CanZeroDistance);
  delay(100);
  // // while(1);
  servoCloseLeft();
  servoCloseRight();
  delay(300);
  can_in_gripper[0] = readColor('l');
  can_in_gripper[1] = readColor('r');
  if (can_in_gripper[0] == 'u') {  //แขนซ้ายเจอ u
    for (int i = 0; i < 2; i++) {
      servoOpenLeft();
      delay(300);
      servoCloseLeft();
      delay(300);
      can_in_gripper[0] = readColor('l');
      if (can_in_gripper[0] != 'u') break;
    }
  }
  if (can_in_gripper[1] == 'u') {  //แขนขวาเจอ u
    for (int i = 0; i < 2; i++) {
      servoOpenRight();
      delay(300);
      servoCloseRight();
      delay(300);
      can_in_gripper[1] = readColor('r');
      if (can_in_gripper[1] != 'u') break;
    }
  }
  if (can_in_gripper[0] == 'u') {  //แขนซ้ายเป็น u
    if (can_in_gripper[1] == 'r') {
      can_in_gripper[0] = 'y';
      tft.fillRect(0, 0, 80, 128, 0xffc0);
    }  //yellow
    else if (can_in_gripper[1] == 'y') {
      can_in_gripper[0] = 'g';
      tft.fillRect(0, 0, 80, 128, 0x1d40);
    }  //green
    else if (can_in_gripper[1] == 'g') {
      can_in_gripper[0] = 'r';
      tft.fillRect(0, 0, 80, 128, 0xf800);
    }  //red
  }
  if (can_in_gripper[1] == 'u') {  //แขนขวาเป็น u
    if (can_in_gripper[0] == 'r') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    } else if (can_in_gripper[0] == 'y') {
      can_in_gripper[1] = 'r';
      tft.fillRect(80, 0, 80, 128, 0xf800);
    } else if (can_in_gripper[0] == 'g') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    }
  }
  if (swap == 1) {
    if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'g';
    else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'r';
    if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'g';
    else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'r';
  }
  if (can_in_gripper[0] == can_in_gripper[1] && pick_height >= 0) {  //สีซ้ำกัน

    if (can_in_gripper[0] == 'r') {  //วางแดงขวาก่อน และ เก็บ เหลือเหลืองไว้มือซ้าย
      can_in_gripper[0] = 'p';       //repeat
      can_in_gripper[1] = 'r';       //place right
      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว

      servoOpenLeft();
      // swingGripper('l', Swing_Left + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Left, Open_Left);
      // delay(200);
      // swingGripper('l', Swing_Left + switch_degree);
      delay(300);
      can_in_gripper[0] = 'u';
      can_in_gripper[1] = 'r';

    } else if (can_in_gripper[1] == 'g') {  //วางเขียวซ้ายก่อน และ เหลือเขียวไว้มือขวา
      can_in_gripper[0] = 'l';              //place left
      can_in_gripper[1] = 'p';              //repeat
      servoOpenRight();

      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว
      // swingGripper('r', Swing_Right + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Right, Open_Right);
      // delay(200);
      // swingGripper('r', Swing_Right + switch_degree);
      // delay(300);
      // can_in_gripper[0] = 'l';
      // can_in_gripper[1] = 'u';
    } else if (can_in_gripper[1] == 'y') {  //วางเหลืองซ้ายก่อน และ เหลือเหลืองไว้มือขวา
      can_in_gripper[0] = 'p';              //place center
      can_in_gripper[1] = 'c';              //repeat
      servoOpenLeft();

      //ให้ข้างนึงไม่เจอแล้ว เอาแดงวางขวาข้างเดียว
      // swingGripper('r', Swing_Right + switch_degree + 10);
      // delay(200);
      // servoWrite(chanal_Gripper_Right, Open_Right);
      // delay(200);
      // swingGripper('r', Swing_Right + switch_degree);
      // delay(300);
      // can_in_gripper[0] = 'c';
      // can_in_gripper[1] = 'u';
    }
  } else {  //ถ้าสีด้านซ้าย != ด้านขวา แสดงว่าสีไม่ซ้ำ
    // can in gripper / 0 = LEFT , 1 = Right
    if ((can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') ||  // L:RED / R:GREEN
        (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') ||  // L:YELLOW / R:GREEN
        (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y')) {  // L:RED / R:YELLOW
      vTaskResume(switchGripperTaskHandle);
      delay(10);

      lift(pick_height + 2);
      delay(400);

      swingGripper('l', Swing_Left - (switch_degree + 13));
      delay(200);
      // servoWrite(chanal_Gripper_Left, Open_Left);
      servoOpenLeft();
      delay(200);
      swingGripper('l', Swing_Left - (switch_degree));
      delay(200);
      BB(30, 400);
      switchGripper('r', 'l');
      delay(1200);
      servoWrite(chanal_Gripper_Right, Open_Right);
      swingGripper('r', Swing_Right - (switch_degree + 10));
      lift(pick_height + 4);
      if (pick_height != 0) {
      moveToCan(SonarDis);
      }else{FF(30,400);}
      lift(pick_height + 2);
      delay(400);
      servoCloseRight();
      delay(200);
      vTaskSuspend(switchGripperTaskHandle);
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'r';
      }
      if (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'c';
      }
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y') {
        can_in_gripper[0] = 'c';
        can_in_gripper[1] = 'r';
      }
    } else {  //ถ้าไม่ซ้ำทั้งสองข้างและไม่สลับ จะแทนตัวแปรลงไปในมือ ซ้าย ขวา เลย
      //Left
      if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'r';
      else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
      else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
      //Right
      if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'r';
      else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'l';
      else if (can_in_gripper[1] == 'y') can_in_gripper[1] = 'c';
    }
  }
  // delay(10000000);
  // while(1);
  delay(300);  //200
  lift(pick_height + 2);
  BB(30, 790);
  lift(2);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(300);
  servoOpenLeft();
  servoOpenRight();
  delay(delayALL);
  lift(0);
  delay(delayALL);
  FF(15, 250);
  delay(delayALL);
  servoCloseRight();
  servoCloseLeft();
  delay(delayALL);
  lift(2);
  delay(delayALL);
  BB(15, 250);
}



void autoPickCanTime(int time) {  //Grip Low
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(0);
  moveToCanTime(time);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
  // while(1);
  delay(200);
  lift(2);
  delay(300);
  can_in_gripper[0] = readColor('l');
  can_in_gripper[1] = readColor('r');
  if (can_in_gripper[0] == can_in_gripper[1]) {
    if (can_in_gripper[0] == 'r') {
      servoWrite(chanal_Gripper_Left, Open_Left);
      delay(200);
      can_in_gripper[0] = 'u';
      can_in_gripper[1] = 'r';
    } else {
      servoWrite(chanal_Gripper_Right, Open_Right);
      delay(200);
      if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
      else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
      can_in_gripper[1] = 'u';
    }
  } else {
    if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'r';
    else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
    else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
    if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'r';
    else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'l';
    else if (can_in_gripper[1] == 'y') can_in_gripper[1] = 'c';
  }

  lift(3);
  delay(300);
  BB(30, 400);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}

void placeCan1(int drop_height, int distance, char from_gripper, char drop_point) {
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
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
}

void placeCan2(int drop_height, int distance, char left_gripper, char right_gripper) {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  lift(drop_height + 3);
  if (left_gripper == 'r' && right_gripper == 'l') {
    moveToCan(distance + 5);
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
    lift(drop_height + 3);
    moveToCan(distance + 5);
    servoCloseRight();
    delay(200);
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
    vTaskSuspend(switchGripperTaskHandle);
    BB(30, 500);
    placeCan1(drop_height, distance, 'l', 'l');
    BB(30, 100);
    placeCan1(drop_height, distance, 'r', 'r');
  } else {
    if (left_gripper == 'l' && right_gripper == 'r') {
      placeCan1(drop_height, distance, 'l', 'l');
      BB(30, 100);
      placeCan1(drop_height, distance, 'r', 'r');
    } else if (left_gripper == 'l' && right_gripper == 'c') {
      placeCan1(drop_height, distance, 'r', 'c');
      BB(30, 100);
      placeCan1(drop_height, distance, 'l', 'l');
    } else if (left_gripper == 'c' && right_gripper == 'r') {
      placeCan1(drop_height, distance, 'l', 'c');
      BB(30, 100);
      placeCan1(drop_height, distance, 'r', 'r');
    } else {
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      if (left_gripper == 'c') {
        swingGripper('l', Swing_Left - (switch_degree + 10));
        swingGripper('r', Swing_Right + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('l');
        delay(200);
        BB(30, 400);
        lift(drop_height + 3);
        switchGripper('r', 'l');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('r', Swing_Right + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('l');
      } else if (right_gripper == 'c') {
        swingGripper('r', Swing_Right - (switch_degree + 10));
        swingGripper('l', Swing_Left + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('r');
        delay(200);
        BB(30, 400);
        lift(drop_height + 3);
        switchGripper('l', 'r');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('l', Swing_Left + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('r');
      }
    }
  }
  delay(200);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
}

void placeCanMix(int drop_height, int distance, char from_gripperL, char drop_pointL, char from_gripperR, char drop_pointR) {
  bool switch_can = 0;
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  if (drop_height != 15) {
    lift(drop_height + 3);
  } else {
    lift(drop_height + 5);
  }
  if (from_gripperL == 'l' && drop_pointL == 'l') {
    swingGripper('l', Swing_Left + switch_degree - 20);
    //swingGripper('r', Swing_Right + 90);
  } else if (from_gripperL == 'l' && drop_pointL == 'c') {
    swingGripper('l', Swing_Left - (switch_degree + 10));
    //swingGripper('r', Swing_Right + 90);
  }
  if (from_gripperR == 'r' && drop_pointR == 'r') {
    //swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right + switch_degree - 20);  //-10
  } else if (from_gripperR == 'r' && drop_pointR == 'c') {
    //swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right - (switch_degree + 10));  //+10
  }
  moveToCan(distance);
  FF(10, MoveTimerPlace);
  motorStop();
  lift(drop_height);
  delay(300);
  //
  dropCan('a');
  //
  delay(200);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
}


void autoPlaceCan2(int drop_height, char left_gripper, char right_gripper) {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  if(drop_height==10) lift(drop_height + 5);
  else lift(drop_height + 5);
  
  if (left_gripper == 'r' && right_gripper == 'l') {  //สลับ
    moveToCan(place_left_center + 5);
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    swingGripper('l', Swing_Left - (switch_degree + 13));
    delay(400);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(400);
    swingGripper('l', Swing_Left - switch_degree);
    delay(500);
    BB(30, 400);
    switchGripper('r', 'l');
    delay(1200);
    servoWrite(chanal_Gripper_Right, Open_Right);
    swingGripper('r', Swing_Right - (switch_degree + 10));
    lift(drop_height + 3);
    moveToCan(place_left_center + 5);
    servoCloseRight();
    delay(200);
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
    vTaskSuspend(switchGripperTaskHandle);
    BB(30, 500);
    placeCan1(drop_height, place_left_side, 'l', 'l');
    BB(30, 100);
    placeCan1(drop_height, place_right_side, 'r', 'r');
  } else {
    if (left_gripper == 'l' && right_gripper == 'r') {
      if(PlaceBoth!=true){
      placeCan1(drop_height, place_left_side, 'l', 'l');
      BB(30, 100);
      placeCan1(drop_height, place_right_side, 'r', 'r');}

      else placeCanMix(drop_height, 5.0 ,'l', 'l', 'r', 'r');
      } 
    
    else if (left_gripper == 'l' && right_gripper == 'c') {
      if(PlaceBoth!=true)
      {placeCan1(drop_height, place_right_center, 'r', 'c');
      BB(30, 100);
      placeCan1(drop_height, place_left_side, 'l', 'l');}
      else placeCanMix(drop_height, 5.0 ,'l', 'l', 'r', 'c');
      
    } else if (left_gripper == 'c' && right_gripper == 'r') {
      if(PlaceBoth!=true){
      placeCan1(drop_height, place_left_center, 'l', 'c');
      BB(30, 100);
      placeCan1(drop_height, place_right_side, 'r', 'r');}
      else placeCanMix(drop_height, 5.0 ,'l', 'c', 'r', 'r');
    } else {
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      if (left_gripper == 'c') {
        swingGripper('l', Swing_Left - (switch_degree + 10));
        swingGripper('r', Swing_Right + 90);
        moveToCan(place_left_center);
        lift(drop_height);
        delay(200);
        dropCan('l');
        delay(200);
        BB(30, 400);
        lift(drop_height + 3);
        switchGripper('r', 'l');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('r', Swing_Right + 90);
        moveToCan(place_left_side);
        lift(drop_height);
        delay(200);
        dropCan('l');
      } else if (right_gripper == 'c') {
        swingGripper('r', Swing_Right - (switch_degree + 10));
        swingGripper('l', Swing_Left + 90);
        moveToCan(place_right_center);
        lift(drop_height);
        delay(200);
        dropCan('r');
        delay(200);
        BB(30, 400);
        lift(drop_height + 3);
        switchGripper('l', 'r');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('l', Swing_Left + 90);
        moveToCan(place_right_side);
        lift(drop_height);
        delay(200);
        dropCan('r');
      }
    }
  }
  delay(200);
  BB(30, 450);
  
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
}

void autoPlaceCan(int drop_height) {  //วางอัตโนมัติ
       if(drop_height==5) {MoveTimerPlace=150; /*place_left_side = 155;place_right_side = 155;*/}
  else if(drop_height==10){MoveTimerPlace=156; /*place_left_side = 155;place_right_side = 155;*/}
  else if(drop_height==15){MoveTimerPlace=152; /*place_left_side = 155;place_right_side = 155;*/}
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);

  //ลงก่อน//
  // if(drop_height==15)lift(1);
  // else lift(2);
  lift(1);
  delay(200);
  servoOpenLeft();
  servoOpenRight();
  delay(200);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(200);
  if(drop_height==15){lift(10);delay(300);}
  //ยกขึ้น// 
  lift(drop_height + 5);
  delay(250);
  //ถ้าซ้ายและขวาเจอทั้งสองข้าง
  if (can_in_gripper[0] != 'u' && can_in_gripper[1] != 'u') {  //ทั้งสองไม่ซ้ำ
    if (can_in_gripper[0] == 'p' || can_in_gripper[1] == 'p')  //ถ้าทั้งสองซ้ำ
    {
      if (can_in_gripper[0] == 'p' && can_in_gripper[1] == 'r') { SimplePlace(drop_height, 'R', 'R'); }
      if (can_in_gripper[0] == 'p' && can_in_gripper[1] == 'c') { SimplePlace(drop_height, 'R', 'Y'); }
      if (can_in_gripper[0] == 'l' && can_in_gripper[1] == 'p') { SimplePlace(drop_height, 'L', 'G'); }
      delay(200);
      BB(30, 400);
      lift(3);
    }

    else autoPlaceCan2(drop_height, can_in_gripper[0], can_in_gripper[1]);
  }
  //ถ้าไม่ใช่ เจอช้างเดียว
  else {
    if (can_in_gripper[0] != 'u') {  //ถ้าซ้ายเจอ
      if (can_in_gripper[0] == 'l') placeCan1(drop_height, place_left_side, 'l', can_in_gripper[0]);
      else if (can_in_gripper[0] == 'c') placeCan1(drop_height, place_left_center, 'l', can_in_gripper[0]);
    } else {  //ถ้าขวาเจอ
      if (can_in_gripper[1] == 'r') placeCan1(drop_height, place_right_side, 'r', can_in_gripper[1]);
      else if (can_in_gripper[1] == 'c') placeCan1(drop_height, place_right_center, 'r', can_in_gripper[1]);
    }
  }
  setupServo();
  //เหลือง-เหลือง  can_in_gripper[0]='c'(วางcenter)  can_in_gripper[1]='p'(ซ้ำ)
}

void SimplePlace(int drop_height, char from, char drop) {
  if (drop == 'R') {
    PlaceCan_R(drop_height, from);
  } else if (drop == 'Y') {
    PlaceCan_Y(drop_height, from);
  } else if (drop == 'G') {
    PlaceCan_G(drop_height, from);
  }
}
void PlaceCan_R(int drop_height, char from) {
  if (from == 'R') {
    placeCan1(drop_height, place_right_side, 'r', 'r');
  } else if (from == 'L') {
    placeCan1(drop_height, place_right_side, 'l', 'r');
  }
}
void PlaceCan_Y(int drop_height, char from) {
  if (from == 'R') {
    placeCan1(drop_height, place_right_center, 'r', 'c');
  } else if (from == 'L') {
    placeCan1(drop_height, place_left_center, 'l', 'c');
  }
}
void PlaceCan_G(int drop_height, char from) {
  if (from == 'R') {
    placeCan1(drop_height, place_left_side, 'r', 'l');
  } else if (from == 'L') {
    placeCan1(drop_height, place_left_side, 'l', 'l');
  }
}


void PickManual(int pick_height,char CL,char CR) {  //swap=1 คือแท่นวางสลับสี r-y-g  ///swap=0 คือแท่นวางปกติ g-y-r
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) {
    moveToCan(4);
  } else moveToCan0(CanZeroDistance);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
  delay(200);  //200
  lift(pick_height + 2);
  delay(300);
  can_in_gripper[0]=CL;
  can_in_gripper[1]=CR;
  if (can_in_gripper[0] == 'u') {  //แขนซ้ายเป็น u
    if (can_in_gripper[1] == 'r') {
      can_in_gripper[0] = 'y';
      tft.fillRect(0, 0, 80, 128, 0xffc0);
    }  //yellow
    else if (can_in_gripper[1] == 'y') {
      can_in_gripper[0] = 'g';
      tft.fillRect(0, 0, 80, 128, 0x1d40);
    }  //green
    else if (can_in_gripper[1] == 'g') {
      can_in_gripper[0] = 'r';
      tft.fillRect(0, 0, 80, 128, 0xf800);
    }  //red
  }
  if (can_in_gripper[1] == 'u') {  //แขนขวาเป็น u
    if (can_in_gripper[0] == 'r') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    } else if (can_in_gripper[0] == 'y') {
      can_in_gripper[1] = 'r';
      tft.fillRect(80, 0, 80, 128, 0xf800);
    } else if (can_in_gripper[0] == 'g') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    }
  }

  if (can_in_gripper[0] == can_in_gripper[1] && pick_height >= 0) {  //สีซ้ำกัน

    if (can_in_gripper[0] == 'r') {  //วางแดงขวาก่อน และ เก็บ เหลือเหลืองไว้มือซ้าย
      delay(300);
      can_in_gripper[0] = 'p';
      can_in_gripper[1] = 'r';
      servoWrite(chanal_Gripper_Left, Open_Left);

    } else if (can_in_gripper[1] == 'g') {  //วางเขียวซ้ายก่อน และ เหลือเขียวไว้มือขวา
      can_in_gripper[0] = 'l';              //place left
      can_in_gripper[1] = 'p';              //repeat
      servoWrite(chanal_Gripper_Right, Open_Right);
    } else if (can_in_gripper[1] == 'y') {  //วางเหลืองซ้ายก่อน และ เหลือเหลืองไว้มือขวา
      can_in_gripper[0] = 'p';              //place center
      can_in_gripper[1] = 'c';              //repeat
      // servoWrite(chanal_Gripper_Right, Open_Right);
      servoOpenLeft();
    }
  } else {  //ถ้าสีด้านซ้าย != ด้านขวา แสดงว่าสีไม่ซ้ำ
    // can in gripper / 0 = LEFT , 1 = Right
    if ((can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') ||  // L:RED / R:GREEN
        (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') ||  // L:YELLOW / R:GREEN
        (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y')) {  // L:RED / R:YELLOW
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      swingGripper('l', Swing_Left - (switch_degree + 13));
      delay(200);
      servoWrite(chanal_Gripper_Left, Open_Left);
      delay(200);
      swingGripper('l', Swing_Left - (switch_degree));
      delay(200);
      BB(30, 400);
      switchGripper('r', 'l');
      delay(1200);
      servoWrite(chanal_Gripper_Right, Open_Right);
      swingGripper('r', Swing_Right - (switch_degree + 10));
      lift(pick_height + 4);
      moveToCan(3);
      lift(pick_height + 2);
      delay(400);
      servoCloseRight();
      delay(200);
      vTaskSuspend(switchGripperTaskHandle);
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'r';
      }
      if (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'c';
      }
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y') {
        can_in_gripper[0] = 'c';
        can_in_gripper[1] = 'r';
      }
    } else {  //ถ้าไม่ซ้ำทั้งสองข้างและไม่สลับ จะแทนตัวแปรลงไปในมือ ซ้าย ขวา เลย
      //Left
      if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'r';
      else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
      else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
      //Right
      if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'r';
      else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'l';
      else if (can_in_gripper[1] == 'y') can_in_gripper[1] = 'c';
    }
  }
  // delay(10000000);
  // while(1);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}

void PickManual(int pick_height,char CL,char CR,int swap) {  //swap=1 คือแท่นวางสลับสี r-y-g  ///swap=0 คือแท่นวางปกติ g-y-r
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) {
    moveToCan(4);
  } else moveToCan0(CanZeroDistance);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
  delay(200);  //200
  lift(pick_height + 2);
  delay(300);
  can_in_gripper[0]=CL;
  can_in_gripper[1]=CR;
  if (can_in_gripper[0] == 'u') {  //แขนซ้ายเป็น u
    if (can_in_gripper[1] == 'r') {
      can_in_gripper[0] = 'y';
      tft.fillRect(0, 0, 80, 128, 0xffc0);
    }  //yellow
    else if (can_in_gripper[1] == 'y') {
      can_in_gripper[0] = 'g';
      tft.fillRect(0, 0, 80, 128, 0x1d40);
    }  //green
    else if (can_in_gripper[1] == 'g') {
      can_in_gripper[0] = 'r';
      tft.fillRect(0, 0, 80, 128, 0xf800);
    }  //red
  }
  if (can_in_gripper[1] == 'u') {  //แขนขวาเป็น u
    if (can_in_gripper[0] == 'r') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    } else if (can_in_gripper[0] == 'y') {
      can_in_gripper[1] = 'r';
      tft.fillRect(80, 0, 80, 128, 0xf800);
    } else if (can_in_gripper[0] == 'g') {
      can_in_gripper[1] = 'y';
      tft.fillRect(80, 0, 80, 128, 0xffc0);
    }
  }
  if (swap == 1) {
    if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'g';
    else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'r';
    if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'g';
    else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'r';
  }
  if (can_in_gripper[0] == can_in_gripper[1] && pick_height >= 0) {  //สีซ้ำกัน

    if (can_in_gripper[0] == 'r') {  //วางแดงขวาก่อน และ เก็บ เหลือเหลืองไว้มือซ้าย
      delay(300);
      can_in_gripper[0] = 'p';
      can_in_gripper[1] = 'r';
      servoWrite(chanal_Gripper_Left, Open_Left);

    } else if (can_in_gripper[1] == 'g') {  //วางเขียวซ้ายก่อน และ เหลือเขียวไว้มือขวา
      can_in_gripper[0] = 'l';              //place left
      can_in_gripper[1] = 'p';              //repeat
      servoWrite(chanal_Gripper_Right, Open_Right);
    } else if (can_in_gripper[1] == 'y') {  //วางเหลืองซ้ายก่อน และ เหลือเหลืองไว้มือขวา
      can_in_gripper[0] = 'p';              //place center
      can_in_gripper[1] = 'c';              //repeat
      servoWrite(chanal_Gripper_Right, Open_Right);
    }
  } else {  //ถ้าสีด้านซ้าย != ด้านขวา แสดงว่าสีไม่ซ้ำ
    // can in gripper / 0 = LEFT , 1 = Right
    if ((can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') ||  // L:RED / R:GREEN
        (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') ||  // L:YELLOW / R:GREEN
        (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y')) {  // L:RED / R:YELLOW
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      swingGripper('l', Swing_Left - (switch_degree + 13));
      delay(200);
      servoWrite(chanal_Gripper_Left, Open_Left);
      delay(200);
      swingGripper('l', Swing_Left - (switch_degree));
      delay(200);
      BB(30, 400);
      switchGripper('r', 'l');
      delay(1200);
      servoWrite(chanal_Gripper_Right, Open_Right);
      swingGripper('r', Swing_Right - (switch_degree + 10));
      lift(pick_height + 4);
      moveToCan(3);
      lift(pick_height + 2);
      delay(400);
      servoCloseRight();
      delay(200);
      vTaskSuspend(switchGripperTaskHandle);
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'r';
      }
      if (can_in_gripper[0] == 'y' && can_in_gripper[1] == 'g') {
        can_in_gripper[0] = 'l';
        can_in_gripper[1] = 'c';
      }
      if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'y') {
        can_in_gripper[0] = 'c';
        can_in_gripper[1] = 'r';
      }
    } else {  //ถ้าไม่ซ้ำทั้งสองข้างและไม่สลับ จะแทนตัวแปรลงไปในมือ ซ้าย ขวา เลย
      //Left
      if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'r';
      else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
      else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
      //Right
      if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'r';
      else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'l';
      else if (can_in_gripper[1] == 'y') can_in_gripper[1] = 'c';
    }
  }
  // delay(10000000);
  // while(1);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}