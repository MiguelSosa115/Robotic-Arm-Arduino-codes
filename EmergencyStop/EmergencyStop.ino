const int pinIN3 = 13;  
const int pinIN4 = 12;  
const int pinENB = 11;  
void setup() {
pinMode(pinIN3, OUTPUT);
pinMode(pinIN4, OUTPUT);
pinMode(pinENB, OUTPUT);

digitalWrite(pinIN3, LOW);
digitalWrite(pinIN4, LOW);
analogWrite(pinENB, 0); 

}

void loop() {
  // put your main code here, to run repeatedly:

}
