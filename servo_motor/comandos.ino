void cerrar(){
for (int angle = 0; angle <= distancia; angle++) {
    myServo.write(angle); 
    delay(15);
  }
}
