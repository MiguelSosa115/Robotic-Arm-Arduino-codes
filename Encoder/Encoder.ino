#include <EnableInterrupt.h>

const int pinIN3 = A1;
const int pinIN4 = 7;
const int pinENB = 6;

const int pinA = 11;    // canal A → interrupción 0
const int pinB = 13;    // canal B

volatile long contador = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("EMPIEZA");

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  enableInterrupt(pinA, interrupcion, RISING);
  //attachInterrupt(digitalPinToInterrupt(pinA), interrupcion, RISING);

  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);

  
  //anticlock();
  //Stop();
}

void loop() {
  Serial.print("pulsos: ");
  Serial.println(contador);
  delay(1000);
}

void interrupcion() {
  // Si B está HIGH → un sentido
  // Si LOW → el otro
  if (digitalRead(pinB)) {
    contador++;
  } else {
    contador--;
  }
}
