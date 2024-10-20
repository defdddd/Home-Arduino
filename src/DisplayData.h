#ifndef DisplayData_h
#define DisplayData_h

#include <HomeAutomatization.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
#include <SPI.h>

class DisplayData {
    private: 
    Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST);

    // Textele pentru a afișa structura
    String statusInvertorText = "Status:";
    String procentBaterieText = "BAT:";
    String puterePanouriText = "PV W:";
    String consumText = "Consum:";
    String voltajText = "PV V:";
    String dataText = "Data:";
    String currentDate = "";
    String hour = "Ora:";
    String currentHour = "";

    int previousInvertorStatus = 0;
    int previousBatteryPOW = 0;
    int previousSolarPower = 0;
    int previousPvVoltage = 0;
    int previousConsumptionPower = 0;
    int previousMinute = 0;
    int previousDay = 0;
    int previousHour = 0;


    void checkData(GrowattData data)
    {
        if (data.invertorStatus != previousInvertorStatus) {
        // Actualizează valoarea pe ecran
            tft.fillRect(140, 20, 100, 20, BLACK);
            previousInvertorStatus = data.invertorStatus; // Actualizează valoarea anterioară
        }

        if (data.hour != previousHour) {
            tft.resetDisplay();
            Setup();
            previousHour = data.hour; // Actualizează valoarea anterioară
        }

        if (data.batteryPOW != previousBatteryPOW) {
            tft.fillRect(140, 50, 100, 20, BLACK);
            previousBatteryPOW = data.batteryPOW;
        }

        if (data.solarPower != previousSolarPower) {
            tft.fillRect(140, 80, 100, 20, BLACK);
            previousSolarPower = data.solarPower;
        }

        if (data.pvVoltage != previousPvVoltage) {
            tft.fillRect(140, 110, 100, 20, BLACK);
            previousPvVoltage = data.pvVoltage;
        }

        if (data.consumptionPower != previousConsumptionPower) {
            tft.fillRect(140, 140, 100, 20, BLACK);
            previousConsumptionPower = data.consumptionPower;
        }

        if (data.day != previousDay) {
            tft.fillRect(100, 170, 200, 20, BLACK);
            previousDay = data.day;

            currentDate = (String) data.day + "." +
                          (String) data.month + "." +
                          (String) data.year;
        }

        if (data.min != previousMinute) {
            tft.fillRect(100, 200, 200, 20, BLACK);
            previousMinute = data.min;

            currentHour = (String) data.hour + ":" +
                          (String) data.min;
        }
    }

    void displayInputData()
    {
        tft.setTextSize(2);
        tft.setTextColor(GREEN); // Schimbă culoarea textului pentru valorile actualizate

        // Scrie valorile actualizate pe ecran
        tft.setCursor(140, 20); // Setează poziția textului
        tft.println(previousInvertorStatus, 1);

        tft.setCursor(140, 50);
        tft.println(previousBatteryPOW, 1);

        tft.setCursor(140, 80);
        tft.println(previousSolarPower, 1);

        tft.setCursor(140, 110);
        tft.println(previousPvVoltage, 1);

        tft.setCursor(140, 140);
        tft.println(previousConsumptionPower, 1);
    }


    void displayHoldingData()
    {
        tft.setTextSize(2);
        tft.setTextColor(BLUE); 

        tft.setCursor(100, 170);
        tft.println(currentDate);

        tft.setCursor(100, 200);
        tft.println(currentHour);
    }


    public: 
        DisplayData() {}
        void Setup() {
            tft.init(SCR_WD, SCR_HT);
            tft.fillScreen(BLACK);
            // Setează fontul și dimensiunea textului
            tft.setTextSize(2);
            tft.setTextColor(WHITE);
            
            // Scrie textele pentru structura
            tft.setCursor(10, 20); // Setează poziția textului
            tft.println(statusInvertorText);
            tft.setCursor(10, 50);
            tft.println(procentBaterieText);
            tft.setCursor(10, 80);
            tft.println(puterePanouriText);
            tft.setCursor(10, 110);
            tft.println(voltajText);
            tft.setCursor(10, 140);
            tft.println(consumText);
            tft.setCursor(10, 170);
            tft.println(dataText);        
            tft.setCursor(10, 200);
            tft.println(hour);
        }

        void Display(GrowattData data) {

            checkData(data);

            displayInputData();

            displayHoldingData();
        }   
};

///LCD pin	LCD pin name	Arduino
///#01	GND	GND
///#02	VCC	VCC (3.3V only!)
///#03	SCL	D13/SCK
///#04	SDA	D11/MOSI
///#05	RES	D8 or any digital
///#06	DC	D7 or any digital
///#07	BLK	NC

#endif