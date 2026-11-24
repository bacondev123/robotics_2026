void Diy()
{ 
  lift(1);
  delay(500);
  servoOpenLeft();
  servoOpenRight();
  delay(500);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(500);
}