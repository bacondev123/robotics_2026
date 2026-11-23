
void FACC3() {
  FF_ACC(40, 100, 350);
  FF(100, 450);
  FF(100, 350);
}

void FACC4() {
  FF(40, 350);
  FF(100, 700);  // 450
  FF(40, 350);
}


void BACC3() {
  BB(40, 350);
  BB(100, 450);
  BB(40, 350);
}

void BACC4() {
  BB(40, 350);
  BB(100, 700);  // 450
  BB(40, 350);
}
void FACC3_test() {
  FF_ACC(20, 50, 350);
  FF_ACC(50, 50, 450);
  FF_ACC(50, 20, 350);
}

void FF_ACC(int start_speed, int end_speed, float timer) {
  float kp = 2.8;   // KP 
  float kd = 15.0;  // KD 

  unsigned long timer_forward = millis();
  float previous_error = 0;

  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;

    // If the timer is finished, EXIT the loop.
    // Notice there is NO motorStop() here! It transitions instantly to the next command.
    if (elapsed_time >= timer) {
      break;
    }

    // Smoothly calculate current speed based on time passed
    // This prevents instant speed jumps and saves your motors!
    int current_speed = start_speed + ((float)elapsed_time / timer) * (end_speed - start_speed);

    // PID Calculation to keep the robot driving straight
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;

    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);

    // Limit PD value based on the highest speed we are using
    int limit_speed = max(start_speed, end_speed);
    if (pd_value > limit_speed) pd_value = limit_speed;
    else if (pd_value < -limit_speed) pd_value = -limit_speed;

    int speed_left = current_speed + pd_value;
    int speed_right = current_speed - pd_value;

    motorWrite(1, speed_left);
    motorWrite(2, speed_right);

    previous_error = error;
  }
}