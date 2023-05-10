#include <WiFi.h> //inclut la bibliothèque pour la connexion Wi-Fi
#include <PubSubClient.h> //inclut la bibliothèque pour la connexion MQTT
#include <cstdio> //inclut la bibliothèque pour l'utilisation de snprintf

const char* ssid = "AP_SNIR";           //Nom du réseau wifi
const char* password = "Snir2018";      //Mot de passe du réseau wifi

const char* mqttServer = "172.20.233.40"; //adresse IP de la raspberry
const int mqttPort = 1883;
const char* mqttUser = "Ilane"; //nom d'utilisateur pour la connexion MQTT
const char* mqttPassword = "Ilane2"; //mot de passe pour la connexion MQTT

WiFiClient wifiClient; //crée une instance de la classe WiFiClient pour la connexion Wi-Fi
PubSubClient mqttClient(wifiClient); //crée une instance de la classe PubSubClient pour la connexion MQTT avec la classe WiFiClient

float humidity = 25; //initialise la variable de l'humidité à une valeur de 25

void setup() {
  Serial.begin(9600); //démarre la communication série à une vitesse de 9600 bits par seconde
  WiFi.begin(ssid, password); //tente de se connecter au réseau Wi-Fi avec les identifiants ssid et password
  while (WiFi.status() != WL_CONNECTED) { //tant que la carte n'est pas connectée au réseau Wi-Fi
    delay(1000); //attends 1 seconde
    Serial.println("Connecting to WiFi..."); //affiche le message de connexion au réseau Wi-Fi
  }
  Serial.println("Connected to WiFi"); //affiche le message de connexion réussie au réseau Wi-Fi

  mqttClient.setServer(mqttServer, mqttPort); //configure le serveur MQTT avec l'adresse IP mqttServer et le port mqttPort

  char humidityStr[6]; //crée une chaîne de caractères "humidityStr" de taille 6
  snprintf(humidityStr, sizeof(humidityStr), "%.2f", humidity); //convertit la variable humidity en une chaîne de caractères et la stocke dans humidityStr

  while (!mqttClient.connected()) { //tant que la carte n'est pas connectée au serveur MQTT
    Serial.println("Connecting to MQTT server..."); //affiche le message de connexion au serveur MQTT
    if (mqttClient.connect("ESP32Client", mqttUser, mqttPassword)) { //tente de se connecter au serveur MQTT avec un identifiant "ESP32Client", un nom d'utilisateur et un mot de passe
      Serial.println("Connected to MQTT server"); //affiche le message de connexion réussie au serveur MQTT
      delay(2000); //attend 2 secondes
      Serial.println("Envoie du message"); //affiche le message d'envoi du message
      mqttClient.publish("test_co2", humidityStr); //envoie la valeur de l'humidité sur le topic "test_co2"
    } else {
      Serial.print("Failed to connect to MQTT server with state "); //affiche le message d'échec de connexion au serveur MQTT
      Serial.println(mqttClient.state()); //affiche le code d'état de la connexion MQTT
      delay(2000); //attend 2 secondes
    }
  }
}

void loop() {
  mqttClient.loop(); //maintient la connexion MQTT en boucle
}
