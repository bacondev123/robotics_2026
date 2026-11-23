int Ref_LL = 600;
int Ref_L = 600;
int Ref_C = 600;
int Ref_R = 600;
int Ref_RR = 600;

int LL, L, C, R, RR;

float I = 0;
float previous_error = 0;
float error = 0;

void setup()  
{
    skip_close_cross(1,500);
    Mission_1();
    
    ao();
    system_stop();
}

void loop()
{
    
}

void Mission_1(){
    Skip_Cross_PID(2);
    sleep(1500);
    track_cross_PID1();
    Skip_Cross_PID(2);
    /*
    track_PID_loop(2);
    skip_close_cross(1,300);
    R90(200,2);
    */
    //Track_Side_Line_PID(4,70);
}
// PID V3.3 by Phoenix_Editz

float Calculate_PID(float Kp, float Ki, float Kd) {
  float P = error;

  if (Math.Abs(error) <= 1) {
    I += error;
    
    if (I > 100) I = 100;
    else if (I < -100) I = -100;
    
  } else {
    I = 0;
  }

  float D = error - previous_error;
  float PID_Value = (Kp * P) + (Ki * I) + (Kd * D);
  previous_error = error;

  return PID_Value;
}

void Read_Sensor() {
  LL = analog(0);
  L = analog(1);
  C = analog(2);
  R = analog(3);
  RR = analog(4);
}

void Check_Error() {

  Read_Sensor();

  bool s0 = (LL < Ref_LL);
  bool s1 = (L < Ref_L);
  bool s2 = (C < Ref_C);
  bool s3 = (R < Ref_R);
  bool s4 = (RR < Ref_RR);

  if (s0 && s1 && s2 && s3 && s4)
    error = previous_error;

  else if (!s0 && !s1 && !s2 && !s3 && !s4) {  // line lost
    if (previous_error <= 0)
      error = -5;
    else
      error = 5;
  }

  else if (s0 && !s1 && !s2 && !s3 && !s4) error = -4;
  else if (s0 && s1 && !s2 && !s3 && !s4) error = -3;
  else if (!s0 && s1 && !s2 && !s3 && !s4) error = -2;
  else if (!s0 && s1 && s2 && !s3 && !s4) error = -1;
  else if (!s0 && !s1 && s2 && !s3 && !s4) error = 0;
  else if (!s0 && !s1 && s2 && s3 && !s4) error = 1;
  else if (!s0 && !s1 && !s2 && s3 && !s4) error = 2;
  else if (!s0 && !s1 && !s2 && s3 && s4) error = 3;
  else if (!s0 && !s1 && !s2 && !s3 && s4) error = 4;

  else
    error = previous_error;
}

void trackline_PID(float maxspeed, float Kp, float Ki, float Kd) {

  Check_Error();

  float PID_value = Calculate_PID(Kp, Ki, Kd);

  float corner_brake = Math.Abs(error) * (maxspeed/10);
  float current_speed = maxspeed - corner_brake;

  if (current_speed <= 15) {
    current_speed = 15;
  }

  int leftspeed = (int)(current_speed + PID_value);
  int rightspeed =(int)(current_speed - PID_value);

  if (leftspeed > 100) leftspeed = 100;
  else if (leftspeed < -100) leftspeed = -100;
  
  if (rightspeed > 100) rightspeed = 100;
  else if (rightspeed < -100) rightspeed = -100;

  fd2(leftspeed, rightspeed);
}

void PID_Reset() {
  I = 0;
  error = 0;
  previous_error = 0;
}
void track_PID_loop(int count){
    for(int i = 1; i <= count; i++){
        track_cross_PID1();
    }
}
void track_CR(int speed3) {
  while (true) {
    if (analog(3) < Ref_RR) {
      break;
    }
    trackline(speed3);
  }
  ao();
  sleep(500);
}

void track_CL(int speed2) {
  while (true) {
    if (analog(0) < Ref_LL) {
      break;
    }
    trackline(speed2);
  }
  ao();
  sleep(500);
}

