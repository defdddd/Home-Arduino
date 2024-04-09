#include <ModbusMaster.h>
#include <pins.cpp>
#include <helpers.cpp>

class ReadData {
    private:
        int privateMember;
    public: 
        ReadData() {}
        void Setup() {}

        GrowattData GetDataFromInvertor() {
            GrowattData result;

            result.batteryPOW = 80;
            result.solarPower = 3600;
            result.consumptionPower = 2500;

            return result;
        }
};