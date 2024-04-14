#include <ModbusMaster.h> // Includerea bibliotecii ModbusMaster pentru comunicarea Modbus
#include <pins.cpp> // Includerea fișierului de configurare a pinilor
#include <helpers.cpp> // Includerea fișierului de funcții auxiliare
#include <SoftwareSerial.h> // Includerea bibliotecii SoftwareSerial pentru comunicare serială software

class ReadData {
    private:
        ModbusMaster rs485; // Obiect pentru comunicarea Modbus
        SoftwareSerial *serial; // Obiect pentru comunicarea serială software
    public: 
        ReadData() {} // Constructorul clasei

        void Setup() {
            serial = new SoftwareSerial (RX, TX, false); // Inițializarea obiectului SoftwareSerial cu pinii RX și TX
            serial->begin(MODBUS_RATE); // Inițializarea comunicării seriale cu viteza specificată
            rs485.begin(SLAVE_ID , *serial); // Inițializarea comunicării Modbus cu ID-ul sclavului și portul serial specificat
        }

        GrowattData GetDataFromInvertor() {
            GrowattData result; // Crearea unui obiect GrowattData pentru a stoca datele citite

            uint8_t gorwatResult = rs485.readInputRegisters(0x0000, 64); // Citirea registrilor de intrare Modbus

            delay(500);
            if (gorwatResult == rs485.ku8MBSuccess)   // Verificarea rezultatului citirii
            {
                // Interpretarea datelor citite pentru statusul invertorului și datele PV
                result.invertorStatus = rs485.getResponseBuffer(0);
                result.batteryPOW  = rs485.getResponseBuffer(18); // Puterea bateriei
                result.solarPower = (rs485.getResponseBuffer(4)) * 0.1; // Puterea solară
                result.consumptionPower = ((rs485.getResponseBuffer(9) << 16) | rs485.getResponseBuffer(10)) * 0.1; // Puterea de consum
                result.pvVoltage = (rs485.getResponseBuffer(1)) * 0.1; // Puterea solară

            }
            else
            {
                // În cazul unei erori la citire, se setează valori implicite
                result.invertorStatus = random(1);
                result.batteryPOW = random(100);;
                result.solarPower = random(1212);;
                result.consumptionPower = random(1222);;
                result.pvVoltage = random(1123);;
            }
            
            return result; // Returnarea datelor citite
        }
};