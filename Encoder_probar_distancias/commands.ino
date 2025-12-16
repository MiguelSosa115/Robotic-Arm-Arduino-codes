void clockwise(){
digitalWrite(pinIN3, HIGH);
digitalWrite(pinIN4, LOW);
analogWrite(pinENB, 30); 
}

void anticlock(){
digitalWrite(pinIN3, LOW);
digitalWrite(pinIN4, HIGH);
analogWrite(pinENB, 225);
}

void Stop(){
digitalWrite(pinIN3, LOW);
digitalWrite(pinIN4, LOW);
analogWrite(pinENB, 0); 
}
void Return(){
if(contador>0){
anticlock();
}
else if(contador<0){
clockwise();
}
while(abs(contador)>10){
Serial.print("pulsos: ");
Serial.println(contador);
}
Stop();
while(true){
}
}
