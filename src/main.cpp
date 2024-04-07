#include <Arduino.h>

const int pinLed = A0; // Definește pinul digital la care este conectat LED-ul (schimbă cu pinul pe care îl folosești)

void setup() {
  pinMode(pinLed, OUTPUT); // Configurează pinul LED-ului ca ieșire
}

void loop() {
  digitalWrite(pinLed, HIGH); // Trimite semnal deschis către pinul LED-ului
  delay(1000); // Așteaptă 1 secundă
  digitalWrite(pinLed, LOW); // Trimite semnal închis către pinul LED-ului
  delay(1000); // Așteaptă 1 secundă
}