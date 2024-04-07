#include <pins.cpp>

void setup() {
  pinMode(automaticSwitch, OUTPUT); // Configurează pinul LED-ului ca ieșire
}

void loop() {
  digitalWrite(automaticSwitch, HIGH); // Trimite semnal deschis către pinul LED-ului
  delay(1000); // Așteaptă 1 secundă
  digitalWrite(automaticSwitch, LOW); // Trimite semnal închis către pinul LED-ului
  delay(1000); // Așteaptă 1 secundă
}