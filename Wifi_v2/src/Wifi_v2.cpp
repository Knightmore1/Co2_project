#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "AP_SNIR";           //Nom du réseau wifi
const char* password = "Snir2018";      //Mot de passe du réseau wifi

const char* mqttServer = "172.20.233.?"; //adresse IP de la raspberry
const int mqttPort = 1883;
const char* mqttUser = "Non d'utilisateur";
const char* mqttPassword = "mot de passe de l'utilisateur";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  mqttClient.setServer(mqttServer, mqttPort);

  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT server...");
    if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT server");
      delay(2000);
      Serial.println("Evoie du message");
      mqttClient.publish("test_co2", "test_publish");
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