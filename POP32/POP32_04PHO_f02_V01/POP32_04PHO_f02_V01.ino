#include <POP32.h>

constexpr uint8_t NUM_SENSORS = 4;
constexpr uint8_t sensorPins[NUM_SENSORS] = { 1, 3, 6, 8 };
int sensorRef[NUM_SENSORS] = { 2828, 2062, 2708, 2559 };  // Old val   2950, 2740, 3088, 2788
int sensorValue[NUM_SENSORS];
const float MOTOR_BIAS = 1.64;
const int LOOP_DELAY_MS = 100;
const int DEFAULT_LINE_SKIP = 905;
const float DEFAULT_SPEED = 20.0;
const float TURN_DELAY = 50;
void trackPD(float speed, float Kp, float Kd, float Ki = 0.0);
void trackPD_Time(float speed, float Kp, float Kd, unsigned long durationMs, float Ki = 0.0);
void trackPD_Cross(float speed, float Kp, float Kd, float Ki = 0.0);
void trackPD_Side(int sensorIdx, float speed, float Kp, float Kd, float Ki = 0.0);
void trackPD_Left(float speed, float Kp, float Kd, float speedOffset);
void trackPD_Right(float speed, float Kp, float Kd, float speedOffset);
void trackPDLeft_Time(float speed, float Kp, float Kd, unsigned long durationMs, float speedOffset = 0.0, float minOffset = 0.0, float rampUpRatio = 0.0, float holdRatio = 0.0);
void trackPDRight_Time(float speed, float Kp, float Kd, unsigned long durationMs, float speedOffset = 0.0, float minOffset = 0.0, float rampUpRatio = 0.0, float holdRatio = 0.0);
void trackPD_Offset(
  float speed,
  float Kp,
  float Kd,
  float leftOffset = 0.0,
  float rightOffset = 0.0);

void trackPDLR_Time(
  float speed,
  float Kp,
  float Kd,
  unsigned long durationMs,
  float leftMin = 0.0,
  float leftPeak = 0.0,
  float rightMin = 0.0,
  float rightPeak = 0.0,
  float rampUpRatio = 0.0,
  float holdRatio = 0.0);

void setup() {
  oled.clear();
  oled.text(0, 0, "SW_OK");
  oled.show();
  servo(1, 90);
  waitSW_OK();
  oled.clear();
  oled.text(0, 0, "RUN..");
  oled.show();

  // Motor_tuning(20 + MOTOR_BIAS ,20);
  // Motor_tuning(-20 + MOTOR_BIAS, -20);
  Experiment();
  // Operation();
  // sensors_Calibration();
  // test_servo();
  // servo_drop();
}

void loop() {
  // show_analog();
  // sensors_Calibration();
  // trackLine(30);
}






