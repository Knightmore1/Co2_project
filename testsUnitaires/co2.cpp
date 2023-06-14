#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial mhzSerial(1);

#define MHZ19_RXD_PIN 37
#define MHZ19_TXD_PIN 36

float co2;

void setup()
{
    Serial.begin(9600);
    mhzSerial.begin(9600, SERIAL_8N1, MHZ19_RXD_PIN, MHZ19_TXD_PIN);
}

void loop()
{
    // Mesure du taux de CO2
    mhzSerial.write((uint8_t)0xFF);
    mhzSerial.write((uint8_t)0x01);
    mhzSerial.write((uint8_t)0x86);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x79);

    int response = mhzSerial.read();
    if (response == 0xFF && mhzSerial.read() == 0x86)
    {
        int high = mhzSerial.read();
        int low = mhzSerial.read();
        co2 = (high << 8) + low;
        Serial.println("CO2: " + String(co2) + " ppm");
    }

    delay(3000);
}
