#include <Arduino.h>
#include <FastLED.h>
#include "clientBroker.h"
#include "DHTesp.h"
#include "SSD1306Wire.h"
#include <Wire.h>
#include <HardwareSerial.h>
#include <ESPAsyncWebServer.h>

// Inclusion des bibliothèques nécessaires

clientBroker *cB = new clientBroker;  // Création d'une instance de la classe clientBroker

#ifdef ESP32
// Code spécifique pour l'ESP32
#endif

QueueHandle_t xQueue;  // Déclaration d'une file d'attente

DHTesp dht;  // Création d'une instance de la classe DHTesp pour le capteur d'humidité et de température
SSD1306Wire display(0x3c, SDA, SCL);  // Création d'une instance de la classe SSD1306Wire pour l'écran OLED

#define MHZ19_RXD_PIN 37
#define MHZ19_TXD_PIN 36

#define LED_PIN  18
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];  // Déclaration d'un tableau de couleurs pour les LED

HardwareSerial mhzSerial(1);  // Création d'une instance de la classe HardwareSerial pour la communication série avec le capteur de CO2

const char* ssid = "AP_SNIR";  // Nom du réseau WiFi
const char* password = "Snir2018";  // Mot de passe du réseau WiFi

AsyncWebServer server(80);  // Création d'une instance du serveur Web sur le port 80

const char* mqttServer = "172.20.233.39";  // Adresse IP du serveur MQTT (Raspberry Pi)
const int mqttPort = 1883;
const char* mqttUser = "root";
const char* mqttPassword = "root";

float humidity;  // Variable pour stocker l'humidité
float temperature;  // Variable pour stocker la température
int high;
int low;
int co2;  // Variable pour stocker le taux de CO2

String ssidWifi;  // Variable pour stocker le SSID du réseau WiFi saisi par l'utilisateur
String passwordWifi;  // Variable pour stocker le mot de passe du réseau WiFi saisi par l'utilisateur

// Tâche pour mesurer l'humidité et la température
void TaskTemp(void *pvParameters) {
  for (;;) {
    humidity = dht.getHumidity();  // Mesure de l'humidité
    temperature = dht.getTemperature();  // Mesure de la température
    vTaskDelay(pdMS_TO_TICKS(250));  // Pause de 250 millisecondes
  }
}

// Tâche pour mesurer le taux de CO2
void TaskOxy(void *pvParameters) {
  for (;;) {
    // Envoi de la commande de mesure au capteur de CO2
    mhzSerial.write((uint8_t)0xFF);
    mhzSerial.write((uint8_t)0x01);
    mhzSerial.write((uint8_t)0x86);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x79);

    // Lecture de la réponse du capteur de CO2
    int response = mhzSerial.read();
    if (response == 0xFF && mhzSerial.read() == 0x86) {
      high = mhzSerial.read();
      low = mhzSerial.read();
      co2 = (high << 8) + low;  // Calcul du taux de CO2 à partir des octets reçus
      Serial.println("CO2: " + String(co2) + " ppm");  // Affichage du taux de CO2 dans la console
    }
    vTaskDelay(pdMS_TO_TICKS(250));  // Pause de 250 millisecondes
  }
}

// Tâche pour afficher les mesures sur l'écran OLED
void TaskPrint(void *pvParamaters) {
  for (;;) {
    display.clear();
    display.setLogBuffer(5, 30);
    display.print("Humidité : ");
    display.print(humidity, 1);
    display.print("%\n");
    display.print("Température : ");
    display.print(temperature, 1);
    display.print("°C\n");
    display.print("CO2 : ");
    display.print(co2);
    display.print(" ppm\n");
    display.drawLogBuffer(0, 0);
    display.display();
    vTaskDelay(pdMS_TO_TICKS(250));  // Pause de 250 millisecondes
  }
}

// Tâche pour publier les mesures sur MQTT
void TaskMqtt(void *pvParameters) {
  for (;;) {
    cB->client(humidity, temperature, co2);  // Envoi des mesures via MQTT
    vTaskDelay(pdMS_TO_TICKS(250));  // Pause de 250 millisecondes
  }
}

