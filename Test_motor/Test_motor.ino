const int pinIN3 = 7;  
const int pinIN4 = 8;  
const int pinENB = 9;  

void setup() {
pinMode(pinIN3, OUTPUT);
pinMode(pinIN4, OUTPUT);
pinMode(pinENB, OUTPUT);
delay(1000);
anticlock();
delay(600);
Stop();
}

void loop(){
}