void R8(int sensor) {
  R = analog(sensor);
  while (R > Ref_R) {
    sr(30);
    R = analog(sensor);
  }
  ao();
  sleep(200);
}
void L90(int turn, int sensor1){
  sl(100);
  delay(turn);
  ao();
  L = analog(sensor1);
  while(L>Ref_L){
    sl(30);
    L = analog(sensor1);
  }
  ao();delay(300);
}
void R90(int turn1, int sensor2){
  sr(100);delay(turn1);ao(); //ปรับเวลา delay ให้หมุนขวา ให้ analog(3) พ้นเส้นดำมาก่อน
  R = analog(sensor2);  // เก็บค่าที่อ่านได้จาก analog(3)* ถ้าไม่มี โปรแกรมจะไม่ทำงาน
  while(R>Ref_R){  // ถ้าค่า R>Ref_R คือ R เจอพื้นขาว จะทำ
      sr(100);
    R = analog(sensor2);  // เก็บค่าที่อ่านได้จาก analog(3)* ถ้าไม่มี โปรแกรมจะไม่ทำงาน
  }
  ao();delay(300); // stop motor
}
void fd_c(int sensor, int sensor_refval) {
  while (true) {
    if (analog(sensor) < sensor_refval) {
      break;
    }
    fd2(20, 21);
  }
  ao();
  sleep(500);
}
void fd_c2(int sensor) {
  while (true) {
    if (analog(sensor) < Ref_LL) {
      break;
    }
    fd2(20, 35);
  }
  ao();
  sleep(500);
}
void fd_c3(int sensor) {
  while (true) {
    if (analog(sensor) < Ref_LL) {
      break;
    }
    fd2(35, 25);
  }
  ao();
  sleep(500);
}
void trackline(int speed) {
  L = analog(1);
  R = analog(3);
  if (L > Ref_L && R > Ref_RR) {
    fd(speed);
  } else if (L < Ref_L && R > Ref_RR) {
    sl(speed);
  } else if (L > Ref_L && R < Ref_RR) {
    sr(speed);
  }
}
void track_side_line(int speed4, int sensor, int refval) {
  while (true) {
    if (analog(sensor) < refval) {
      break;
    } else {
      trackline(speed4);
    }
  }
}
void Skip_Side_Line(int count, int cross_duration, int line_speed, int sensor, int refval) {
  for (int i = 1; i <= count; i++) {
    track_side_line(line_speed, sensor, refval);
    cross(cross_duration);
    sleep(100);
  }
}



void track_cross_PID1() {
  while (true) {
    if (analog(0) < Ref_LL && analog(4) < Ref_RR) {
      break;
    } else {
      trackline_PID(70f, 25f, 0.01f, 10f);
    }
  }
  ao();
}
void track_cross_PID2() {
  while (true) {
    if (analog(0) < Ref_LL && analog(4) < Ref_RR) {
      break;
    } else {
      trackline_PID(70f, 50f, 0.05f, 20f);
    }
  }
  ao();
}
void Skip_Cross_PID(int count) {
  for (int i = 1; i <= count; i++) {
    track_cross_PID2();
    cross(500);
    sleep(100);
  }
}
void Cross_PID(int count) {
  for (int i = 1; i <= count; i++) {
    cross(500);
    track_cross_PID1();
    sleep(100);
  }
}

void skip_close_cross(int count, int duration) {
  for (int i = 1; i <= count; i++) {
    close_cross_detect();
    cross(duration);
  }
}
void skip_Circle_Right_PID(int count) {
  for (int i = 1; i <= count; i++) {
    Circle_Right_PID();
    cross(100);
  }
}
void skip_Circle_Left_PID(int count) {
  for (int i = 1; i <= count; i++) {
    Circle_Left_PID();
    cross(100);
  }
}
void Circle_Right_PID() {
  while (true) {
    if (analog(3) < Ref_RR) {
      break;
    } else {
      trackline_PID(20f, 12f, 0.05f, 8f);
    }
  }
  ao();
}
void Circle_Left_PID() {
  while (true) {
    if (analog(0) < Ref_LL) {
      break;
    } else {
      trackline_PID(20f, 12f, 0.05f, 8f);
    }
  }
  ao();
}
void close_cross_detect() {
  while (true) {
    if (analog(1) < Ref_L && analog(3) < Ref_R) {
      break;
    } else {
        trackline(100);
    }
  }
  ao();
}

void cross(int time) {
  fd(100);
  sleep(time);
  ao();
}

void track_T(int speed1, int time1) {
  for (int i = 1; i <= time1; i++) {
    trackline(speed1);
  }
  ao();
  sleep(1000);
}
void Skip_Square_Left(int count) {
  for (int i = 1; i <= count; i++) {
    Skip_Side_Line(1, 500, 20, 3, Ref_RR);
    R90(200, 2);
    Skip_Side_Line(1, 500, 20, 0, Ref_LL);
    sleep(200);
  }
}
void Skip_Square_Right(int count) {
  for (int i = 1; i <= count; i++) {
    Skip_Side_Line(1, 525, 20, 0, Ref_LL);
    L90(200, 1);
    sleep(200);
    L90(1,1);
    Skip_Side_Line(1, 500, 20, 3, Ref_RR);
    sleep(200);
  }
}
int get_sensor_ref(int sensor){
  if(sensor == 0) return Ref_LL;
  if(sensor == 1) return Ref_L;
  if(sensor == 2) return Ref_R;
  if(sensor == 3) return Ref_RR;
  return 0;
}
void delay(int time)
{
    sleep(time);
}
void Track_Side_Line_PID_Custom(int sensor, float basespeed, float KpTemp, float KiTemp, float KdTemp){
  int refval = get_sensor_ref(sensor);
  while(true){
    if(analog(sensor) < refval){
      break;
    }else{
      trackline_PID(basespeed, KpTemp, KiTemp, KdTemp);
    }
  }
  PID_Reset();
  ao();
}
void Track_Side_Line_PID(int sensor, float basespeed) {
  // Replace these with your desired constant values or global variables
  float Kp = 1.2f; 
  float Ki = 0.01f;
  float Kd = 0.5f;

  int refval = get_sensor_ref(sensor);

  while(true) {
    if(analog(sensor) < refval) {
      break;
    } else {
      // Calling the PID function with the new local/global constants
      trackline_PID(basespeed, Kp, Ki, Kd);
    }
  }

  PID_Reset();
  ao();
}