#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>
#include <Preferences.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1
#define chanal_Swing_Left 0
#define chanal_Swing_Right 1
#define chanal_Gripper_Left 2
#define chanal_Gripper_Right 3

// Preferences ;
/* ค่าเซ็นเซอร์ตรวจจับเส้น */
//                  S0   S1   S2   S3   S4   S5
int sensor_min[] = { 268, 267, 167, 248, 235, 213 };    // ค่าสีดำ
int sensor_max[] = { 948, 949, 744, 958, 950, 919 };  // ค่าสีขาว
int X;
/* ค่าเซ็นเซอร์อ่านค่าสี */
// .begin("C_Color_Cal", true);
int clear_color_left = (3862+4281)/2;    // ค่าสีเหลืองมือจับด้านซ้าย
int clear_color_right = (4424+4899)/2;   // ค่าสีเหลืองมือจับด้านขวา
// int clear_color_left = .getInt("Col_L", ((3548+4195)/2)); // ค่าสีเหลืองมือจับด้านซ้าย
// int clear_color_right = .getInt("Col_R", ((4159+4028)/2));   // ค่าสีเหลืองมือจับด้านขวา
// .end();

/* ค่าระยะจอดหน้าแท่นหยิบ */
float pick_can_distance = 7.5;  // ค่าระยะจอดหน้าแท่นหยิบ
/* ค่าระยะจอดเมื่อ IR เจอกระป๋อง */
float can_distance = 20;


/* ค่าระยะจอดหน้าแท่นวาง */
float place_left_side = 178; //5.0;//2.5 + 2.0;      // ค่าระยะจอดกรณีมือซ้ายวางกระป๋องซ้าย
float place_right_side = 178; //5.0; //2.5 + 2.0;     // ค่าระยะจอดกรณีมือขวาวางกระป๋องขวา

float place_left_center = 175; //5.0;//2.8 + 2.8;    // ค่าระยะจอดกรณีมือซ้ายวางกระป๋องกลาง
float place_right_center = 175; //5.0; //2.8 + 2.8;   // ค่าระยะจอดกรณีมือขวาวางกระป๋องกลาง

float power_factor = 1.0;