// Tâche pour gérer l'état de la LED en fonction du taux de CO2
void TaskAlertLed(void *pvParamaters) {
  for (;;) {
    if (co2 >= 800) {
      // Change la couleur de la LED en rouge
      leds[0] = CRGB::Red;
      FastLED.show();
    } else if (co2 >= 730) {
      // Fait clignoter la LED en orange
      leds[0] = CRGB::Orange;
      FastLED.show();
      vTaskDelay(pdMS_TO_TICKS(1000));
      // Éteint la LED
      leds[0] = CRGB::Black;
      FastLED.show();
      vTaskDelay(pdMS_TO_TICKS(1000));
    } else {
      // Change la couleur de la LED en vert
      leds[0] = CRGB::Green;
      FastLED.show();
    }

    vTaskDelay(pdMS_TO_TICKS(4000));  // Pause de 4 secondes
  }
}

// Fonction pour gérer la page racine du serveur Web
void handleRoot(AsyncWebServerRequest *request) {
  if (request->hasArg("ssidWifi") && request->hasArg("passwordWifi")) {
    // Si les arguments "ssidWifi" et "passwordWifi" sont présents dans la requête
    ssidWifi = request->arg("ssidWifi");  // Stockage du SSID saisi
    passwordWifi = request->arg("passwordWifi");  // Stockage du mot de passe saisi
    Serial.println(ssidWifi);  // Affichage du SSID dans la console
    Serial.println(passwordWifi);  // Affichage du mot de passe dans la console

    // Envoi d'une réponse HTML avec les informations saisies
    request->send(200, "text/html", "<html>   <body>   <p>SSID du wifi: " + ssidWifi + "</p></br>   <p>mot de passe du wifi: " + passwordWifi + "</p>   </body>   </html>");
  } else {
    // Si les arguments ne sont pas présents, affichage d'un formulaire HTML pour saisir les informations
    request->send(200, "text/html", "<html>   <body>   <form method=\"post\">   <label for=\"ssidWifi\">entrez l'SSID et le mot de passe du wifi:</label>   <input type=\"text\" id=\"ssidWifi\" name=\"ssidWifi\"></br>   <label for=\"passwordWifi\">entrez le mot de passe du wifi: </label>   <input type=\"password\" id=\"passwordWifi\" name=\"passwordWifi\"></br>   <button type=\"submit\">Submit</button>   </form>   </body>   </html>");
  }
}

// Fonction de configuration initiale
void setup() {
  mhzSerial.begin(9600, SERIAL_8N1, MHZ19_RXD_PIN, MHZ19_TXD_PIN);
  Serial.begin(9600);

  // Initialisation du point d'accès WiFi
  WiFi.softAP(ssid, password);
  IPAddress apIP(192, 168, 4, 1);  // Adresse IP du point d'accès
  IPAddress netMsk(255, 255, 255, 0);  // Masque de sous-réseau
  WiFi.softAPConfig(apIP, apIP, netMsk);  // Configuration de l'adresse IP et du masque de sous-réseau du point d'accès

  cB->connexionWIFI(ssid, password);
  cB->connexionMQTT(mqttServer, mqttPort, mqttUser, mqttPassword);

  // Configuration du serveur Web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", "<form>SSID:<br><input type='text' name='ssidWifi'><br>Password:<br><input type='password' name='passwordWifi'><br><input type='submit' value='Submit'></form>");
  });
  server.begin();  // Démarrage du serveur
  Serial.println("Server started");  // Affichage d'un message pour indiquer que le serveur a démarré

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  dht.setup(17, DHTesp::DHT22);  // Connexion du capteur DHT au GPIO 17
  display.init();

  delay(250);
  sendMacAddress();
  delay(250);

  // Création des tâches
  xTaskCreate(TaskPrint, "Affiche la temp et l'humid", 10000, NULL, 2, NULL);
  xTaskCreate(TaskTemp, "Prise de l'Humidité/Température", 10000, NULL, 3, NULL);
  xTaskCreate(TaskOxy, "Prise du taux de CO2", 10000, NULL, 4, NULL);
  xTaskCreate(TaskMqtt, "MQTT", 10000, NULL, 5, NULL);
  xTaskCreate(TaskAlertLed, "Etat alerte led", 10000, NULL, 6, NULL);
}

void loop() {
  delay(1000);
}
