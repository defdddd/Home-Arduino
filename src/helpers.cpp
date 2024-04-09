const int NUMBEROFINVERTORS = 2;
const int HOUSECONSUMPTION = 200;
const int BOILERPOWER = 3000/NUMBEROFINVERTORS - HOUSECONSUMPTION;
const int WATERHEATERPOWER = 4000/NUMBEROFINVERTORS - HOUSECONSUMPTION;


struct GrowattData {
  int batteryPOW;
  int solarPower;
  int consumptionPower;  
};