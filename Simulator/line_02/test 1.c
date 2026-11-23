int Ref_L0 = 730;  
int Ref_L1 = 770;  
int Ref_R2 = 890;  
int Ref_R3 = 780;

int L0 = analog(0); 
int L1 = analog(1);
int R2 = analog(2);
int R3 = analog(3);
void setup() {
  mission2();


motorstop();  

}

void loop() {
  // put your main code here, to run repeatedly:

}
void b2() {
  walkline(20, 0);
  Delay(20, 20, 150);
  sl(2, 20, 50);
  walkline(20, 3);
  Delay(20, 20, 200);
  sr(1, 20, 150);
  walkline(20, 0);
  Delay(20, 20, 200);
  sl(2, 20, 150);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(20);
  delay(100);
}

void b1() {
  walkline(20, 0);
  Delay(20, 20, 250);
  sl(2, 20, 150);
  walkline(20, 3);
  Delay(20, 20, 250);
  sr(1, 20, 150);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 150);
  walkline(20, 0);
  Delay(20, 20, 250);
  sl(2, 20, 150);
  walkline(20, 0);
  Delay(20, 20, 250);
  sl(2, 20, 150);
  bk(20);
  delay(100);
  walkline(20, 3);
  Delay(20, 20, 250);
  sr(1, 20, 150);
  bk(20);
  delay(100);
}
void b321() {
  walkline(20, 3);
  Delay(20, 20, 300);
  sr(1, 20, 250);
  walkline(20, 0);
  Delay(20, 20, 300);
  sl(2, 20, 250);
  walkline(20, 0);
  Delay(20, 20, 350);
}

void b312() {
  walkline(20, 0);
  Delay(20, 20, 300);
  sl(2, 20, 250);
  walkline(20, 3);
  Delay(20, 20, 300);
  sr(1, 20, 250);
  walkline(20, 3);
  Delay(20, 20, 250);
}

void b523() {
  walkline(20, 0);
  Delay(20, 20, 300);
  sl(2, 20, 250);
  walkline(20, 0);
  Delay(20, 20, 300);
}

void b521() {
  walkline(20, 3);
  Delay(20, 20, 300);
  sr(1, 20, 250);
  walkline(20, 3);
  Delay(20, 20, 300);
}

void b512() {
  walkline(20, 0);
  Delay(20, 20, 300);
  sl(2, 20, 250);
  walkline(20, 0);
  Delay(20, 20, 250);
  sl(2, 20, 250);
}

void b513() {
  walkline(20, 0);
  Delay(20, 20, 300);
  sl(2, 20, 250);
  track_close_cross(20);
  Delay(20, 20, 250);
  sr(1, 20, 250);
  walkline(20, 0);
  Delay(20, 20, 300);
  sl(20);
  delay(100);
}

void b532() {
  walkline(20, 3);
  Delay(20, 20, 300);
  sr(1, 20, 250);
  walkline(20, 3);
  Delay(20, 20, 250);
  sr(1, 20, 250);
}

void b531() {
  walkline(20, 3);
  Delay(20, 20, 300);
  sr(1, 20, 250);
  walkline(20, 3);
  Delay(20, 20, 250);
  sl(2, 20, 250);
  walkline(20, 3);
  Delay(20, 20, 300);
}

void b712() {
  walkline(20, 1);
  Delay(20, 20, 300);
  sl(2, 20, 250);
  walkline(20, 1);
  Delay(20, 20, 250);
  sl(2, 20, 250);
}
void b713l() {
  walkline(20, 1);
  Delay(20, 20, 300);
  sl(2, 20, 250);
  walkline(20, 1);
  Delay(20, 20, 350);
  sr(1, 20, 250);
  walkline(20, 3);
  Delay(20, 20, 250);
  sl(2, 20, 50);
  walkline(20, 3);
  Delay(20, 20, 350);
}

void b714() {
  walkline(20, 2);
  Delay(20, 20, 300);
  sr(1, 20, 250);
  walkline(20, 2);
  Delay(20, 20, 250);
  sr(1, 20, 250);
}
void b713r() {
  walkline(20, 2);
  Delay(20, 20, 300);
  sr(1, 20, 250);
  walkline(20, 2);
  Delay(20, 20, 350);
  sl(2, 20, 250);
  walkline(20, 0);
  Delay(20, 20, 250);
  sr(1, 20, 50);
  walkline(20, 3);
  Delay(20, 20, 350);
}

void b612() {
  return_base1();
}

