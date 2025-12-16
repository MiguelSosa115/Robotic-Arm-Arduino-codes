void Base() {
  Serial.println("Enter distance:");
  delay(3000);

  bool userEntered = false;
  while (!userEntered) {
    if (Serial.available() > 0) {
      distancia_Base = Serial.parseInt();
      Serial.print("You entered: ");
      Serial.println(distancia_Base);
      userEntered = true;
    }
  }
  distancia_Base = (distancia_Base * full_round_Base)/360;

  Setpoint_Base = distancia_Base;

  while (true) {
    Input_Base = contador_Base;     // feedback from encoder
    PID_Base.Compute();           // calculate PID → Output

    if (abs(Setpoint_Base - Input_Base) < 1) {  // motor is at target
      Stop_Base();
      Serial.println("Reached target.");
      break;
    }

    if (Output_Base > 0) {
      clockwise_Base(Output_Base);      // send PWM speed as Output
    } 
    else {
      anticlock_Base(255-abs(Output_Base)); // speed = |Output|
    }

    Serial.print("pulsos: ");
    Serial.println(contador_Base);
  }
}

void Link1(){
  Serial.println("Enter distance:");
  delay(3000);

  bool userEntered = false;
  while (!userEntered) {
    if (Serial.available() > 0) {
      distancia_Link1 = Serial.parseInt();
      Serial.print("You entered: ");
      Serial.println(distancia_Link1);
      userEntered = true;
    }
  }

  distancia_Link1 = (distancia_Link1 * full_round_Link1)/360;
  Setpoint_Link1 = distancia_Link1;

  while (true) {
    Input_Link1 = contador_Link1;     // feedback from encoder
    PID_Link1.Compute();           // calculate PID → Output
    if (abs(Setpoint_Link1 - Input_Link1) < 1) {  // motor is at target
      Stop_Link1();
      Serial.println("Reached target.");
      break;
    }

    if (Output_Link1 > 0 && Output_Link1 < 10) {Output_Link1 = 10;}
    if (Output_Link1 < 0 && Output_Link1 > -10) {Output_Link1 = -10;}
    if (Output_Link1 > 0) {
      clockwise_Link1(Output_Link1);      // send PWM speed as Output
    } 
    else {
      anticlock_Link1(255-abs(Output_Link1)); // speed = |Output|
    }

    Serial.print("pulsos: ");
    Serial.println(contador_Link1);
  }
}

void Link2(){
  Serial.println("Enter distance:");
  delay(3000);

  bool userEntered = false;
  while (!userEntered) {
    if (Serial.available() > 0) {
      distancia_Link2 = Serial.parseInt();
      Serial.print("You entered: ");
      Serial.println(distancia_Link2);
      userEntered = true;
    }
  }
  distancia_Link2 = (distancia_Link2 * full_round_Link2)/360;
  Setpoint_Link2 = distancia_Link2;

  while (true) {
    Input_Link2 = contador_Link2;     // feedback from encoder
    PID_Link2.Compute();           // calculate PID → Output

    if (abs(Setpoint_Link2 - Input_Link2) < 1) {  // motor is at target
      Stop_Link2();
      Serial.println("Reached target.");
      break;
    }
    if (Output_Link2 > 0 && Output_Link2 < 10) {Output_Link2 = 10;}
    if (Output_Link2 < 0 && Output_Link2 > -10) {Output_Link2 = -10;}
    if (Output_Link2 > 0) {
      clockwise_Link2(Output_Link2);      // send PWM speed as Output
    } 
    else {
      anticlock_Link2(255-abs(Output_Link2)); // speed = |Output|
    }

    Serial.print("pulsos: ");
    Serial.println(contador_Link2);
  }
}

void Servo(){
  myServo.attach(pin_Servo);  // attach servo signal pin to digital pin 1
  // sweep from 0° to 180°
  Serial.println("Enter lenght to pick:");
  bool userEntered = false;
  while(!userEntered){
  if (Serial.available() > 0) {
    distance_Servo = Serial.parseInt();   // reads an integer from Serial
    Serial.print("You entered: ");
    Serial.println(distance_Servo);
    userEntered = true;
  }  
  }
  //180º Closed, 0º Open
  Grip();
  
}
