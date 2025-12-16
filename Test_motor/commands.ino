void clockwise(){
digitalWrite(pinIN3, HIGH);
digitalWrite(pinIN4, LOW);
analogWrite(pinENB, 120); 
}

void anticlock(){
digitalWrite(pinIN3, LOW);
digitalWrite(pinIN4, HIGH);
analogWrite(pinENB, 160);
}

void Stop(){
digitalWrite(pinIN3, LOW);
digitalWrite(pinIN4, LOW);
analogWrite(pinENB, 0); 
}