#include <readDataGrowatt.cpp>

class HouseAutomatization {
    private:
        void startBoiler(int solarPower, int batteryPow){
            if(solarPower < BOILERPOWER)
            {
                digitalWrite(boiler, OFF);
                digitalWrite(waterHeater, OFF);
            }

            if(batteryPow > 75)
            {
                digitalWrite(boiler, ON);
                delay(500);
            }
            else
            {
                digitalWrite(boiler, OFF);
            }
        }

        void startWaterHeater(int solarPower, int batteryPow){
            if(solarPower < WATERHEATERPOWER)
            {
                digitalWrite(waterHeater, OFF);                
            }

            if(batteryPow > 75)
            {
                digitalWrite(waterHeater, ON);
                delay(500);
            }
            else
            {
                digitalWrite(waterHeater, OFF);
            }
        }
    public: 
        HouseAutomatization() {}

        void Setup() {
            pinMode(automaticSwitch, OUTPUT);
            pinMode(boiler, OUTPUT);
            pinMode(waterHeater, OUTPUT);

        }

        void Execute(GrowattData data) 
        {

            int batteryPow = data.batteryPOW;
            int solarPower = data.solarPower;
            int consumptionPower = data.consumptionPower;

            if(batteryPow < 40)
            {
                digitalWrite(automaticSwitch, OFF);
                digitalWrite(boiler, OFF);
                digitalWrite(waterHeater, OFF);
                return;
            }

            if(batteryPow > 42)
            {
                digitalWrite(automaticSwitch, ON);

                startBoiler(solarPower, batteryPow);

                startWaterHeater(solarPower, batteryPow);
            }
            delay(5000);
        }
};