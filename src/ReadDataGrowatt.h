
#ifndef ReadDataGrowatt_h
#define ReadDataGrowatt_h

#include <ModbusMaster.h> // Includerea bibliotecii ModbusMaster pentru comunicarea Modbus
#include <Pins.h> // Includerea fișierului de configurare a pinilor
#include <Helpers.h> // Includerea fișierului de funcții auxiliare
#include <SoftwareSerial.h> // Includerea bibliotecii SoftwareSerial pentru comunicare serială software

class ReadData {
    private:
        ModbusMaster rs485; // Obiect pentru comunicarea Modbus
        SoftwareSerial *serial; // Obiect pentru comunicarea serială software
        GrowattData result; // Crearea unui obiect GrowattData pentru a stoca datele citite
    public: 
        ReadData() {} // Constructorul clasei

        void Setup() {
            serial = new SoftwareSerial (RX, TX, false); // Inițializarea obiectului SoftwareSerial cu pinii RX și TX
            serial->begin(MODBUS_RATE); // Inițializarea comunicării seriale cu viteza specificată
            rs485.begin(SLAVE_ID , *serial); // Inițializarea comunicării Modbus cu ID-ul sclavului și portul serial specificat
        }

        GrowattData GetDataFromInvertor() {
           

            uint8_t gorwatInputResult = rs485.readInputRegisters(0x0000, 64); // Citirea registrilor de intrare Modbus

            if (gorwatInputResult == rs485.ku8MBSuccess)   // Verificarea rezultatului citirii
            {
                // Interpretarea datelor citite pentru statusul invertorului și datele PV
                result.invertorStatus = rs485.getResponseBuffer(0);
                result.batteryPOW  = rs485.getResponseBuffer(18); // Puterea bateriei
                result.solarPower = (rs485.getResponseBuffer(4)) * 0.1; // Puterea solară
                result.consumptionPower = ((rs485.getResponseBuffer(9) << 16) | rs485.getResponseBuffer(10)) * 0.1; // Puterea de consum
                result.pvVoltage = (rs485.getResponseBuffer(1)) * 0.1; // Puterea solară
                result.isReadOk = true;

            }
            else
            {
                // În cazul unei erori la citire, se setează valori implicite
                result.invertorStatus = 1;
                result.batteryPOW = 100;
                result.solarPower = 3212;
                result.consumptionPower = 3222;
                result.pvVoltage = 1123;
                result.isReadOk = false;
            }

            uint8_t gorwatHoldingResult = rs485.readHoldingRegisters(0x0000, 64); // Citirea registrilor de intrare Modbus

            if (gorwatHoldingResult == rs485.ku8MBSuccess)   // Verificarea rezultatului citirii
            {         
                result.year = rs485.getResponseBuffer(45);
                result.month  = rs485.getResponseBuffer(46);
                result.day = rs485.getResponseBuffer(47); 
                result.hour = rs485.getResponseBuffer(48);
                result.min = rs485.getResponseBuffer(49);
                result.isReadOk = true;
            }
            else
            {
                // În cazul unei erori la citire, se setează valori implicite
                result.year = 2024;
                result.month = 10;
                result.day = 12;
                result.hour = 10;
                result.min = 22;
                result.isReadOk = false;
            }   

            return result; // Returnarea datelor citite
        }
};

#endif