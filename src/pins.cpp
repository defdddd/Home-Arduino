#include <Arduino.h>

const int automaticSwitch = A0;
const int boiler = A1;
const int waterHeater = A2;
const int ON = LOW;
const int OFF = HIGH;
const int MODBUS_RATE = 9600;
const int SLAVE_ID = 1;
const int RX = PD0;
const int TX = PD1;