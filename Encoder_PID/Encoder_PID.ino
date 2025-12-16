/************* PINES *************/
const int pinIN3 = 7;
const int pinIN4 = 8;
const int pinENB = 9;

const int pinA = 3; // Canal A → interrupción
const int pinB = 2; // Canal B

/************* ENCODER *************/
volatile long contador = 0;
long distancia = 0;

/************* PID *************/
float Kp = 1.2;
float Ki = 0.0;
float Kd = 0.05;

float error, prevError = 0;
float integral = 0;
unsigned long lastTime = 0;

/************* SETUP *************/
void setup() {
  Serial.begin(115200);
  Serial.println("EMPIEZA");

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), interrupcion, RISING);

  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);

  Serial.println("Enter target pulses:");
  while (!Serial.available()) { }
  distancia = Serial.parseInt();
  Serial.print("Target pulses = ");
  Serial.println(distancia);

  lastTime = millis();
  delay(5000);
}

/************* MAIN LOOP (PID) *************/
void loop() {

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  if (dt <= 0) dt = 0.001;

  // PID calculations
  error = distancia - contador;
  integral += error * dt;
  float derivative = (error - prevError) / dt;

  float output = Kp * error + Ki * integral + Kd * derivative;

  prevError = error;
  lastTime = now;

  // Motor control
  driveMotor(output);

  // Debug
  Serial.print("pos=");
  Serial.print(contador);
  Serial.print("  error=");
  Serial.print(error);
  Serial.print("  out=");
  Serial.println(output);

  // Stop if close enough
  if (abs(error) < 2) {
    Stop();
  }
}



/************* ENCODER ISR *************/
void interrupcion() {
  if (digitalRead(pinB))
    contador--;
  else
    contador++;
}

