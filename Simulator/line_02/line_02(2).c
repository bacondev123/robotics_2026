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
    fd(100);
    sleep(500);
    
    Mission_1();
    ao();
    system_stop();
}

void loop()
{
    
}

void Mission_1(){
    Skip_Cross_PID(2);
    B112();
}
void B112(){
    Track_Cross_PID_Custom(70f,25f,0.01f,10f);
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

void Track_Cross_PID(){
    
    while(true){
        Read_Sensor();
        if(LL<Ref_LL && RR < Ref_RR){
            break;
        }else
        {trackline_PID(70f,50f,0.05f,20f);
        }
    }
    ao();
}
void Skip_Cross_PID(int count){
    
    for(int i = 1; i <= count; i++){
        Track_Cross_PID();
        Walk_Cross(500);
    }
}
void Track_Cross_PID_Custom(float basespeed, float kp, float ki, float kd){
    
    while(true){
        Read_Sensor();
        if(LL<Ref_LL && RR < Ref_RR){
            break;
        }else
        {trackline_PID(basespeed,kp,ki,kd);
        }
    }
    ao();
}
void Walk_Cross(int time){
    
    fd(100);
    sleep(time);
    ao();
}
