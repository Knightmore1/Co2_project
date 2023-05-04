#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char* ssid = "AP_SNIR";           //Nom du réseau wifi
const char* password = "Snir2018";      //Mot de passe du réseau wifi

const char* mqttServer = "172.20.233.71"; //adresse IP de la raspberry
const int mqttPort = 1883;
const char* mqttUser = "root";
const char* mqttPassword = "root";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WIFI CONNECTION OK");

  mqttClient.setServer(mqttServer, mqttPort);
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    if (mqttClient.connect("mac_address", mqttUser, mqttPassword)) {
      Serial.println("MQTT CONNECTION OK");
      String mac = WiFi.macAddress();
      mqttClient.publish("mac_address", mac.c_str());
    } else {
      delay(1000);
    }
  }
}

void loop() {

}
