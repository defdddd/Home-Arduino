#include <homeAutomatization.cpp>

ReadData readData;
HouseAutomatization houseAutomatization;

void setup() {
  readData.Setup();
  houseAutomatization.Setup();
}

void loop() {
  GrowattData growattData = readData.GetDataFromInvertor();
  houseAutomatization.Execute(growattData);
}