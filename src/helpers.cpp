const int NUMBEROFINVERTORS = 2;
const int BOILERPOWER = 3000/NUMBEROFINVERTORS - 200;
const int WATERHEATERPOWER = 4000/NUMBEROFINVERTORS - 200;


struct GrowattData {
  int batteryPOW;
  int solarPower;
  int consumptionPower;  
};