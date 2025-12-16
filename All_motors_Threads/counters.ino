// ===================== INTERRUPTS =====================
void interrupcion_Base() {
  if (digitalRead(pinB_Base)) contador_Base--;
  else contador_Base++;
}

void interrupcion_Link1() {
  if (digitalRead(pinB_Link1)) contador_Link1++;
  else contador_Link1--;
}

void interrupcion_Link2() {
  if (digitalRead(pinB_Link2)) contador_Link2++;
  else contador_Link2--;
}