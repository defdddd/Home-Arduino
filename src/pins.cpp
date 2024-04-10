#include <Arduino.h>

//CONSTANTS
const int NUMBEROFINVERTORS = 2;
const int HOUSECONSUMPTION = 200;
const int BOILERPOWER = 3000/NUMBEROFINVERTORS - HOUSECONSUMPTION;
const int WATERHEATERPOWER = 4000/NUMBEROFINVERTORS - HOUSECONSUMPTION;

const int ON = LOW;
const int OFF = HIGH;

const int MODBUS_RATE = 9600;
const int SLAVE_ID = 1;

const int SCR_WD = 240;
const int SCR_HT = 240;

//PINS
const int automaticSwitch = A0;
const int boiler = A1;
const int waterHeater = A2;

const int RX = PD0;
const int TX = PD1;

const int TFT_DC  =  7;
const int TFT_RST  = 8;

