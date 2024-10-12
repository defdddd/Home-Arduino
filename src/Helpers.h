#ifndef Helpers_h
#define Helpers_h

struct GrowattData {
  float invertorStatus;
  float batteryPOW;
  float solarPower;
  float consumptionPower;
  float pvVoltage; 
  /////
  int year;
  int month;
  int day;
  int hour;
  int min;   
  int sec;   

//
  bool isReadOk = false; 
};
#endif