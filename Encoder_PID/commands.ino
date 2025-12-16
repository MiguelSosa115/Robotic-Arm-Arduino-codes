/************* MOTOR CONTROL *************/
void driveMotor(float pwm) {
  pwm = constrain(pwm, -255, 255);

  if (pwm > 0) {
    clockwise();
    analogWrite(pinENB, pwm);
  } else if (pwm < 0) {
    anticlock();
    analogWrite(pinENB, -pwm);
  } else {
    Stop();
  }
}

void clockwise() {
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
}

void anticlock() {
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
}

void Stop() {
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, LOW);
  analogWrite(pinENB, 0);
}