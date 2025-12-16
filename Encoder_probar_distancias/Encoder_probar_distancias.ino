const int pinIN3 = 13;
const int pinIN4 = 12;
const int pinENB = 11;

const int pinA = 3;    // canal A → interrupción 0
const int pinB = 2;    // canal B

volatile long contador = 0;
int distancia;
bool mode;

void setup() {
  Serial.begin(115200);

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), interrupcion, RISING);

  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);

  Serial.println("EMPIEZA");
  Serial.println("Enter distance:");
  delay(3000);
  if (Serial.available() > 0) {
    distancia = Serial.parseInt();   // reads an integer from Serial
    Serial.print("You entered: ");
    Serial.println(distancia);
  }  
  
  if(contador<=distancia){
  Serial.print("Clock");
  clockwise();
  while(contador<distancia){
  Serial.print("pulsos: ");
  Serial.println(contador);
  }
  Serial.print("pulsos: ");
  Serial.println(contador);
  Stop();
  }
  else if(contador>distancia){
  Serial.print("AntiClock");
  anticlock();
  while(contador>=distancia){
  Serial.print("pulsos: ");
  Serial.println(contador);
  }
  Stop();
  }
}

void loop() {
}

void interrupcion() {
  // Si B está HIGH → un sentido
  // Si LOW → el otro
  if (digitalRead(pinB)) {
    contador--;
  } else {
    contador++;
  }
}
