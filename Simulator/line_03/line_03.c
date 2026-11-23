

// --- LEGACY VARIABLES (UNTOUCHED) ---
int Ref_LL = 600;
int Ref_L = 600;
int Ref_C = 600;
int Ref_R = 600;
int Ref_RR = 600;

int LL, L, C, R, RR;

float I = 0;
float previous_error = 0;
float error = 0;

// --- NEW ADVANCED SENSOR ARRAYS & HELPERS ---
int NUM_SENSORS = 5; // Expanded to 5 to match the simulator's LL, L, C, R, RR
int[] sensorPins = new int[] { 0, 1, 2, 3, 4 };
int[] sensorRef = new int[] { 600, 600, 600, 600, 600 }; 
int[] sensorValue = new int[5];

void readSensors() {
  for (int idx = 0; idx < NUM_SENSORS; idx++) {
    sensorValue[idx] = analog(sensorPins[idx]);
  }
}

bool isBlack(int idx) {
  return sensorValue[idx] < sensorRef[idx];
}

bool isWhite(int idx) {
  return sensorValue[idx] >= sensorRef[idx];
}

bool centerDetected() {
  return isBlack(1) || isBlack(2);
}

bool crossFound() {
  readSensors();
  // Using 0 and 4 to match LL and RR
  return sensorValue[0] < sensorRef[0] && sensorValue[4] < sensorRef[4];
}

bool allBlack() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (!isBlack(i)) return false;
  }
  return true;
}

bool allWhite() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (isBlack(i)) return false;
  }
  return true;
}

void setup()  
{
    //RunPath("500W T 500W");
    
    //Function_test();
    
    //Test();
    B414();
    ao();
    system_stop();
}

void loop()
{
    
}
void B112() {trac();}
void B121() {trac();}

void B212() {trac();}
void B221() {trac();}

void B312() {trac2();}
void B321() {trac2();}

void B412() {RunPath("5W L3 T0 2W L3 S");}
void B413() {RunPath("5W L3 T0 2W R2 T0 2W L3 S");}
void B414() {RunPath("5W L3 T0 2W R2 T0 2W R3");}
void B415() {}
void B416() {}
void B421() {}
void B423() {}
void B424() {}
void B425() {}
void B426() {}
void B431() {}
void B432() {}
void B434() {}
void B435() {}
void B436() {}
void B441() {}
void B442() {}
void B443() {}
void B445() {}
void B446() {}
void B451() {}
void B452() {}
void B453() {}
void B454() {}
void B456() {}
void B461() {}
void B462() {}
void B463() {}
void B464() {}
void B465() {}

void B512() {}
void B521() {}

void B612() {}
void B613() {}
void B614() {}
void B621() {}
void B623() {}
void B624() {}
void B631() {}
void B632() {}
void B634() {}
void B641() {}
void B642() {}
void B643() {}

void B712() {}
void B713() {}
void B714() {}
void B721() {}
void B723() {}
void B724() {}
void B731() {}
void B732() {}
void B734() {}
void B741() {}
void B742() {}
void B743() {}
void Test(){
    
}

void trac(){Track_Cross_PID_Custom(70f,25f,0.01f,10f);}
void trac2(){Track_Side_Line_PID_Custom(0, 70f, 25f, 0.01f, 10f);}



void RunPath(string path) {
    // Split the string by spaces to automatically extract each command
    string[] commands = path.Split(' ');

    for (int i = 0; i < commands.Length; i++) {
        string action = commands[i];
        int cmdLen = action.Length;

        // Skip any empty strings caused by extra spaces in the input
        if (cmdLen == 0) continue;

        char firstChar = action[0];
        char lastChar = action[cmdLen - 1];

        // 1. Process custom Walk_Cross timer (e.g., "100W", "250W", or "1W", "5W")
        if (cmdLen >= 2 && firstChar >= '0' && firstChar <= '9' && lastChar == 'W') {
            
            int driveTime = 0;
            
            // Loop through all the numbers before the 'W' and build the integer
            for (int j = 0; j < cmdLen - 1; j++) {
                driveTime = (driveTime * 10) + (action[j] - '0');
            }

            // If accidentally put 1-9 (e.g. "1W" or "5W"), treat it as 100-900
            if (driveTime <= 9) {
                driveTime *= 100;
            }

            Walk_Cross(driveTime);
        }
        // 2. Process single-character commands (S, T, w, W, l, r)
        else if (cmdLen == 1) {
            switch (firstChar) {
                case 'S': Skip_Cross_PID(1); break;
                case 'T': Track_Cross_PID(); break;
                case 'w': Walk_Cross(300);   break;
                case 'W': Walk_Cross(400);   break;
                case 'l': L90(100, 2);       break;
                case 'r': R90(100, 2);       break;
            }
        }
        // 3. Process two-character commands dynamically (e.g., T0-T4, L0-L4, R0-R4)
        else if (cmdLen == 2) {
            char secondChar = action[1];

            // Ensure the second character is a valid number between 0 and 4
            if (secondChar >= '0' && secondChar <= '4') {
                
                // Dynamically convert the character '0'-'4' into an integer 0-4
                int param = secondChar - '0'; 

                switch (firstChar) {
                    case 'T': Track_Side_Line_PID(param); break;
                    case 'L': L90(0, param);              break;
                    case 'R': R90(0, param);              break;
                }
            }
        }
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
        RunPath(" L4 T0 W R1 T0 W L4 T0 W L3");
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
        {trackline_PID(70f,24f,0.03f,12f);
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
  float Kp = 24f; 
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
