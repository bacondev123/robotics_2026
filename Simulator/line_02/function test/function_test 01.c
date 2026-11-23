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
    
    //Function_test();
    
    Test();
    ao();
    system_stop();
}

void loop()
{
    
}

void Test(){
    
    Skip_Cross_PID(2);
    B1();
    Skip_Cross_PID(2);
    B3();
    sleep(1000);
    Track_Side_Line_PID_Custom(4, 70f, 25f, 0.01f, 10f);
    Walk_Cross(500);
    L90(300,2);
    Skip_Cross_PID(1);
    L90(200,2);
    Track_Side_Line_PID_Custom(4, 70f, 25f, 0.01f, 10f);
    Walk_Cross(300);
    R90(200,2);
    sleep(500);
    
    B5("2R");
    
}
void RunPath(string path) {
    for (int i = 0; i < path.Length; i++) {
        
        
        string action = path.Substring(i, 1); 

        if      (action == "S") Skip_Cross_PID(1);
        else if (action == "T") Track_Cross_PID(); 
        else if (action == "W") Walk_Cross(300); 
        else if (action == "w") Walk_Cross(400);        
        else if (action == "L") L90(0, 0); 
        else if (action == "R") R90(0, 4); 
        else if (action == "l") L90(100, 2);            
        else if (action == "r") R90(100, 2);            
    }
}
void Function_test(){
    B4("3L");
}
void B1(){
    Track_Cross_PID_Custom(70f,25f,0.01f,10f);
}
void B2(){
    Track_Cross_PID_Custom(70f,25f,0.01f,10f);
}
void B3(){
    Track_Side_Line_PID_Custom(0, 70f, 25f, 0.01f, 10f);
}
void B4(string choice){
    
    if(choice == "L"){
        L90(0,4);
        Track_Side_Line_PID(0);
        Walk_Cross(300);
    }
    else if(choice == "2L"){
        L90(0,4);
        Track_Side_Line_PID(0);
        Walk_Cross(300);
        L90(100,3);
    }
    else if(choice == "3L"){
        L90(0,4);
        Track_Side_Line_PID(0);
        Walk_Cross(300);
        R90(0,1);
        Track_Side_Line_PID(0);
        Walk_Cross(300);
        L90(0,4);
        Track_Side_Line_PID(0);
        Walk_Cross(300);
        L90(100,3);
    }
    
    
}
void B5(string choice){
    
    if (choice == "L"){
        Track_Side_Line_PID(0);
        Walk_Cross(400);
    }
    else if (choice == "R"){
        Track_Side_Line_PID(4);
        Walk_Cross(400);
    }
    else if (choice == "2L"){
        Track_Side_Line_PID(0);
        Walk_Cross(400);
        R90(0,1);
        Track_Side_Line_PID(0);
    }
    else if (choice == "2R"){
        Track_Side_Line_PID(4);
        Walk_Cross(400);
        L90(0,3);
        Track_Side_Line_PID(4);
    }
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
int get_sensor_ref(int sensor){
  if(sensor == 0) return Ref_LL;
  if(sensor == 1) return Ref_L;
  if(sensor == 2) return Ref_C;
  if(sensor == 3) return Ref_R;
  if(sensor == 4) return Ref_RR;
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
void Track_Side_Line_PID(int sensor) {
  
  float basespeed = 70f ; 
  float Kp = 30f; 
  float Ki = 0.03f;
  float Kd = 12f;

  int refval = get_sensor_ref(sensor);

  while(true) {
    if(analog(sensor) < refval) {
      break;
    } else {
      trackline_PID(basespeed, Kp, Ki, Kd);
    }   
  }

  PID_Reset();
  ao();
}
void L90(int turn, int sensor1){
  sl(100);
  delay(turn);
  ao();
  L = analog(sensor1);
  while(L>Ref_L){
    sl(100);
    L = analog(sensor1);
  }
  ao();delay(300);
}
void R90(int turn, int sensor1){
  sr(100);
  delay(turn);
  ao();
  R = analog(sensor1);
  while(R>Ref_R){
    sr(100);
    R = analog(sensor1);
  }
  ao();delay(300);
}
