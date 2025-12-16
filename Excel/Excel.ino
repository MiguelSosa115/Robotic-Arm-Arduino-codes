#include <Servo.h>
#include <PID_v1.h>
#include <EnableInterrupt.h>
//===================== SERVO ======================
Servo myServo;
const int pin_Servo = A0;

//===================== MOTOR PINS ======================
const int pin3_Base  = 6;
const int pin2_Base  = 7;
const int pin1_Base  = A1;

const int pin3_Link1 = 5;
const int pin2_Link1 = 4;
const int pin1_Link1 = A2;

const int pin3_Link2 = 3;
const int pin2_Link2 = 2;
const int pin1_Link2 = A3;

//===================== ENCODER PINS ======================
const int pinA_Base  = 11;
const int pinB_Base  = 13;

const int pinA_Link1 = 10;
const int pinB_Link1 = 12;

const int pinA_Link2 = 9;
const int pinB_Link2 = 8;

//===================== ENCODER COUNTERS ======================
volatile long contador_Base  = 0;
volatile long contador_Link1 = 0;
volatile long contador_Link2 = 0;

//===================== PID OBJECTS ======================
double Kp = 1.0, Ki = 0.5, Kd = 0.05;

double Input_Base, Output_Base, Setpoint_Base;
double Input_Link1, Output_Link1, Setpoint_Link1;
double Input_Link2, Output_Link2, Setpoint_Link2;

PID PID_Base(&Input_Base, &Output_Base, &Setpoint_Base, Kp, Ki, Kd, DIRECT);
PID PID_Link1(&Input_Link1, &Output_Link1, &Setpoint_Link1, Kp, Ki, Kd, DIRECT);
PID PID_Link2(&Input_Link2, &Output_Link2, &Setpoint_Link2, Kp, Ki, Kd, DIRECT);   

//===================== DISTANCES ======================
long distancia_Base;
long distancia_Link1;
long distancia_Link2;
long full_round_Base = 3320;
long full_round_Link1 = 1840;
long full_round_Link2 = 500;

int distance_Servo;
int measure;

String input;

void setup() {
  Serial.begin(9600);

  PID_Base.SetMode(AUTOMATIC);
  PID_Base.SetOutputLimits(-200, 200); 

  PID_Link1.SetMode(AUTOMATIC);
  PID_Link1.SetOutputLimits(-255, 255);

  PID_Link2.SetMode(AUTOMATIC);
  PID_Link2.SetOutputLimits(-255, 255);

  pinMode(pinA_Base, INPUT_PULLUP);
  pinMode(pinB_Base, INPUT_PULLUP);

  enableInterrupt(pinA_Base,interrupcion_Base,RISING);
  //attachInterrupt(digitalPinToInterrupt(pinA_Base), interrupcion_Base, RISING);

  pinMode(pin3_Base, OUTPUT);
  pinMode(pin2_Base, OUTPUT);
  pinMode(pin1_Base, OUTPUT);
  
  pinMode(pinA_Link1, INPUT_PULLUP);
  pinMode(pinB_Link1, INPUT_PULLUP);

  enableInterrupt(pinA_Link1,interrupcion_Link1,RISING);
  //attachInterrupt(digitalPinToInterrupt(pinA_Link1), interrupcion_Link1, RISING);

  pinMode(pin3_Link1, OUTPUT);
  pinMode(pin2_Link1, OUTPUT);
  pinMode(pin1_Link1, OUTPUT);

  pinMode(pinA_Link2, INPUT_PULLUP);
  pinMode(pinB_Link2, INPUT_PULLUP);
  enableInterrupt(pinA_Link2,interrupcion_Link2,RISING);
  //attachInterrupt(digitalPinToInterrupt(pinA_Link2), interrupcion_Link2, RISING);

  pinMode(pin3_Link2, OUTPUT);
  pinMode(pin2_Link2, OUTPUT);
  pinMode(pin1_Link2, OUTPUT);

  measure = 0;
}

void loop() {
  delay(10000);
  measure++;
  if (measure==1){
    Base();
  }

}

void Base() {
  delay(3000);
  distancia_Base = -45;
  distancia_Base = (distancia_Base * full_round_Base)/360;

  Setpoint_Base = distancia_Base;

  while (true) {
    Input_Base = contador_Base;     // feedback from encoder
    PID_Base.Compute();           // calculate PID → Output

    if (abs(Setpoint_Base - Input_Base) < 1) {  // motor is at target
      Stop_Base();
      break;
    }

    if (Output_Base > 0) {
      clockwise_Base(Output_Base);      // send PWM speed as Output
    } 
    else {
      anticlock_Base(255-abs(Output_Base)); // speed = |Output|
    }

    Serial.println(contador_Base);
  }
}

void Link1(){
  distancia_Link1 = -45;

  distancia_Link1 = (distancia_Link1 * full_round_Link1)/360;
  Setpoint_Link1 = distancia_Link1;

  while (true) {
    Input_Link1 = contador_Link1;     // feedback from encoder
    PID_Link1.Compute();           // calculate PID → Output
    if (abs(Setpoint_Link1 - Input_Link1) < 1) {  // motor is at target
      Stop_Link1();
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
    int excel = contador_Link1;
    Serial.println(excel);
  }
}

void Link2(){
  delay(3000);
  distancia_Link2 = -45;
  bool userEntered = false;

  distancia_Link2 = (distancia_Link2 * full_round_Link2)/360;
  Setpoint_Link2 = distancia_Link2;

  while (true) {
    Input_Link2 = contador_Link2;     // feedback from encoder
    PID_Link2.Compute();           // calculate PID → Output

    if (abs(Setpoint_Link2 - Input_Link2) < 1) {  // motor is at target
      Stop_Link2();
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

void interrupcion_Base() {
  if (digitalRead(pinB_Base)) {
    contador_Base--;
  } 
  else {
    contador_Base++;
  }
}

void interrupcion_Link1() {
  if (digitalRead(pinB_Link1)) {
    contador_Link1++;
  } 
  else {
    contador_Link1--;
  }
}

void interrupcion_Link2() {
  if (digitalRead(pinB_Link2)) {
    contador_Link2++;
  } 
  else {
    contador_Link2--;
  }
}
