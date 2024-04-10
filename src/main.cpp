#include <displayData.cpp>

ReadData readData;
DisplayData TFT;
HouseAutomatization houseAutomatization;

void setup() {
  readData.Setup();
  houseAutomatization.Setup();
  TFT.Setup();
}

void loop() {
  
  //ia datele de la invertor
  GrowattData growattData = readData.GetDataFromInvertor();

  //executa automatizarile in functie de date
  houseAutomatization.Execute(growattData);

  //afiseaza datele e dislay
  TFT.Display(growattData);
}