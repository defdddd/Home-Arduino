#include <homeAutomatization.cpp>
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
    void deleteData()
    {
        tft.setTextSize(2);
        tft.setTextColor(BLACK);
        tft.setCursor(140, 20); // Setează poziția textului
        tft.println(1000,1);

        tft.setCursor(140, 50);
        tft.println(1000,1);

        tft.setCursor(140, 80);
        tft.println(1000,1);

        tft.setCursor(140, 110);
        tft.println(1000,1);

        tft.setCursor(140, 140);
        tft.println(1000,1);
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
        }

        void Display(GrowattData data) {

            delay(500);

            // Setează fontul și dimensiunea textului pentru valorile structurii
            deleteData();
            tft.setTextSize(2);
            tft.setTextColor(GREEN); // Schimbă culoarea textului pentru valorile actualizate

            // Scrie valorile actualizate pe ecran
            tft.setCursor(140, 20); // Setează poziția textului
            tft.println(data.invertorStatus, 1);

            tft.setCursor(140, 50);
            tft.println(data.batteryPOW, 1);

            tft.setCursor(140, 80);
            tft.println(data.solarPower, 1);

            tft.setCursor(140, 110);
            tft.println(data.pvVoltage, 1);

            tft.setCursor(140, 140);
            tft.println(data.consumptionPower, 1);
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