#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1

//                    S0   S1   S2   S3
int sensor_min[] = { 140, 125, 40, 40 };    // ค่าสีดำ
int sensor_max[] = { 770, 600, 620, 680 };  // ค่าสีขาว
float power_factor = 1.0;

int line_value[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int current_degree = 0;
float previous_error_forward = 0;
byte servo_pin[] = { 6, 5, 4, 0, 1, 2, 3 };

int place_can_distance = 5;
int pick_can_distance = 5;
int pick_can_floor = 13;

long delayALL = 150;

TaskHandle_t sonarTaskHandle = NULL;
TaskHandle_t switchGripperTaskHandle = NULL;
// มอเตอร์ ต่อ 1 ซ้าย 2 ขวา
// เซ็นเซอร์ ซ้ายหน้า 0 - ขวาหน้า 1
// เซ้็นเซอร์ หลังขวา 2 - ซ้ายสุด 3
void setup() {
  initialize();
  Serial.begin(115200);
  // สร้างงาน Muti-Tasking (ทำพร้อมกัน)
  xTaskCreatePinnedToCore(liftLoop, "liftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sonarLoop, "sonarLoop", 2048, NULL, 1, &sonarTaskHandle, 1);
  xTaskCreatePinnedToCore(switchGripperLoop, "switchGripperLoop", 2048, NULL, 1, &switchGripperTaskHandle, 1);
  vTaskSuspend(sonarTaskHandle);
  vTaskSuspend(switchGripperTaskHandle);
  setupDistanceSensor();
  setupServo();
  // lift(3);  // ก่อนเปิดหุ่นต้องกดลงให้สุดก่อน
  ///////////////////////เปิดอ่าค่า เซนเซอร์ ////////////////////////////////
  // ShowValue_Sensor();  // จับเส้น
  // ShowDistanceSensor(); // ระยะทาง
}

void loop() {
  // STOP();
  // SetBack(20, 275, 'L');
  // pickCan(5);
  // SetBack(20, 275, 'R');
  // FF_Enhanced(40, 750);
  // SetFront(20, 425, 'L');
  // StableOBJ();
  // placeCan(5, 'A', 'A');
  // BB(40, 300);

  // STOP();
  // spinDegree_Enhanced(90);
  // BB_Enhanced(40, 700);

  // SetBack(20, 275, 'L');
  // pickCan(5);
  // SetBack(20, 275, 'R');
  // FF_Enhanced(40, 700);
  // SetFront(20, 425, 'L');
  // StableOBJ();
  // placeCan(5, 'R', 'C');
  // BB_Enhanced(40, 300);
  // placeCan(5, 'L', 'S');
  // BB_Enhanced(40, 300);

  // STOP();
  // spinDegree_Enhanced(90);
  // BB_Enhanced(40, 700);

  // SetBack(20, 275, 'L');
  // pickCan(5);
  // SetBack(20, 275, 'R');
  // FF(40, 600);
  // SetFront(20, 425, 'L');
  // StableOBJ();
  // placeCan(5, 'L', 'S');
  // BB_Enhanced(40, 300);
  // placeCan(5, 'R', 'S');
  // BB_Enhanced(40, 300);

  // STOP();
  // spinDegree_Enhanced(90);
  // BB_Enhanced(40, 700);

  // SetBack(20, 275, 'L');
  // pickCan(5);
  // SetBack(20, 275, 'R');
  // FF_Enhanced(40, 700);
  // SetFront(20, 425, 'L');
  // StableOBJ();
  // placeCan(5, 'L', 'C');
  // BB_Enhanced(40, 300);
  // placeCan(5, 'R', 'S');
  // BB_Enhanced(40, 300);

  // STOP();
  // spinDegree_Enhanced(90);
  // BB_Enhanced(40, 700);

  // SetBack(20, 275, 'L');
  // pickCan(5);
  // SetBack(20, 275, 'R');
  // FF(40, 600);
  // SetFront(20, 425, 'L');
  // placeCan(5, 'R', 'S');
  // BB_Enhanced(40, 300);
  // placeCan(5, 'L', 'S');
  // BB_Enhanced(40, 300);

  // ---

  // STOP();
  // SetBack(20, 275, 'L');
  // pickCan(5);  // GG
  // BB_Enhanced(40, 375, 'R');
  // FF_Enhanced(40, 700);
  // SetFront(20, 500, 'L');
  // placeCan(5, 'A', 'A');
  // BB(40, 300);

  // // STOP();
  // spinDegree_Enhanced(90);
  // BB(40, 600);

  // SetBack(20, 275, 'L');
  // pickCan(5);  // YR
  // BB_Enhanced(40, 375, 'R');
  // FF_Enhanced(40, 700);
  // SetFront(20, 500, 'L');
  // BB_Enhanced(40, 700);
  // SetBack(20, 400, 'R');
  // placeCan(10, 'L', 'S');

  // // STOP();
  // BB_Enhanced(40, 400);
  // spinDegree_Enhanced(-90);
  // SetBack(20, 275, 'L');
  // placeCan(15, 'R', 'S');

  // // STOP();
  // BB_Enhanced(40, 300, 'R');
  // FF_Enhanced(40, 750, 'R');
  // BB_Enhanced(40, 700);
  // SetBack(20, 275, 'L');

  // pickCan(5); // RY
  // BB_Enhanced(40, 375, 'R');
  // FF_Enhanced(40, 700);
  // SetFront(20, 500, 'L');
  // BB_Enhanced(40, 700);
  // SetBack(20, 275, 'R');
  // placeCan(10, 'R', 'C');

  // // STOP();
  // BB_Enhanced(40, 400);
  // spinDegree_Enhanced(-90);
  // SetBack(20, 250, 'L');
  // placeCan(15, 'L', 'C');

  // ---

  STOP();
  SetBack(20, 275, 'L');
  pickCan(5);  // GR
  BB_Enhanced(40, 375, 'R');
  FF_Enhanced(40, 700);
  SetFront(20, 375, 'L');
  placeCan(5, 'L', 'C');
  BB(40, 700);
  SetBack(20, 175, 'L');
  placeCan(15, 'R', 'C');

  // STOP();
  BB_Enhanced(40, 400, 'R');
  SetBack(20, 275);
  FF_Enhanced(40, 750, 'R');
  BB_Enhanced(40, 700);
  SetBack(20, 275, 'L');

  pickCan(5);  // GY
  BB_Enhanced(40, 375, 'R');
  FF_Enhanced(40, 700);
  SetFront(20, 475, 'L');
  placeCan(5, 'L', 'L');
  BB_Enhanced(40, 700);
  SetBack(20, 400, 'R');
  placeCan(10, 'R', 'S');

  // STOP();
  BB_Enhanced(40, 400);
  spinDegree_Enhanced(-90);
  SetBack(20, 275);
  FF_Enhanced(40, 750, 'R');
  BB_Enhanced(40, 700);
  SetBack(20, 275, 'L');

  pickCan(5); // YR
  BB_Enhanced(40, 375, 'R');
  FF_Enhanced(40, 700);
  SetFront(20, 500, 'L');
  BB_Enhanced(40, 700);
  SetBack(20, 275, 'R');
  placeCan(10, 'L', 'S');

  BB_Enhanced(40, 400);
  spinDegree_Enhanced(-90);
  SetBack(20, 300, 'L');
  placeCan(15, 'R', 'S');
}
