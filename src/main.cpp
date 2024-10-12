#include <DisplayData.h>

ReadData readData;
DisplayData TFT;
HouseAutomatization houseAutomatization;

unsigned long previousMillis = 0;  // Variabila care va reține ultimul timp în care LED-ul a fost schimbat
const long interval = 1000;

void setup() {
  readData.Setup();
  houseAutomatization.Setup();
  TFT.Setup();
}

void loop() {
    //ia datele de la invertor
  GrowattData growattData;

    unsigned long currentMillis = millis();  // Timpul curent în milisecunde

    // Verificăm dacă intervalul de 1 secundă a trecut
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  // Actualizăm momentul ultimei schimbări

        growattData = readData.GetDataFromInvertor();
    }


  //executa automatizarile in functie de date
  houseAutomatization.Execute(growattData);

  //afiseaza datele pe dislay
  TFT.Display(growattData);
}