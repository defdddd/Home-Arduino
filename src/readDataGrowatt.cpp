#include <ModbusMaster.h>
#include <pins.cpp>
#include <helpers.cpp>
#include <SoftwareSerial.h> 
class ReadData {
    private:
        ModbusMaster rs485;
        SoftwareSerial *serial;
    public: 
        ReadData() {}
        void Setup() {
            serial = new SoftwareSerial (RX, TX, false); //RX, TX
            serial->begin(MODBUS_RATE);
            rs485.begin(SLAVE_ID , *serial);
        }

        GrowattData GetDataFromInvertor() {
            GrowattData result;

            uint8_t gorwatResult = rs485.readInputRegisters(0x0000, 64);

             if (gorwatResult == rs485.ku8MBSuccess)   
             {
                // Status and PV data
                result.batteryPOW  = rs485.getResponseBuffer(18) * 0.1;
                result.solarPower = ((rs485.getResponseBuffer(5) << 16) | rs485.getResponseBuffer(6)) * 0.1;
                result.consumptionPower = ((rs485.getResponseBuffer(9) << 16) | rs485.getResponseBuffer(10)) * 0.1;
            }
            else
            {
                result.batteryPOW = 100;
                result.solarPower = 1200;
                result.consumptionPower = 2500;
            }
            return result;
        }
};