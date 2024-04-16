#include <readDataGrowatt.cpp> // Includerea fișierului pentru citirea datelor Growatt

class HouseAutomatization {
    private:
        int boilerCount = 0; // Contor pentru activarea boilerului
        int heaterCount = 0; // Contor pentru activarea încălzitorului de apă

        void resetCounters(){
            boilerCount = 0;
            heaterCount = 0;
        }

        bool canRunByDate(GrowattData data)
        {
            if(!data.isReadOk)
            {
                return false;
            }

            int month = data.month;
            int hour = data.hour;
            int min = data.min;

            if(hour < 8)
            {
                return false;
            }

            if(month == 1)
            {
                return hour <= HOUR_01 && min < MIN_01;
            }

            if(month == 2)
            {
                return hour <= HOUR_02 && min < MIN_02;
            }

            if(month == 3)
            {
                return hour <= HOUR_03 && min < MIN_03;
            }
            
            if(month == 4)
            {
                return hour <= HOUR_04 && min < MIN_04;
            }
            
            if(month == 5)
            {
                return hour <= HOUR_05 && min < MIN_05;
            }
            
            if(month == 6)
            {
                return hour <= HOUR_06 && min < MIN_06;
            }
            
            if(month == 7)
            {
                return hour <= HOUR_07 && min < MIN_07;
            }
            
            if(month == 8)
            {
                return hour <= HOUR_08 && min < MIN_08;
            }
            
            if(month == 9)
            {
                return hour <= HOUR_09 && min < MIN_09;
            }
            
            if(month == 10)
            {
                return hour <= HOUR_10 && min < MIN_10;
            }
            
            if(month == 11)
            {
                return hour <= HOUR_11 && min < MIN_11;
            }
            
            if(month == 12)
            {
                return hour <= HOUR_12 && min < MIN_12;
            }

            return true;
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
