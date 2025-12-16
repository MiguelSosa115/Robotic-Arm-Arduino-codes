// ===================== MOTOR DRIVERS =====================
void drive_Base() {
  if (abs(Setpoint_Base - Input_Base) < 10) {  // motor is at target
      Stop_Base();
      return;}
  if (Output_Base > 0) clockwise_Base(Output_Base);
  else if (Output_Base < 0) anticlock_Base(255-abs(Output_Base));
}

void drive_Link1() {
  if (abs(Setpoint_Link1 - Input_Link1) < 15) {  // motor is at target
      Stop_Link1();
      return;
    }
    if(Output_Link1>90) Output_Link1=90;
    if(Output_Link1<-90) Output_Link1=-90;
    if (Output_Link1 > 0) {
      clockwise_Link1(Output_Link1);      // send PWM speed as Output
    } 
    else {
      anticlock_Link1(255-abs(Output_Link1)); // speed = |Output|
    }
}


void drive_Link2() {
  if (abs(Setpoint_Link2 - Input_Link2) < 10) {  // motor is at target
      Stop_Link2();
      return;
    }
  if(Output_Link2>70) Output_Link2=70;
  if(Output_Link2<-70) Output_Link2=-70;
  if (Output_Link2 > 0) clockwise_Link2(Output_Link2);
  else if (Output_Link2 < 0) anticlock_Link2(255-abs(Output_Link2));
  else Stop_Link2();
}