// =========================================================
// SIMPLE & CRISP PD LINE FOLLOWER ENGINE (POP32)
// =========================================================
//Stable PD tuning list:
//    maxspeed        Kp           Ki          Kd
//      20       ||   8      ||   0  ||   2


#define CENTER_POS 1500.0
#define MIN_POS 0.0
#define MAX_POS 3000.0

float lastPosition = CENTER_POS;
float lastError = 0.0;
float integral = 0.0;

// Reset PID memory
void resetPD() {
  lastError = 0.0;
  integral = 0.0;
  lastPosition = CENTER_POS;
}
// ---------------------------------------------------------
// RAMP OFFSET HELPERS (Left/Right Neutral, Default = 0)
// ---------------------------------------------------------

// Single-channel 3-phase ramp: Ramp Up -> Hold -> Quick Decelerate
// Returns 0.0 (no ramp) if no optional arguments are passed
float getRampOffset(unsigned long elapsed,
                    unsigned long totalDuration,
                    float minOffset = 0.0,
                    float peakOffset = 0.0,
                    float rampUpRatio = 0.0,
                    float holdRatio = 0.0) {

  // Safety / Default Guard: no duration, flat value, or zero ratios -> no ramp
  if (totalDuration == 0 || peakOffset == minOffset || (rampUpRatio <= 0.0 && holdRatio <= 0.0)) {
    return minOffset;
  }

  float t = constrain((float)elapsed / (float)totalDuration, 0.0, 1.0);
  float holdEnd = rampUpRatio + holdRatio;
  if (holdEnd > 1.0) {
    holdEnd = 1.0;
  }

  // Phase 1: Ramp Up (minOffset -> peakOffset)
  if (t < rampUpRatio) {
    float progress = (rampUpRatio > 0.0) ? (t / rampUpRatio) : 1.0;
    return minOffset + (peakOffset - minOffset) * progress;
  }

  // Phase 2: Hold at Peak
  if (t < holdEnd) {
    return peakOffset;
  }

  // Phase 3: Quick Decelerate (peakOffset -> minOffset)
  float decaySpan = 1.0 - holdEnd;
  float progress = (decaySpan > 0.0) ? ((t - holdEnd) / decaySpan) : 1.0;
  return peakOffset - (peakOffset - minOffset) * progress;
}

// Dual-channel wrapper: sets both Left and Right offsets at once
// Sets both outputs to 0.0 (no ramp) if no optional arguments are passed
void getRampOffsetsLR(unsigned long elapsed,
                      unsigned long totalDuration,
                      float &leftOut,
                      float &rightOut,
                      float leftMin = 0.0,
                      float leftPeak = 0.0,
                      float rightMin = 0.0,
                      float rightPeak = 0.0,
                      float rampUpRatio = 0.0,
                      float holdRatio = 0.0) {

  leftOut = getRampOffset(elapsed, totalDuration, leftMin, leftPeak, rampUpRatio, holdRatio);
  rightOut = getRampOffset(elapsed, totalDuration, rightMin, rightPeak, rampUpRatio, holdRatio);
}
// ---------------------------------------------------------
// 1. CALCULATE WEIGHTED LINE POSITION (0 to 3000, Center = 1500)
// ---------------------------------------------------------
float getLinePosition() {
  readSensors();

  long sum = 0;
  long totalWeight = 0;

  for (int i = 0; i < NUM_SENSORS; i++) {
    long weight = sensorRef[i] - sensorValue[i];  // Higher weight = more black
    if (weight > 0) {
      sum += (weight * (i * 1000L));
      totalWeight += weight;
    }
  }

  // Line Lost Memory: if no black detected, remember the last exit direction
  if (totalWeight <= 0) {
    if (lastPosition < (CENTER_POS - 250.0)) {
      lastPosition = MIN_POS;  // Was on the far left
    } else if (lastPosition > (CENTER_POS + 250.0)) {
      lastPosition = MAX_POS;  // Was on the far right
    } else {
      lastPosition = CENTER_POS;
    }
  } else {
    lastPosition = (float)sum / (float)totalWeight;
  }

  return lastPosition;
}

// ---------------------------------------------------------
// 2. CORE PID CONTROLLER STEP
// ---------------------------------------------------------
void trackPD(float speed, float Kp, float Kd, float Ki = 0.0) {
  float position = getLinePosition();

  // Normalize error: scale between -3.0 (Far Left) to +3.0 (Far Right)
  float error = (position - CENTER_POS) / 500.0;

  // P Term (Proportional)
  float P = Kp * error;

  // I Term (Integral) with Anti-Windup (only accumulate near center)
  if (abs(error) <= 1.0) {
    integral += error;
    integral = constrain(integral, -15.0, 15.0);
  } else {
    integral = 0.0;
  }
  float I = Ki * integral;

  // D Term (Derivative)
  float D = Kd * (error - lastError);

  // Compute total motor differential power
  float power = P + I + D;

  float leftSpeed = speed + power;
  float rightSpeed = speed - power;

  leftSpeed = constrain(leftSpeed, -100.0, 100.0);
  rightSpeed = constrain(rightSpeed, -100.0, 100.0);

  fd2(round(leftSpeed + MOTOR_BIAS), round(rightSpeed));

  lastError = error;
}
void trackPD_Left(float speed, float Kp, float Kd, float speedOffset) {
  float position = getLinePosition();

  // Normalize error: scale between -3.0 (Far Left) to +3.0 (Far Right)
  float error = (position - CENTER_POS) / 500.0;

  // P Term (Proportional)
  float P = Kp * error;

  // D Term (Derivative)
  float D = Kd * (error - lastError);

  // Compute total motor differential power
  float power = P + D;

  float leftSpeed = speed + power;
  float rightSpeed = speed - power;

  leftSpeed = constrain(leftSpeed, -100.0, 100.0);
  rightSpeed = constrain(rightSpeed, -100.0, 100.0);

  fd2(round(leftSpeed + MOTOR_BIAS), round(rightSpeed + 10 + speedOffset));

  lastError = error;
}
void trackPD_Right(float speed, float Kp, float Kd, float speedOffset) {
  float position = getLinePosition();

  // Normalize error: scale between -3.0 (Far Left) to +3.0 (Far Right)
  float error = (position - CENTER_POS) / 500.0;

  // P Term (Proportional)
  float P = Kp * error;

  // D Term (Derivative)
  float D = Kd * (error - lastError);

  // Compute total motor differential power
  float power = P + D;

  float leftSpeed = speed + power;
  float rightSpeed = speed - power;

  leftSpeed = constrain(leftSpeed, -100.0, 100.0);
  rightSpeed = constrain(rightSpeed, -100.0, 100.0);

  fd2(round(leftSpeed + MOTOR_BIAS + 10 + speedOffset), round(rightSpeed));

  lastError = error;
}

