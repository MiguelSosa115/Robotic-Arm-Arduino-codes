#include <Servo.h>
#include <PID_v1.h>
#include <EnableInterrupt.h>
// ===================== SERVO =====================
Servo myServo;
const int pin_Servo = A0;

// ===================== MOTOR PINS =====================
const int pin3_Base  = 6;
const int pin2_Base  = 7;
const int pin1_Base  = A1;

const int pin3_Link1 = 5;
const int pin2_Link1 = 4;
const int pin1_Link1 = A2;

const int pin3_Link2 = 3;
const int pin2_Link2 = 2;
const int pin1_Link2 = A3;

// ===================== ENCODER PINS =====================
const int pinA_Base  = 11;
const int pinB_Base  = 13;

const int pinA_Link1 = 10;
const int pinB_Link1 = 12;

const int pinA_Link2 = 9;
const int pinB_Link2 = 8;

// ===================== ENCODER COUNTERS =====================
volatile long contador_Base  = 0;
volatile long contador_Link1 = 0;
volatile long contador_Link2 = 0;

// ===================== PID OBJECTS =====================
double Kp = 1, Ki = 0.5, Kd = 0.02;

double Input_Base, Output_Base, Setpoint_Base;
double Input_Link1, Output_Link1, Setpoint_Link1;
double Input_Link2, Output_Link2, Setpoint_Link2;

PID PID_Base(&Input_Base, &Output_Base, &Setpoint_Base, Kp, Ki, Kd, DIRECT);
PID PID_Link1(&Input_Link1, &Output_Link1, &Setpoint_Link1, Kp, Ki, Kd, DIRECT);
PID PID_Link2(&Input_Link2, &Output_Link2, &Setpoint_Link2, Kp, Ki, Kd, DIRECT);

// ===================== MILLIS PID LOOP =====================
unsigned long lastPID = 0;
const int PID_INTERVAL = 5;   // PID loop runs every 5ms = 200Hz

// ===================== MENU STATE =====================
String command = "";
int axisWaiting = -1;  // -1 = none, 0 = Base, 1 = Link1, 2 = Link2, 3 = Servo
int dist;
int angle;
// ========================== SETUP ==========================
void setup() {
  Serial.begin(115200);

  // Init PID controllers
  PID_Base.SetMode(AUTOMATIC);
  PID_Base.SetOutputLimits(-100, 100);

  PID_Link1.SetMode(AUTOMATIC);
  PID_Link1.SetOutputLimits(-255, 255);

  PID_Link2.SetMode(AUTOMATIC);
  PID_Link2.SetOutputLimits(-255, 255);

  // Encoder interrupts
  pinMode(pinA_Base, INPUT_PULLUP);
  pinMode(pinB_Base, INPUT_PULLUP);
  enableInterrupt(pinA_Base, interrupcion_Base, RISING);
  //attachInterrupt(digitalPinToInterrupt(pinA_Base), interrupcion_Base, RISING);

  pinMode(pinA_Link1, INPUT_PULLUP);
  pinMode(pinB_Link1, INPUT_PULLUP);
  enableInterrupt(pinA_Link1, interrupcion_Link1, RISING);
  //attachInterrupt(digitalPinToInterrupt(pinA_Link1), interrupcion_Link1, RISING);

  pinMode(pinA_Link2, INPUT_PULLUP);
  pinMode(pinB_Link2, INPUT_PULLUP);
  enableInterrupt(pinA_Link2, interrupcion_Link2, RISING);
  //attachInterrupt(digitalPinToInterrupt(pinA_Link2), interrupcion_Link2, RISING);

  // Motor pins
  pinMode(pin3_Base, OUTPUT);
  pinMode(pin2_Base, OUTPUT);
  pinMode(pin1_Base, OUTPUT);

  pinMode(pin3_Link1, OUTPUT);
  pinMode(pin2_Link1, OUTPUT);
  pinMode(pin1_Link1, OUTPUT);

  pinMode(pin3_Link2, OUTPUT);
  pinMode(pin2_Link2, OUTPUT);
  pinMode(pin1_Link2, OUTPUT);

  myServo.attach(pin_Servo);
  
  Serial.println("System Ready. Type Base, Link1, Link2 or Servo.");
}

// ========================== LOOP ==========================
void loop() {

  // Run PID loop every 5ms
  if (millis() - lastPID >= PID_INTERVAL) {
    lastPID = millis();
    //updatePID();
  }

  // Non-blocking menu
  handleMenu();
  // Check if user entered a distance
  processMovement();
}

// ===================== PID UPDATE LOOP =====================
void updatePID() {
  // Base
  Input_Base = contador_Base;
  PID_Base.Compute();
  drive_Base();
  // Link1
  Input_Link1 = contador_Link1;
  PID_Link1.Compute();
  drive_Link1();

  // Link2
  Input_Link2 = contador_Link2;
  PID_Link2.Compute();
  drive_Link2();
}

// ===================== NON-BLOCKING MENU =====================
void handleMenu() {
  if (!Serial.available()) return;

  command = Serial.readStringUntil('\n');
  command.trim();

  if (command == "Base")  { axisWaiting = 0; Serial.println("Enter distance:"); }
  if (command == "Link1") { axisWaiting = 1; Serial.println("Enter distance:"); }
  if (command == "Link2") { axisWaiting = 2; Serial.println("Enter distance:"); }
  if (command == "Servo") { axisWaiting = 3; Serial.println("Enter Angle: ");}
}

// ===================== DISTANCE INPUT =====================
void processMovement() {
  if (axisWaiting >= 0 && Serial.available()) {
    int dist = Serial.parseInt();
    Serial.print("You entered: ");
    Serial.println(dist);

    if (axisWaiting == 0) Setpoint_Base = dist;
    if (axisWaiting == 1) Setpoint_Link1 = dist;
    if (axisWaiting == 2) Setpoint_Link2 = dist;
    if (axisWaiting == 3){
      //angle = (dist*180)/17
      for (int i = 0; i <= dist; i++) {
      myServo.write(i);
      }
    }
    axisWaiting = -1;   // done
  }
}
