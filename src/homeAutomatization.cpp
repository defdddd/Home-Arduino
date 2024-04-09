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

            if(batteryPow > 75)
            {
                //O data la 10 secunde porneste boileru
                if(boilerCount % 10 == 0){
                    digitalWrite(boiler, ON);
                }

                // Verifica din 20 in 20 de secunde puterea panourilor
                // il opreste boileru daca nu are putere
                if(boilerCount > 20)
                {
                    boilerCount = 0;

                    if(solarPower < BOILERPOWER)
                    {
                        digitalWrite(boiler, OFF);
                    }
                }

            }             
            else
            {
                digitalWrite(boiler, OFF);
            }         
        }

        void updateStatusHeater(int solarPower, int batteryPow){
            if(batteryPow > 89)
            {
                //O data la 10 secunde porneste puferul
                if(heaterCount % 10 == 0){
                    digitalWrite(waterHeater, ON);
                }

                // Verifica din 20 in 20 de secunde puterea panourilor
                // il opreste puferul daca nu are putere
                if(heaterCount > 20)
                {
                    heaterCount = 0;

                    if(solarPower < WATERHEATERPOWER)
                    {
                        digitalWrite(waterHeater, OFF);
                    }
                }

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

            if(batteryPow < 40)
            {
                digitalWrite(automaticSwitch, OFF);
                digitalWrite(boiler, OFF);
                digitalWrite(waterHeater, OFF);
                resetCounters();
                return;
            }

            if(batteryPow > 42)
            {

                digitalWrite(automaticSwitch, ON);

                updateStatusBoiler(solarPower, batteryPow);

                updateStatusHeater(solarPower, batteryPow);

                boilerCount++;
                heaterCount++;
            }
            else
            {
                resetCounters();
            }
            delay(1000);
        }
};