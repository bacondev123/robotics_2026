int Default_lift = 3;

void pickCan(int pick_height) {
  BalanceArm('O');
  lift(pick_height);
  if (pick_height != 0) moveToCan(pick_can_distance);
  else moveToCan0(pick_can_floor);
  delay(500);
  FF(10, 250);
  delay(500);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(500);
  lift(pick_height + 3);
  delay(250);
  BB(30, 500);
  lift(Default_lift);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  StableOBJ();
}

void placeCan(int drop_height, char gripper, char drop_point) {
  int delay_time = 250 + (drop_height * 25);
  if (delay_time < 0) delay_time = 0;
  lift(drop_height + 3);
  delay(delay_time);
  switch (gripper) {
    case 'L':
      switch (drop_point) {
        case 'L':
          swingGripper('l', Swing_Left + 10);
          swingGripper('r', Swing_Right + 120);
          break;
        case 'C':
          swingGripper('l', Swing_Left - 45);
          swingGripper('r', Swing_Right + 120);
          break;
        case 'S':
          servoWrite(chanal_Swing_Left, Swing_Left);
          servoWrite(chanal_Swing_Right, Swing_Right + 120);
          break;
      }
      break;

    case 'R':
      switch (drop_point) {
        case 'R':
          swingGripper('l', Swing_Left + 120);
          swingGripper('r', Swing_Right + 10);
          break;
        case 'C':
          swingGripper('l', Swing_Left + 120);
          swingGripper('r', Swing_Right - 45);
          break;
        case 'S':
          servoWrite(chanal_Swing_Left, Swing_Left + 120);
          servoWrite(chanal_Swing_Right, Swing_Right);
          break;
      }
      break;

    case 'A':
      switch (drop_point) {
        case 'A':
          BalanceArm('S');
          break;
      }
      break;
  }

  moveToCan(place_can_distance);
  delay(500);
  FF(10, 250);
  lift(drop_height);
  delay(500);
  DropPosition(gripper);
  delay(250);
  BB(30, 500);
  BalanceArm('S');
  lift(Default_lift);
}

void BalanceArm(char position) {
  switch (position) {
    case 'C':
      servoWrite(chanal_Gripper_Left, Close_Left);
      servoWrite(chanal_Gripper_Right, Close_Right);
      servoWrite(chanal_Swing_Left, Swing_Left - 15);
      servoWrite(chanal_Swing_Right, Swing_Right - 15);
      break;

    case 'O':
      servoWrite(chanal_Swing_Left, Swing_Left);
      servoWrite(chanal_Swing_Right, Swing_Right);
      servoWrite(chanal_Gripper_Left, Open_Left);
      servoWrite(chanal_Gripper_Right, Open_Right);
      break;

    case 'L':
      servoWrite(chanal_Gripper_Left, Close_Left);
      servoWrite(chanal_Gripper_Right, Close_Right);
      servoWrite(chanal_Swing_Left, Swing_Left + 100);
      servoWrite(chanal_Swing_Right, Swing_Right - 30);
      break;

    case 'R':
      servoWrite(chanal_Gripper_Left, Close_Left);
      servoWrite(chanal_Gripper_Right, Close_Right);
      servoWrite(chanal_Swing_Right, Swing_Right + 100);
      servoWrite(chanal_Swing_Left, Swing_Left - 30);
      break;

    case 'S':
      servoWrite(chanal_Swing_Left, Swing_Left);
      servoWrite(chanal_Swing_Right, Swing_Right);
      break;

    case 'W':
      servoWrite(chanal_Gripper_Left, Close_Left);
      servoWrite(chanal_Gripper_Right, Close_Right);
      servoWrite(chanal_Swing_Left, Swing_Left + 100);
      servoWrite(chanal_Swing_Right, Swing_Right + 100);
      break;
  }
  delay(250);
}

void DropPosition(char gripper) {
  switch (gripper) {
    case 'L':
      servoWrite(chanal_Gripper_Left, Close_Left - 10);
      delay(250);
      servoWrite(chanal_Gripper_Left, Open_Left);
      break;

    case 'R':
      servoWrite(chanal_Gripper_Right, Close_Right - 10);
      delay(250);
      servoWrite(chanal_Gripper_Right, Open_Right);
      break;

    case 'A':
      servoWrite(chanal_Gripper_Left, Close_Left - 10);
      servoWrite(chanal_Gripper_Right, Close_Right - 10);
      delay(250);
      servoWrite(chanal_Gripper_Left, Open_Left);
      servoWrite(chanal_Gripper_Right, Open_Right);
      break;
  }
  delay(500);
}

void StableOBJ() {
  BalanceArm('S');
  lift(0);
  BB(10, 500);
  delay(500);
  servoWrite(chanal_Gripper_Left, Close_Left - 30);
  servoWrite(chanal_Gripper_Right, Close_Right - 30);
  delay(250);
  FF(10, 500);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(125);
  lift(Default_lift);
  delay(125);
}

