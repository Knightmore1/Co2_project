#include <Arduino.h>
#include "DHTesp.h"

DHTesp dht;
float humidity;

void setup()
{
    Serial.begin(9600);
    dht.setup(17, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
}

void loop()
{
    humidity = dht.getHumidity();
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    
    delay(3000);
}
