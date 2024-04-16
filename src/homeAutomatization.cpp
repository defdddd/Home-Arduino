#include <readDataGrowatt.cpp> // Includerea fișierului pentru citirea datelor Growatt

class HouseAutomatization {
    private:
        int boilerCount = 0; // Contor pentru activarea boilerului
        int heaterCount = 0; // Contor pentru activarea încălzitorului de apă

        void resetCounters(){
            boilerCount = 0;
            heaterCount = 0;
        }

        bool canRunByDate(GrowattData data) {
            if (!data.isReadOk || data.hour < 8) {
                return false;
            }
            
            int month = data.month;
            int hour = data.hour;
            int min = data.min;
            
            int hours[] = { HOUR_01, HOUR_02, HOUR_03, HOUR_04, HOUR_05, HOUR_06,
                            HOUR_07, HOUR_08, HOUR_09, HOUR_10, HOUR_11, HOUR_12 };
            int minutes[] = { MIN_01, MIN_02, MIN_03, MIN_04, MIN_05, MIN_06, MIN_07,
                              MIN_08, MIN_09, MIN_10, MIN_11, MIN_12 };
    
            return hour <= hours[month - 1] && min < minutes[month - 1];
    }


        void updateStatusBoiler(int solarPower, int batteryPow){

            if(batteryPow > BATTERY_POWER_FOR_BOILER)
            {
                // Pornirea boilerului la fiecare 10 secunde
                if(boilerCount % CHECKER_FOR_COUNTER_ON == 0){
                    digitalWrite(BOILER, ON);
                }

                // Oprirea boilerului după 20 de secunde dacă nu există suficientă putere solară
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
                // Pornirea încălzitorului de apă la fiecare 10 secunde
                if(heaterCount % CHECKER_FOR_COUNTER_ON == 0){
                    digitalWrite(WATER_HEATER, ON);
                }

                // Oprirea încălzitorului de apă după 20 de secunde dacă nu există suficientă putere solară
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
            pinMode(AUTOMATIC_SWITCH, OUTPUT); // Inițializarea pinului AUTOMATIC_SWITCH ca ieșire
            pinMode(BOILER, OUTPUT); // Inițializarea pinului BOILER ca ieșire
            pinMode(WATER_HEATER, OUTPUT); // Inițializarea pinului WATER_HEATER ca ieșire
            //Serial.begin(9600); // Inițializarea comunicării seriale cu viteza 9600 baud
        }

        void Execute(GrowattData data) 
        {

            int batteryPow = data.batteryPOW;
            int solarPower = data.solarPower;
            int pvVoltage = data.pvVoltage;

            //Serial.println("Boiler seconds:"+ String(boilerCount)); // Afisarea contorului pentru boiler în secunde
            //Serial.println("Solar Power:" + String(solarPower)); // Afisarea puterii solare

            if(batteryPow < BATTERY_POWER_FOR_SWITHCING_OFF)
            {
                digitalWrite(AUTOMATIC_SWITCH, OFF); // Oprirea automatizării casei dacă puterea bateriei este prea mică
                digitalWrite(BOILER, OFF); // Oprirea boilerului
                digitalWrite(WATER_HEATER, OFF); // Oprirea încălzitorului de apă
                resetCounters(); // Resetarea contoarelor
                return;
            }

            if(batteryPow > BATTERY_POWER_FOR_SWITHCING_ON)
            {

                digitalWrite(AUTOMATIC_SWITCH, ON); // Pornirea automatizării casei

                if(canRunByDate(data))
                {
                    updateStatusBoiler(solarPower, batteryPow); // Actualizarea stării boilerului

                    updateStatusHeater(solarPower, batteryPow); // Actualizarea stării încălzitorului de apă

                    boilerCount++; // Incrementarea contorului pentru boiler
                    heaterCount++; // Incrementarea contorului pentru încălzitorul de apă
                }
                else
                {
                    digitalWrite(BOILER, OFF); // Oprirea boilerului
                    digitalWrite(WATER_HEATER, OFF); // Oprirea încălzitorului de apă
                    resetCounters(); // Resetarea contoarelor
                }
            }
            else
            {
                resetCounters(); // Resetarea contoarelor dacă puterea bateriei este prea mică
            }
            //delay(1000); // O eventuală întârziere (nu este activată în acest moment)
        }
};