void b614() {
  return_base2();
}

void b613l() {
  return_base();
}
void b613r() {
  return_base4();
}

void b4(int version) {

//// M
  if (version == 1) {
    walkline(20, 1);
    Delay(20, 20, 350);
    sl(2, 20, 200);
    track_close_cross(20);
    Delay(20, 20, 285);
    sl(2, 20, 250);
    bk(20);
    delay(100);
  }


  
   if  (version == 2) {
      walkline(20, 1);
      Delay(20, 20, 350);
      sr(1, 20, 200);
      track_close_cross(20);
      Delay(20, 20, 285);
      sr(1, 20, 250);
      bk(20);
      delay(100);
    }
   
   if (version == 3) {
    walkline(20, 1);
    Delay(20, 20, 350);
    sl(2, 20, 200);
    track_close_cross(20);
    Delay(20, 20, 285);
    sr(1, 20, 250);
    walkline(20, 0);
    Delay(20, 20, 350);
    sl(2, 20, 200);
     track_close_cross(20);
    Delay(20, 20, 285);
    sl(2, 20, 250);
    bk(20);
    delay(100);
    
  }

  if (version == 4) {
    walkline(20, 1);
    Delay(20, 20, 350);
    sr(1, 20, 200);
    track_close_cross(20);
    Delay(20, 20, 285);
    sl(2, 20, 250);
    walkline(20, 3);
    Delay(20, 20, 350);
    sr(1, 20, 200);
     track_close_cross(20);
    Delay(20, 20, 285);
    sr(1, 20, 250);
    bk(20);
    delay(100);
  }

  if (version == 5){
    walk_circle5();
  }

  if  (version == 6){
    walk_circle();
  }
//// L
  if (version == 7){
     walkline(20, 1);
    Delay(20, 20, 350);
    sl(2, 20, 200);
    track_close_cross(20);
    Delay(20, 20, 285);
    sl(2, 20, 250);
    bk(20);
    delay(100);
  }

  if (version == 8){
     walkline(20, 1);
    Delay(20, 20, 350);
    sl(2, 20, 200);
    track_close_cross(20);
    Delay(20, 20, 285);
    sr(1, 20, 250);
    track_close_cross(20);
    Delay(20, 20, 350);
    sl(2, 20, 200);
     bk(20);
    delay(100);
  }

  if (version == 9){
    walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
      walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(15, 2);
  Delay(20, 20, 350);
  sr(1, 20, 200);
  bk(20);
    delay(100);

  }
   if (version == 10){
    walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
      walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(15, 2);
  Delay(20, 20, 350);
  sl(2, 20, 200);
   track_close_cross(15);
  Delay(20, 20, 250);
  sr(1, 20, 200);
  bk(20);
  sleep(100);
  

  }

   if (version == 11){
    walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
      walkline(20, 3);
  Delay(20, 20, 350);
  sl(2, 20, 50);
      walkline(20, 2);
  Delay(20, 20, 350);
  sr(1, 20, 50);
  track_close_cross(15);
  Delay(20, 20, 250);
  sl(2, 20, 200);
  bk(20);
  sleep(100);
  

  }
//// R
   if (version == 12){
     walkline(20, 1);
    Delay(20, 20, 350);
    sr(1, 20, 200);
    track_close_cross(20);
    Delay(20, 20, 285);
    sr(1, 20, 250);
    bk(20);
    delay(100);
  }

  if (version == 13){
     walkline(20, 1);
    Delay(20, 20, 350);
    sr(1, 20, 200);
    track_close_cross(20);
    Delay(20, 20, 285);
    sl(2, 20, 250);
    track_close_cross(20);
    Delay(20, 20, 350);
    sr(1, 20, 200);
     bk(20);
    delay(100);
  }

  if (version == 14){
    walkline(20, 3);
  Delay(20, 20, 350);
  sl(2, 20, 350);
      walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(15, 1);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  bk(20);
    delay(100);

  }
   if (version == 15){
    walkline(20, 3);
  Delay(20, 20, 350);
  sl(2, 20, 350);
      walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(15, 1);
  Delay(20, 20, 350);
  sr(1, 20, 200);
   track_close_cross(15);
  Delay(20, 20, 250);
  sl(2, 20, 200);
  bk(20);
  sleep(100);
  

  }

   if (version == 16){
    walkline(20, 3);
  Delay(20, 20, 350);
  sl(2, 20, 350);
      walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 50);
      walkline(20, 1);
  Delay(20, 20, 350);
  sl(2, 20, 50);
  track_close_cross(15);
  Delay(20, 20, 250);
  sr(1, 20, 200);
  bk(20);
  sleep(100);
  

  }
}
int switch_sensor(int sensor) {
  switch (sensor) {
    case 0: return Ref_L0;
    case 1: return Ref_L1;
    case 2: return Ref_R2;
    case 3: return Ref_R3;
    default: return 600;
  }
}

