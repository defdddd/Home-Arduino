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
        tft.setTextColor(BLACK);
        tft.setCursor(140, 10); // Setează poziția textului
        tft.print(1111);

        tft.setCursor(140, 40);
        tft.print(1111);

        tft.setCursor(140, 70);
        tft.print(1111);

        tft.setCursor(140, 100);
        tft.print(1111);

        tft.setCursor(140, 130);
        tft.print(1111);
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
            tft.print(statusInvertorText);
            tft.setCursor(10, 50);
            tft.print(procentBaterieText);
            tft.setCursor(10, 80);
            tft.print(puterePanouriText);
            tft.setCursor(10, 110);
            tft.print(voltajText);
            tft.setCursor(10, 140);
            tft.print(consumText);

            tft.setTextColor(RED);
        }

        void Display(GrowattData data) {

            // Setează fontul și dimensiunea textului pentru valorile structurii
            deleteData();
            tft.setTextSize(2);
            tft.setTextColor(RED); // Schimbă culoarea textului pentru valorile actualizate

            // Scrie valorile actualizate pe ecran
            tft.setCursor(140, 20); // Setează poziția textului
            tft.print(data.invertorStatus);

            tft.setCursor(140, 50);
            tft.print(data.batteryPOW);

            tft.setCursor(140, 80);
            tft.print(data.solarPower);

            tft.setCursor(140, 110);
            tft.print(data.pvVoltage);

            tft.setCursor(140, 140);
            tft.print(data.consumptionPower);
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