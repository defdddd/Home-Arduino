#include <Arduino.h>

//CONSTANTS
const int NUMBER_OF_INVERTORS = 2; // Numărul de invertori utilizat
const int HOUSE_CONSUMPTION = 50; // Consumul casei în watt
const int BOILER_POWER = (3000/NUMBER_OF_INVERTORS) + HOUSE_CONSUMPTION; // Puterea boilerei în watt
const int WATER_HEATER_POWER = (4000/NUMBER_OF_INVERTORS) + HOUSE_CONSUMPTION; // Puterea încălzitorului de apă în watt

const int START_SOLAR_POWER = 50; // Puterea inițială a sursei solare în watt
const int BATTERY_POWER_FOR_SWITHCING_OFF = 40; // Puterea bateriei pentru întreruperea alimentării în %
const int BATTERY_POWER_FOR_SWITHCING_ON = 42; // Puterea bateriei pentru reluarea alimentării în %
const int START_SOLAR_VOLTAGE = 200;

const int BATTERY_POWER_FOR_BOILER = 74; // Puterea bateriei necesară pentru boiler în %
const int BATTERY_POWER_FOR_HEATER = 89; // Puterea bateriei necesară pentru încălzitorul de apă în %

const int CHECKER_FOR_COUNTER_ON = 7; // Verificator pentru contorizarea pornirii în secunde
const int CHECKER_FOR_COUNTER_OFF = 10; // Verificator pentru contorizarea opirii în secunde

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