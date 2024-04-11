#include <readDataGrowatt.cpp>

class HouseAutomatization {
    private:
        int boilerCount = 0;
        int heaterCount = 0;

        void resetCounters(){
            boilerCount = 0;
            heaterCount = 0;
        }

        void updateStatusBoiler(int solarPower, int batteryPow){

            if(batteryPow > BATTERY_POWER_FOR_BOILER)
            {
                //O data la 10 secunde porneste boileru
                if(boilerCount % CHECKER_FOR_COUNTER_ON == 0){
                    digitalWrite(BOILER, ON);
                }

                // Verifica din 20 in 20 de secunde puterea panourilor
                // il opreste boileru daca nu are putere
                if(boilerCount > CHECKER_FOR_COUNTER_OFF)
                {
                    boilerCount = 0;

                    if(solarPower < BOILER_POWER)
                    {
                        digitalWrite(BOILER, OFF);
                    }
                }

            }             
            else
            {
                digitalWrite(BOILER, OFF);
            }         
        }

        void updateStatusHeater(int solarPower, int batteryPow){
            if(batteryPow > BATTERY_POWER_FOR_HEATER)
            {
                //O data la 10 secunde porneste puferul
                if(heaterCount % CHECKER_FOR_COUNTER_ON == 0){
                    digitalWrite(WATER_HEATER, ON);
                }

                // Verifica din 20 in 20 de secunde puterea panourilor
                // il opreste puferul daca nu are putere
                if(heaterCount > CHECKER_FOR_COUNTER_OFF)
                {
                    heaterCount = 0;

                    if(solarPower < WATER_HEATER_POWER)
                    {
                        digitalWrite(WATER_HEATER, OFF);
                    }
                }

            }             
            else
            {
                digitalWrite(WATER_HEATER, OFF);
            }         
        }       
    public: 
        HouseAutomatization() {}

        void Setup() {
            pinMode(AUTOMATIC_SWITCH, OUTPUT);
            pinMode(BOILER, OUTPUT);
            pinMode(WATER_HEATER, OUTPUT);
            Serial.begin(9600);
        }

        void Execute(GrowattData data) 
        {

            int batteryPow = data.batteryPOW;
            int solarPower = data.solarPower;
            int consumptionPower = data.consumptionPower;

            Serial.println("Boiler secounds:"+ String(boilerCount));
            Serial.println("Solar Power:" + String(solarPower));
            //Serial.println("Boiler secounds:", heaterCount);

            if(batteryPow < BATTERY_POWER_FOR_SWITHCING_OFF)
            {
                digitalWrite(AUTOMATIC_SWITCH, OFF);
                digitalWrite(BOILER, OFF);
                digitalWrite(WATER_HEATER, OFF);
                resetCounters();
                return;
            }

            if(batteryPow > BATTERY_POWER_FOR_SWITHCING_ON)
            {

                digitalWrite(AUTOMATIC_SWITCH, ON);

                if(solarPower > START_SOLAR_POWER)
                {
                    updateStatusBoiler(solarPower, batteryPow);

                    updateStatusHeater(solarPower, batteryPow);

                    boilerCount++;
                    heaterCount++;
                }
            }
            else
            {
                resetCounters();
            }
            //delay(1000);
        }
};