void tracktime(int speed, int time) {
  for (int i = 0; i <= time; i++) {
    trackline(speed);
  }
  motorstop();
}

void walkline(int speed, int sensor) {
  int refVal = switch_sensor(sensor);
  while (1) {
    if (analog(sensor) < refVal) break;
    trackline(speed);
  }
  motorstop();

  // line left use analog 0 & line right use analog 3 //
}
void walkline2(int speed) {
  int S2 = analog(2);
  int S3 = analog(3);
  while (1) {
    S2 = analog(2);
    S3 = analog(3);
    if (S2 < Ref_R2 && S3 < Ref_R3){
      break;
    }trackline(speed);
  }
  motorstop();

  // line left use analog 0 & line right use analog 3 //
}
void walkline_test(int speed, int sensor) {
  int refVal = switch_sensor(sensor);
  float temp_error = 0;
  while (1) {
    if (analog(sensor) < refVal) break;
    trackline_test(speed + (temp_error / 25));
    if (analog(1) < Ref_L1 && analog(2) < Ref_R2) {
      temp_error++;
    }
  }
  motorstop();

  // line left use analog 0 & line right use analog 3 //
}
void Delay(int speed1, int speed2, int time) {
  fd2(speed1, speed2);
  delay(time);
  motorstop();
}

void sr(int sensor, int speed, int time) {
  sr(speed);
  delay(time);
  motorstop();

  int refVal = switch_sensor(sensor);
  while (analog(sensor) > refVal) {
    sr(speed);
  }
  motorstop();

  // use analog 1 //
}

void sl(int sensor, int speed, int time) {
  sl(speed);
  delay(time);
  motorstop();

  int refVal = switch_sensor(sensor);
  while (analog(sensor) > refVal) {
    sl(speed);
  }
  motorstop();

  // use analog 2 //
}

void trackline(int speed) {
  L1 = analog(1);
  R2 = analog(2);

  if (L1 > Ref_L1 && R2 > Ref_R2) fd(speed);
  else if (L1 < Ref_L1 && R2 > Ref_R2) tl(speed);
  else if (L1 > Ref_L1 && R2 < Ref_R2) tr(speed);
}

void trackline_test(int speed) {
  L1 = analog(1);
  R2 = analog(2);

  if (L1 > Ref_L1 && R2 > Ref_R2) fd(speed);
  else if (L1 < Ref_L1 && R2 > Ref_R2) sl(speed);
  else if (L1 > Ref_L1 && R2 < Ref_R2) sr(speed);
}
void trackline_test2(int speed) {
  L1 = analog(1);
  R2 = analog(2);

  if (L1 > Ref_L1 && R2 > Ref_R2) fd(speed);
  else if (L1 < Ref_L1 && R2 > Ref_R2) tl(speed);
  else if (L1 > Ref_L1 && R2 < Ref_R2) tr(speed);
}

void motorstop() {
  ao();
  delay(100);
}

void skipline(int sensor) {
  walkline(20, sensor);
  Delay(20, 20, 350);
}
void keep_up() {
  ao();
  delay(5000);
}
void keep_down() {
  servo(1, 180);
  delay(2000);
  servo(1, 75);
}
void leave_base() {
  walkline(20, 0);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(20, 3);
  Delay(20, 20, 350);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
}
void leave_base1() {
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(20, 0);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  bk(20);
  delay(100);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
}
void leave_base2() {
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(2, 20, 350);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  bk(20);
  delay(100);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
}
void return_base() {
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
   bk(20);
  delay(100);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  bk(20);
  delay(100);
  walkline(20, 0);
  Delay(20, 20, 350);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
   bk(20);
  delay(100);
  walkline(20, 1);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  bk(20);
  delay(100);

}
void return_base1() {
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
   bk(20);
  delay(100);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  bk(20);
  delay(100);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
//  walkline(20, 3);
//   Delay(20, 20, 350);
//   sr(1, 20, 350); 
//   walkline(20, 3);
//   Delay(20, 20, 350);
}
void return_base2() {
  walkline(20, 0);
  Delay(20, 20, 350);
  sr(1, 20, 350);
   bk(20);
  delay(100);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  bk(20);
  delay(100);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  // walkline(20, 0);
  // Delay(20, 20, 350);
  // sl(2, 20, 350);
  // walkline(20, 3);
  // Delay(20, 20, 350);
}

