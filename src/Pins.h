
#ifndef Pins_h
#define Pins_h

#include <Arduino.h>

//CONSTANTS
const int NUMBER_OF_INVERTORS = 2; // Numărul de invertori utilizat
const int HOUSE_CONSUMPTION = 50; // Consumul casei în watt
const int BOILER_POWER = (2700/NUMBER_OF_INVERTORS) + HOUSE_CONSUMPTION; // Puterea boilerei în watt
const int WATER_HEATER_POWER = (3700/NUMBER_OF_INVERTORS) + HOUSE_CONSUMPTION; // Puterea încălzitorului de apă în watt

const int START_SOLAR_POWER = 50; // Puterea inițială a sursei solare în watt
const int BATTERY_POWER_FOR_SWITHCING_OFF = 40; // Puterea bateriei pentru întreruperea alimentării în %
const int BATTERY_POWER_FOR_SWITHCING_ON = 42; // Puterea bateriei pentru reluarea alimentării în %
const int START_SOLAR_VOLTAGE = 200;

const int BATTERY_POWER_FOR_BOILER = 74; // Puterea bateriei necesară pentru boiler în %
const int BATTERY_POWER_FOR_HEATER = 89; // Puterea bateriei necesară pentru încălzitorul de apă în %

const int CHECKER_FOR_COUNTER_ON = 7; // Verificator pentru contorizarea pornirii în secunde
const int CHECKER_FOR_COUNTER_OFF = 14; // Verificator pentru contorizarea opirii în secunde
const int CHECKER_FOR_COUNTER_MIN = 2; // in minute

const int ON = LOW; // Stare de activare (în cazul pinilor)
const int OFF = HIGH; // Stare de dezactivare (în cazul pinilor)

const int MODBUS_RATE = 9600; // Rata de transmitere a modbus
const int SLAVE_ID = 1; // ID-ul sclavului

const int SCR_WD = 240; // Lățimea ecranului TFT în pixeli
const int SCR_HT = 240; // Înălțimea ecranului TFT în pixeli

//PINS
const int AUTOMATIC_SWITCH = A0; // Pinul pentru comutatorul automat
const int BOILER = A1; // Pinul pentru boiler
const int WATER_HEATER = A2; // Pinul pentru încălzitorul de apă

const int RX = PD0; // Pinul pentru recepția serială
const int TX = PD1; // Pinul pentru transmiterea serială

const int TFT_DC = 7; // Pinul pentru comanda DC al ecranului TFT
const int TFT_RST = 8; // Pinul pentru resetarea ecranului TFT

/// hours and minutes 

///ianuarie
const int HOUR_01 = 15;
const int MIN_01 = 30;
///februarie
const int HOUR_02 = 16;
const int MIN_02 = 10;
///martie
const int HOUR_03 = 17;
const int MIN_03 = 50;
///aprilie
const int HOUR_04 = 18;
const int MIN_04 = 25;
///mai
const int HOUR_05 = 18;
const int MIN_05 = 50;
///iunie
const int HOUR_06 = 19;
const int MIN_06 = 10;
///iulie
const int HOUR_07 = 18;
const int MIN_07 = 45;
///august
const int HOUR_08 = 17;
const int MIN_08 = 55;
///septembrie
const int HOUR_09 = 17;
const int MIN_09 = 2;
///octombrie
const int HOUR_10 = 16;
const int MIN_10 = 10;
///noiembrie
const int HOUR_11 = 15;
const int MIN_11 = 1;
///decembrie
const int HOUR_12 = 15;
const int MIN_12 = 2;

/////
const int HOURS[] = { HOUR_01, HOUR_02, HOUR_03, HOUR_04, HOUR_05, HOUR_06,
                      HOUR_07, HOUR_08, HOUR_09, HOUR_10, HOUR_11, HOUR_12 };
const int MINUTES[] = { MIN_01, MIN_02, MIN_03, MIN_04, MIN_05, MIN_06, MIN_07,
                        MIN_08, MIN_09, MIN_10, MIN_11, MIN_12 };

#endif