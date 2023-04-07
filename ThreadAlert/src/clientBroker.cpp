#include <iostream>
#include <string>
#include "clientBroker.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

    void clientBroker::connexionWIFI(const char* ssid, const char* password)
    {
         WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) 
        {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");

    }

char intToChar(int number) {
    return static_cast<char>(number + '0');
}
    
    void clientBroker::connexionMQTT(const char* mqttServer, const int mqttPort, const char* mqttUser, const char* mqttPassword)
    {
        mqttClient.setServer(mqttServer, mqttPort);

        while (!mqttClient.connected()) {
            Serial.println("Connecting to MQTT server...");
            if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {
                Serial.println("Connected to MQTT server");
                delay(2000);
                //Serial.println("Envoie du message");            
                //mqttClient.publish("test_co2", "Debut de 'envoie: "); //"test_co2" = nom du topic, "test_publish" = valeur à envoyer
            } else {
                Serial.print("Failed to connect to MQTT server with state ");
                Serial.println(mqttClient.state());
                delay(2000);
            }
        }
    }
    
void clientBroker::client(float humidity, float temperature, int co2)
{
    char co2Str[6];
    snprintf(co2Str, sizeof(co2Str), "%d", co2); // convertit la variable co2 en une chaîne de caractères
    mqttClient.publish("co2", co2Str); //"humidity" = nom du topic
    delay(1000);

    char humidityStr[6];
    snprintf(humidityStr, sizeof(humidityStr), "%.2f", humidity); // convertit la variable humidity en une chaîne de caractères
    mqttClient.publish("humidity", humidityStr); //"humidity" = nom du topic
    delay(1000);

    char temperatureStr[6];
    snprintf(temperatureStr, sizeof(temperatureStr), "%.2f", temperature); // convertit la variable temperature en une chaîne de caractères
    mqttClient.publish("temperature", temperatureStr); //"temperature" = nom du topic
    delay(10000);
  }