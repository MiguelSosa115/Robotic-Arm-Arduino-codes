#include <Servo.h>

Servo myServo;   // create servo object
int pin = A0;
int distancia;
void setup() {
  Serial.begin(115200);
  myServo.attach(pin);  // attach servo signal pin to digital pin 1
  // sweep from 0° to 180°
  Serial.println("EMPIEZA");
  Serial.println("Enter angle:");
  delay(3000);

  if (Serial.available() > 0) {
    distancia = Serial.parseInt();   // reads an integer from Serial
    Serial.print("You entered: ");
    Serial.println(distancia);
  }  
  
  //abrir();

  // sweep back from 180° to 0°
  cerrar();
}

void loop() {

}