void FF_Enhanced(int speed, float timer) {
  int min_speed = 15;
  int max_speed = abs(speed);
  float kp = 1.0;
  float kd = 1.0;
  int ramp_up = 250;
  int ramp_down = 250;
  float current_speed = min_speed;
  float actual_timer = timer * power_factor;
  if (actual_timer < (ramp_up + ramp_down)) {
    ramp_up = actual_timer / 2.0;
    ramp_down = actual_timer / 2.0;
  }
  unsigned long start_time = millis();
  unsigned long previous_time_loop = start_time;
  float previous_error = current_degree - angleRead(YAW);
  while (1) {
    unsigned long current_time = millis();
    unsigned long elapsed_time = current_time - start_time;
    long remaining_time = (long)actual_timer - (long)elapsed_time;
    float dt = (float)(current_time - previous_time_loop);
    if (dt == 0) dt = 1;
    if (elapsed_time >= actual_timer) {
      motorStop();
      break;
    }
    if (elapsed_time <= ramp_up && ramp_up > 0) {
      current_speed = min_speed + ((float)elapsed_time / ramp_up) * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down && ramp_down > 0) {
      current_speed = min_speed + ((float)remaining_time / ramp_down) * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else {
      current_speed = max_speed;
    }
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = (error - previous_error) / dt;
    int pd_value = round((error * kp) + (derivative * kd));
    int pd_max_allowance = 80;
    if (pd_value > pd_max_allowance) pd_value = pd_max_allowance;
    else if (pd_value < -pd_max_allowance) pd_value = -pd_max_allowance;
    int base_speed = round(current_speed);
    int speed_left = base_speed + pd_value;
    int speed_right = base_speed - pd_value;
    int max_calculated_speed = max(abs(speed_left), abs(speed_right));
    if (max_calculated_speed > 100) {
      speed_left = map(speed_left, -max_calculated_speed, max_calculated_speed, -100, 100);
      speed_right = map(speed_right, -max_calculated_speed, max_calculated_speed, -100, 100);
    }
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    previous_error = error;
    previous_time_loop = current_time;
  }
}

void FF_Enhanced(int speed, float timer, char spin) {
  FF_Enhanced(speed, timer);
  switch (spin) {
    case 'L':
      spinDegree_Enhanced(-90);
      break;

    case 'R':
      spinDegree_Enhanced(90);
      break;
  }
}

void BB_Enhanced(int speed, float timer) {
  int min_speed = 15;
  int max_speed = abs(speed);
  float kp = 1.0;
  float kd = 1.0;
  int ramp_up = 250;
  int ramp_down = 250;
  float current_speed = min_speed;
  float actual_timer = timer * power_factor;
  if (actual_timer < (ramp_up + ramp_down)) {
    ramp_up = actual_timer / 2.0;
    ramp_down = actual_timer / 2.0;
  }
  unsigned long start_time = millis();
  unsigned long previous_time_loop = start_time;
  float previous_error = current_degree - angleRead(YAW);
  while (1) {
    unsigned long current_time = millis();
    unsigned long elapsed_time = current_time - start_time;
    long remaining_time = (long)actual_timer - (long)elapsed_time;
    float dt = (float)(current_time - previous_time_loop);
    if (dt == 0) dt = 1;
    if (elapsed_time >= actual_timer) {
      motorStop();
      break;
    }
    if (elapsed_time <= ramp_up && ramp_up > 0) {
      current_speed = min_speed + ((float)elapsed_time / ramp_up) * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down && ramp_down > 0) {
      current_speed = min_speed + ((float)remaining_time / ramp_down) * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else {
      current_speed = max_speed;
    }
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = (error - previous_error) / dt;
    int pd_value = round((error * kp) + (derivative * kd));
    int pd_max_allowance = 80;
    if (pd_value > pd_max_allowance) pd_value = pd_max_allowance;
    else if (pd_value < -pd_max_allowance) pd_value = -pd_max_allowance;
    int base_speed = -round(current_speed);
    int speed_left = base_speed + pd_value;
    int speed_right = base_speed - pd_value;
    int max_calculated_speed = max(abs(speed_left), abs(speed_right));
    if (max_calculated_speed > 100) {
      speed_left = map(speed_left, -max_calculated_speed, max_calculated_speed, -100, 100);
      speed_right = map(speed_right, -max_calculated_speed, max_calculated_speed, -100, 100);
    }
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    previous_error = error;
    previous_time_loop = current_time;
  }
}

void BB_Enhanced(int speed, float timer, char spin) {
  BB_Enhanced(speed, timer);
  switch (spin) {
    case 'L':
      spinDegree_Enhanced(-90);
      break;

    case 'R':
      spinDegree_Enhanced(90);
      break;
  }
}

void spinDegree_Enhanced(int relative_degree) {
  delay(125);
  unsigned long timer_turn = millis();
  int min_speed = 20;
  int max_speed = 100;
  float kp = 0.8;
  float kd = 1.0;
  float small_angle_threshold = 30.0;
  float stop_threshold = 2.0;
  float target_degree = current_degree + relative_degree;
  while (target_degree > 180)  target_degree -= 360;
  while (target_degree < -180) target_degree += 360;
  float previous_error = 0;
  while (1) {
    float current_angle = angleRead(YAW);
    float error = target_degree - current_angle;
    if (error > 180)       error -= 360;
    else if (error < -180) error += 360;
    if (abs(error) <= stop_threshold) {
      motorStop();
      if (millis() - timer_turn >= 80) {
        break;
      }
    } 
    else if (error > 0 && error < small_angle_threshold) {
      motorWrite(1, min_speed);
      motorWrite(2, -min_speed);
      timer_turn = millis();
    } 
    else if (error < 0 && error > -small_angle_threshold) {
      motorWrite(1, -min_speed);
      motorWrite(2, min_speed);
      timer_turn = millis();
    } 
    else {
      float derivative = error - previous_error;
      if (derivative > 180)       derivative -= 360;
      else if (derivative < -180) derivative += 360;
      int pd_value = round((error * kp) + (derivative * kd));
      if (error > 0) {
        if (pd_value < min_speed) pd_value = min_speed;
        if (pd_value > max_speed) pd_value = max_speed;
      } else {
        if (pd_value > -min_speed) pd_value = -min_speed;
        if (pd_value < -max_speed) pd_value = -max_speed;
      }
      motorWrite(1, pd_value);
      motorWrite(2, -pd_value);
      timer_turn = millis();
    }
    previous_error = error;
  }
  motorStop();
  current_degree = angleRead(YAW);
  delay(125);
}