int line_value[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int current_degree = 0;
float previous_error_forward = 0;
byte servo_pin[] = { 6, 5, 4, 0, 1, 2, 3 };

long delayALL = 100;
int MoveTimerPlace; //158
int CanZeroDistance = 30;
int MoveCanZeroTimer = 150;
int SonarDis = 150;
TaskHandle_t sonarTaskHandle = NULL;
TaskHandle_t switchGripperTaskHandle = NULL;

////////////////////////////////////////////////////////
int Swing_Left = 90;   //80   //SO สวิงแขนซ้ายเพิ่มง้างออก ลด หุบเข้า
                       // increasing value swing towards right, decreasing value swing toward left. 
int Swing_Right = 90;  //95  //S1 สวิงแขนขวาเพิ่มง้างออก ลด หุบเข้า
                       // increasing value swing towards right, decreasing value swing toward left. 
////////////////////////////////////////////////////////
int Open_Left = 30;   //S2 อ้ามือ ชุดมือจับมือซ้ายค่ามากยิ่งหุบ 35
int Close_Left = 72;  //S2 หุบมือ ชุดมือจับมือซ้ายค่าน้อยยิ่งอ้า //67
////////////////////////////////////////////////////
int Open_Right = 40;   //S3 อ้ามือ ชุดมือจับมือขวาค่ามากยิ่งหุบ 35
int Close_Right = 98;  //S3 หุบมือ ชุดมือจับมือขวา ค่าน้อยยิ่งอ้า //76
////////////////////////////////////////////////////
int switch_degree = 40;  //35
int switch_flag = 0;
int lift_target = 0;
int swing_current_degree[] = { 0, 0 };
char can_in_gripper[2] = { 'u', 'u' };

char CanL[3]={'u','u','u'};
char CanR[3]={'u','u','u'};

bool autoplace= false;
bool PlaceBoth= false; //Set to 'true' if you want to place both cans

void setup() {
  initialize();
  Serial.begin(115200);
  xTaskCreatePinnedToCore(liftLoop, "liftLoop", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(sonarLoop, "sonarLoop", 2048, NULL, 1, &sonarTaskHandle, 0);
  xTaskCreatePinnedToCore(switchGripperLoop, "switchGripperLoop", 2048, NULL, 1, &switchGripperTaskHandle, 1);
  vTaskSuspend(sonarTaskHandle);
  vTaskSuspend(switchGripperTaskHandle);
  setupColorSensor();
  // setupDistanc2eSensor();
  setupServo();
  // SetArm();
  // swingGripper(char gripper, int degree);

  // xTaskCreatePinnedToCore(
  //   beepLogic,    // ชื่อฟังก์ชันที่จะให้ทำงาน
  //   "BeepTask",   // ชื่อเรียก Task
  //   2048,         // ขนาด Stack (ถ้าค้างให้เพิ่มเป็น 4096)
  //   NULL,         // พารามิเตอร์
  //   1,            // Priority
  //   NULL,         // Task handle
  //   0             // รันบน Core 0 (Loop ปกติรันบน Core 1)
  // );

  //--Lower arm reminder
  // delay(300);
  // lcdSetTextSize(1);
  // tft.fillScreen(ST77XX_BLACK);
  // lcdPrintText(0, 20,"Dont forget to reset ARM!!", 0xffff);
  // for(int i=0;i<2;i++){beep(50);delay(100);}
  // lcdPrintText(0, 40,"Press A or B to continue", 0xffff); 
  // STOP();
  //--

  // Menu();
  ///////////////////////เปิดอ่านค่า เซนเซอร์ ////////////////////////////////
  // ShowValue_Sensor();    // โชว์ค่าเซ็นเซอร์ตรวจจับเส้น (ReadSensor)
  // ShowDistanceSensor();  // โชว์ค่าเซ็นเซอร์วัดระยะทาง (Sonar)
  // calibrateCanColor();   // Calibrate เซ็นเซอร์อ่านค่าสี ()
  // testSensorVal();
  //////////////////////////////////////////////////////////
  // calibrateCanColor();
  //-----------

  setAngleOffset();
  
  current_degree = 0;
  // SetArm();
  lift(0);
  delay(150);
  
  delay(700);
  // servoWrite(chanal_Gripper_Left, 30); 

  // servoCloseRight();
  // beep(100);
  // delay(800);
  // servoCloseLeft();

  // servoWrite(chanal_Gripper_Right, 40);


  // KeepArm();
  STOP();
  KeepArm();
  // Experiment();
  Operation();
  // set_close_open();
  // testCanImpl();


  
  //-----------
  // delay(300); calibrateIMU();
  // SelectMenu();


  // MenuTEST();
  // MenuTrack();
}

void loop() {
  // STOP();
  setAngleOffset();
  current_degree = 0;
  // FullMap();

  // FF(40,720);STOP();
  // FF(40,720+510);STOP();
  // BB(40,300);STOP();

  // Menu();
  // Can1();
  // Block1_1();
  // Block1_2();
  // Block2_1();
  // Block2_2();
  // Block3_1();
  // Block3_2();
  // BlockCK();
  // BlockFinish();
  // CanSwap();

  // FF(60,520);
  //Test Switch
  // vTaskResume(switchGripperTaskHandle);
  // switchGripper('r', 'l');
  // vTaskSuspend(switchGripperTaskHandle);

  //Test SetBack
  // SetBack(25,400);
  // STOP();
  // SetFront(25,400);
  
  //Test Grip
  // SetBack(25,400, 'L');
  // autoPickCan(5);
  // SetBack(25,350,'R'); //Set Middle
  // SetBack(25);
  // autoPlaceCan(10);
  // lift(2);
  // STOP();
  // SetBack(25,400, 'R');
  // autoPickCan(5);
  // SetBack(25,400,'L');
  // SetBack(25,400);
  // autoPlaceCan(5);

  //Test ReadColor 
  // readColor('r');
  // readColor('l');
  // delay(300);
  
  // Can1();        // ออกจากจุดสตาร์ท ไปหยิบกระป๋อง และไปวางกระป๋องที่ 1
  // Can1_1();
  // CanCK1();
  // Can2_1();        // ไปวางกระป๋องที่ 2
  // Can2_2();        // ไปวางกระป๋องที่ 2
  // Can3_1();        // ไปหยิบกระป๋อง และไปวางกระป๋องที่ 3
  // Can3_2();        // ไปหยิบกระป๋อง และไปวางกระป๋องที่ 3
  // Can3_3();        // ไปหยิบกระป๋อง และไปวางกระป๋องที่ 3
  // CanFinal();
  
  // Can4();        // ไปวางกระป๋องที่ 4
  // Can5();        // ไปหยิบกระป๋อง และไปวางกระป๋องที่ 5
  // Can6();        // ไปวางกระป๋องที่ 6
  // EndMission();  // เสร็จแล้ววิ่งไปจุดจบ

  // lift(0);
}
