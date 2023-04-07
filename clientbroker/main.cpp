#include <Arduino.h>
#include "clientBroker.h"

const char* ssid = "AP_SNIR";           //Nom du réseau wifi
const char* password = "Snir2018";      //Mot de passe du réseau wifi

const char* mqttServer = "172.20.233.80"; //adresse IP de la raspberry
const int mqttPort = 1883;
const char* mqttUser = "root";
const char* mqttPassword = "root";

float humidity;
float temperature;
int co2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  clientBroker *cB = new clientBroker;

  cB->connexionWIFI(ssid,password);
  cB->connexionMQTT(mqttServer, mqttPort, mqttUser, mqttPassword);
  cB->client(humidity, temperature, co2);
}

void loop() {
  // put your main code here, to run repeatedly:
  /**clientBroker *cB = new clientBroker;
  cB->client(humidity, temperature, co2);**/
}