// ---------------------------------------------------------
// 3. RUN PID FOR A FIXED TIME DURATION (in Milliseconds)
// ---------------------------------------------------------
void trackPD_Time(float speed, float Kp, float Kd, unsigned long durationMs, float Ki = 0.0) {
  resetPD();
  unsigned long startClock = millis();

  while (millis() - startClock < durationMs) {
    trackPD(speed, Kp, Kd, Ki);
  }

  ao();
  resetPD();
}
void trackPDLeft_Time(float speed,
                      float Kp,
                      float Kd,
                      unsigned long durationMs,
                      float speedOffset = 0.0,
                      float minOffset = 0.0,
                      float rampUpRatio = 0.0,
                      float holdRatio = 0.0) {
  resetPD();
  unsigned long startClock = millis();

  while (millis() - startClock < durationMs) {
    unsigned long elapsed = millis() - startClock;
    float currentOffset = speedOffset;

    // Activate ramp only when ramp ratios are provided
    if (rampUpRatio > 0.0 || holdRatio > 0.0) {
      currentOffset = getRampOffset(elapsed, durationMs,
                                    minOffset, speedOffset,
                                    rampUpRatio, holdRatio);
    }

    trackPD_Left(speed, Kp, Kd, currentOffset);
  }

  ao();
  resetPD();
}

void trackPDRight_Time(float speed,
                       float Kp,
                       float Kd,
                       unsigned long durationMs,
                       float speedOffset = 0.0,
                       float minOffset = 0.0,
                       float rampUpRatio = 0.0,
                       float holdRatio = 0.0) {
  resetPD();
  unsigned long startClock = millis();

  while (millis() - startClock < durationMs) {
    unsigned long elapsed = millis() - startClock;
    float currentOffset = speedOffset;

    // Activate ramp only when ramp ratios are provided
    if (rampUpRatio > 0.0 || holdRatio > 0.0) {
      currentOffset = getRampOffset(elapsed, durationMs,
                                    minOffset, speedOffset,
                                    rampUpRatio, holdRatio);
    }

    trackPD_Right(speed, Kp, Kd, currentOffset);
  }

  ao();
  resetPD();
}
// Add to Section 2
void trackPD_Offset(float speed,
                    float Kp,
                    float Kd,
                    float leftOffset = 0.0,
                    float rightOffset = 0.0) {
  float position = getLinePosition();

  // Normalize error: scale between -3.0 (Far Left) to +3.0 (Far Right)
  float error = (position - CENTER_POS) / 500.0;

  // P Term (Proportional)
  float P = Kp * error;

  // D Term (Derivative)
  float D = Kd * (error - lastError);

  // Compute total motor differential power
  float power = P + D;

  float leftSpeed = speed + power;
  float rightSpeed = speed - power;

  leftSpeed = constrain(leftSpeed, -100.0, 100.0);
  rightSpeed = constrain(rightSpeed, -100.0, 100.0);

  fd2(round(leftSpeed + MOTOR_BIAS + leftOffset), round(rightSpeed + rightOffset));

  lastError = error;
}

// Add to Section 3
void trackPDLR_Time(float speed,
                    float Kp,
                    float Kd,
                    unsigned long durationMs,
                    float leftMin = 0.0,
                    float leftPeak = 0.0,
                    float rightMin = 0.0,
                    float rightPeak = 0.0,
                    float rampUpRatio = 0.0,
                    float holdRatio = 0.0) {
  resetPD();
  unsigned long startClock = millis();

  while (millis() - startClock < durationMs) {
    unsigned long elapsed = millis() - startClock;
    float leftOff = leftPeak;
    float rightOff = rightPeak;

    if (rampUpRatio > 0.0 || holdRatio > 0.0) {
      getRampOffsetsLR(elapsed, durationMs,
                       leftOff, rightOff,
                       leftMin, leftPeak,
                       rightMin, rightPeak,
                       rampUpRatio, holdRatio);
    }

    trackPD_Offset(speed, Kp, Kd, leftOff, rightOff);
  }

  ao();
  resetPD();
}

// ---------------------------------------------------------
// 4. RUN PID UNTIL AN INTERSECTION (CROSS LINE) IS FOUND
// ---------------------------------------------------------
void trackPD_Cross(float speed, float Kp, float Kd, float Ki = 0.0) {
  resetPD();

  while (!crossFound()) {
    trackPD(speed, Kp, Kd, Ki);
  }

  ao();
  resetPD();
}
void trackPD_Side(int sensorIdx, float speed, float Kp, float Kd, float Ki = 0.0) {
  resetPD();

  while (isBlack(sensorIdx)) {
    trackPD(speed, Kp, Kd, Ki);
  }

  ao();
  resetPD();
}