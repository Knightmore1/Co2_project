#include <Arduino.h>
#include "DHTesp.h"

DHTesp dht;
float temperature;

void setup()
{
    Serial.begin(9600);
    dht.setup(17, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
}

void loop()
{
    temperature = dht.getTemperature();

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    delay(3000);
}
