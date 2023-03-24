#include <Wire.h>
#include <HardwareSerial.h>

#define MHZ19_RXD_PIN 37
#define MHZ19_TXD_PIN 36

HardwareSerial mhzSerial(1);

void setup() {
  // Remap TXD1 sur la broche 38 et RXD1 sur la broche 39
  //Serial1.begin(115200, SERIAL_8N1, 36, 37);

  mhzSerial.begin(9600, SERIAL_8N1, MHZ19_RXD_PIN, MHZ19_TXD_PIN);
  Serial.begin(9600);
}

void loop() {

  //Serial.println("Envoie des données");

  mhzSerial.write(0xFF);
  mhzSerial.write(0x01);
  mhzSerial.write(0x86);
  mhzSerial.write(0x00);
  mhzSerial.write(0x00);
  mhzSerial.write(0x00);
  mhzSerial.write(0x00);
  mhzSerial.write(0x00);
  mhzSerial.write(0x79);

  //Serial.println("Données envoyées");

  while (mhzSerial.available()) {
    int response = mhzSerial.read();
    if (response == 0xFF && mhzSerial.read() == 0x86) {
      int high = mhzSerial.read();
      int low = mhzSerial.read();
      int co2 = (high << 8) + low;
      Serial.println("CO2: " + String(co2) + " ppm");
    }
  }

  delay(9000);
}
