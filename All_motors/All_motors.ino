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

String input;

void setup() {
  Serial.begin(115200);

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

}

void loop() {
  delay(1000);
  Serial.println("Enter selection between Base, Link1, Link2 and Servo:");
  input = "";
  while(input != "Base" && input != "Link1" && input != "Link2" && input != "Servo"){
    if (Serial.available()) {
      input = Serial.readStringUntil('\n');
    }
  }

  Serial.println("You entered: "+ input);

  if(input == "Base"){
  Base();
  }

  else if(input == "Link1"){
  Link1();
  }

  else if(input == "Link2"){
  Link2();
  }

  else if(input == "Servo"){
  Servo();
  }

}


