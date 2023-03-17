#include <Arduino.h>
#include "DHTesp.h"

#include "SSD1306Wire.h"

#ifdef ESP32
#endif
QueueHandle_t xQueue;
DHTesp dht;
SSD1306Wire display(0x3c, SDA, SCL);
float humidity;
float temperature;
void TaskTemp(void *pvParameters)
{
for( ;; )
{
humidity = dht.getHumidity();
temperature = dht.getTemperature();
delay(2000);
}
}
void TaskPrint(void *pvParamaters)
{
for( ;; )
{
display.clear();
display.setLogBuffer(5, 30);
display.print("Humidité :");
display.print("\n");
display.print(humidity, 1);
display.print("\n");
display.print("Température :");
display.print("\n");
display.print(temperature, 1);
display.print("\n");
display.drawLogBuffer(0,0);
display.display();
delay(500);
}
}
void setup()
{
Serial.begin(9600);
dht.setup(17, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
display.init();
xTaskCreate(TaskPrint, "Affiche la temp et l'humid", 10000, NULL, 2, NULL);
xTaskCreate(TaskTemp, "Prise de l'Humidité/Température", 10000, NULL, 3, NULL);
}
void loop(){}
