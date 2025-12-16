void clockwise_Base(int speed){
  digitalWrite(pin1_Base, HIGH);
  digitalWrite(pin2_Base, LOW);
  analogWrite(pin3_Base, speed); 
}

void anticlock_Base(int speed){
  digitalWrite(pin1_Base, LOW);
  digitalWrite(pin2_Base, HIGH);
  analogWrite(pin3_Base, speed);
}

void Stop_Base(){
  digitalWrite(pin1_Base, LOW);
  digitalWrite(pin2_Base, LOW);
  analogWrite(pin3_Base, 0); 
}

void clockwise_Link1(int speed) {
  digitalWrite(pin1_Link1, HIGH);
  digitalWrite(pin2_Link1, LOW);
  analogWrite(pin3_Link1, speed); 
}

void anticlock_Link1(int speed) {
  digitalWrite(pin1_Link1, LOW);
  digitalWrite(pin2_Link1, HIGH);
  analogWrite(pin3_Link1, speed);
}

void Stop_Link1() {
  digitalWrite(pin1_Link1, LOW);
  digitalWrite(pin2_Link1, LOW);
  analogWrite(pin3_Link1, 0); 
}

void clockwise_Link2(int speed) {
  digitalWrite(pin1_Link2, HIGH);
  digitalWrite(pin2_Link2, LOW);
  analogWrite(pin3_Link2,speed); 
}

void anticlock_Link2(int speed) {
  digitalWrite(pin1_Link2, LOW);
  digitalWrite(pin2_Link2, HIGH);
  analogWrite(pin3_Link2, speed);
}

void Stop_Link2() {
  digitalWrite(pin1_Link2, LOW);
  digitalWrite(pin2_Link2, LOW);
  analogWrite(pin3_Link2, 0); 
}

void Grip(){
  for (int i = 0; i <= distance_Servo; i++) {
    myServo.write(i); 
    delay(15);
  }
}