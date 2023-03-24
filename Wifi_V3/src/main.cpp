#include <WiFi.h>
#include <PubSubClient.h>
#include <cstdio>

const char* ssid = "AP_SNIR";           //Nom du réseau wifi
const char* password = "Snir2018";      //Mot de passe du réseau wifi

const char* mqttServer = "172.20.233.40"; //adresse IP de la raspberry
const int mqttPort = 1883;
const char* mqttUser = "Ilane";
const char* mqttPassword = "Ilane2";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

float humidity = 25;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  mqttClient.setServer(mqttServer, mqttPort);

  char humidityStr[6];
  snprintf(humidityStr, sizeof(humidityStr), "%.2f", humidity); // convertit la variable humidity en une chaîne de caractères

  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT server...");
    if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT server");
      delay(2000);
      Serial.println("Envoie du message");            
      mqttClient.publish("test_co2", humidityStr); //"test_co2" = nom du topic, "test_publish" = valeur à envoyer
    } else {
      Serial.print("Failed to connect to MQTT server with state ");
      Serial.println(mqttClient.state());
      delay(2000);
    }
  }
}

void loop() {
  mqttClient.loop();
}