void return_base4() {
  walkline(20, 0);
  Delay(20, 20, 350);
  sr(1, 20, 350);
   bk(20);
  delay(100);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  bk(20);
  delay(100);
  walkline(20, 3);
  Delay(20, 20, 350);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
   bk(20);
  delay(100);
  walkline(20, 2);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  bk(20);
  delay(100);

}
void walk_circle4() {
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(15, 2);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(15, 2);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  // walkline_test(15, 3); // temporary disabled
  track_close_cross(15);
  Delay(20, 20, 250);
  sr(1, 20, 200);
  // tracktime(20, 2000);
  // Delay(20, 20, 300);
  // sr(1, 20, 250);
}
void walk_circle() {
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(15, 2);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(15, 2);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  track_close_cross(15);
  Delay(20, 20, 250);
  sr(1, 20, 200);
  // tracktime(20, 2000);
  // Delay(20, 20, 300);
  // sr(1, 20, 250);
}
void walk_circle1() {
 
  walkline(20, 1);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  track_close_cross(20);
  Delay(20, 20, 285);
  sr(1, 20, 250);
    walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 200);
    walkline(20, 3);
  Delay(20, 20, 350);
   walkline(20, 3);
  Delay(20, 20, 350);
   walkline(20, 3);
  Delay(20, 20, 350);
   walkline(20, 3);
  Delay(20, 20, 350);
  sl(2, 20, 350);


  // track_close_cross(20);
  // Delay(20, 20, 350);
  // sl(2, 20, 350);
  // walkline(20, 3);
  // Delay(20, 20, 0);
  // keep_up();
  // sl(2, 20, 350);
  // walkline(20, 3);
  // Delay(20, 20, 350);
  // sr(1, 20, 200);
  // walkline(20, 3);
  // Delay(20, 20, 350);
  // sr(1, 20, 200);
  // walkline(20, 2);
  // Delay(20, 20, 350);
  // sl(2, 20, 200);
  // track_close_cross(15);
  // Delay(20, 20, 250);
  // sr(1, 20, 200);
}  
void walk_circle2() {
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(20, 2);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  track_close_cross(15);
  Delay(20, 20, 350);
  sr(1, 20, 200);
  walkline(20, 0);
  Delay(20, 20, 0);
  keep_up();
  sr(1, 20, 350);
  walkline(20, 3);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 200);
  walkline(20, 1);
  Delay(20, 20, 350);
  sr(1, 20, 200);
  track_close_cross(15);
  Delay(20, 20, 250);
  sl(2, 20, 200);
  // walkline(20, 3);
  // Delay(20, 20, 350);
  // sr(1, 20, 350);
  // tracktime(20, 2200);
  // Delay(20, 20, 300);
  // sr(1, 20, 250);
}
void end_mission() {
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(2, 20, 350);
  walkline(20, 0);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(20, 3);
  Delay(20, 20, 350);
  sr(1, 20, 350);
  walkline(20, 3);
  Delay(20, 20, 600);
}
void track_close_cross(int speed) {
  int S1 = analog(1);
  int S2 = analog(2);
  while (true) {
    S1 = analog(1);
    S2 = analog(2);
    int S1 = analog(1);
    int S2 = analog(2);
    if (S1 < Ref_L1 && S2 < Ref_R2) {
      break;
    } else {
      trackline(speed);
    }
  }
  motorstop();
}
void walk_temp1() {
  int S0 = analog(0);
  while (true) {
    S0 = analog(0);
    if (S0 < Ref_L0) {
      break;
    }
    fd2(20, 10);
  }
}
void walk_circle5() {
  walkline(20, 3);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(15, 1);
  Delay(20, 20, 350);
  sr(1, 20, 200);
  walkline(20, 0);
  Delay(20, 20, 350);
  sl(2, 20, 350);
  walkline(15, 1);
  Delay(20, 20, 350);
  sr(1, 20, 200);
  track_close_cross(15);
  Delay(20, 20, 250);
  sl(2, 20, 200);
  // tracktime(20, 2000);
  // Delay(20, 20, 300);
  // sr(1, 20, 250);
}
