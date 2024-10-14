#ifndef HomeAutomatization_h
#define HomeAutomatization_h

#include <ReadDataGrowatt.h> // Includerea fișierului pentru citirea datelor Growatt

class HouseAutomatization {
    private:

        bool canRunByDate(GrowattData data) {
            int month = data.month;
            int hour = data.hour;
            int min = data.min;

            if (hour < 8) {
                return false;
            }

            if(hour == HOURS[month - 1])
            {
                return min < MINUTES[month - 1];
            }
            
            return hour < HOURS[month - 1];
        }


        void updateStatusBoiler(int solarPower, int batteryPow, GrowattData data){

            if(batteryPow > BATTERY_POWER_FOR_BOILER)
            {
                int minute = data.min;

                if(minute % CHECKER_FOR_COUNTER_MIN == 0)
                {
                    digitalWrite(BOILER, ON);
                }
                else
                {
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

        void updateStatusHeater(int solarPower, int batteryPow, GrowattData data){
            if(batteryPow > BATTERY_POWER_FOR_HEATER)
            {

                int minute = data.min;

                if(minute % CHECKER_FOR_COUNTER_MIN == 0)
                {
                    digitalWrite(WATER_HEATER, ON);
                }
                else
                {
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
            pinMode(AUTOMATIC_SWITCH, OUTPUT); // Inițializarea pinului AUTOMATIC_SWITCH ca ieșire
            pinMode(BOILER, OUTPUT); // Inițializarea pinului BOILER ca ieșire
            pinMode(WATER_HEATER, OUTPUT); // Inițializarea pinului WATER_HEATER ca ieșire
            //Serial.begin(9600); // Inițializarea comunicării seriale cu viteza 9600 baud
        }

        void Execute(GrowattData data) 
        {

            int batteryPow = data.batteryPOW;
            int solarPower = data.solarPower;

            //Serial.println("Boiler seconds:"+ String(boilerCount)); // Afisarea contorului pentru boiler în secunde
            //Serial.println("Solar Power:" + String(solarPower)); // Afisarea puterii solare

            if(batteryPow < BATTERY_POWER_FOR_SWITHCING_OFF)
            {
                digitalWrite(AUTOMATIC_SWITCH, OFF); // Oprirea automatizării casei dacă puterea bateriei este prea mică
                digitalWrite(BOILER, OFF); // Oprirea boilerului
                digitalWrite(WATER_HEATER, OFF); // Oprirea încălzitorului de apă
            }

            if(batteryPow > BATTERY_POWER_FOR_SWITHCING_ON)
            {

                digitalWrite(AUTOMATIC_SWITCH, ON); // Pornirea automatizării casei

                if(canRunByDate(data))
                {
                    updateStatusBoiler(solarPower, batteryPow, data); // Actualizarea stării boilerului

                    updateStatusHeater(solarPower, batteryPow, data); // Actualizarea stării încălzitorului de apă
                }
                else
                {
                    digitalWrite(BOILER, OFF); // Oprirea boilerului
                    digitalWrite(WATER_HEATER, OFF); // Oprirea încălzitorului de apă
                }
            }

        }
};

#endif
