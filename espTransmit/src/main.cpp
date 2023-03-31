#include <Arduino.h>
#include <FastLED.h>

#include "DHTesp.h"
#include "SSD1306Wire.h"
#include <Wire.h>
#include <HardwareSerial.h>

#include <WiFi.h>        //Libs wifi et envoie de données
#include <PubSubClient.h>
#include <cstdio>

#ifdef ESP32
// Code spécifique pour l'ESP32
#endif

const char* ssid = "AP_SNIR";           //Nom du réseau wifi
const char* password = "Snir2018";      //Mot de passe du réseau wifi

const char* mqttServer = "172.20.233.80"; //adresse IP de la raspberry
const int mqttPort = 1883;
const char* mqttUser = "root";
const char* mqttPassword = "root";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

QueueHandle_t xQueue;
DHTesp dht;
SSD1306Wire display(0x3c, SDA, SCL);

#define MHZ19_RXD_PIN 37
#define MHZ19_TXD_PIN 36

#define LED_PIN  18
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

HardwareSerial mhzSerial(1);

float humidity;
float temperature;
int high;
int low;
int co2;

void TaskTemp(void *pvParameters) {
  for (;;) {
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
    delay(2000);
  }
}

void TaskOxy(void *pvParameters) {
  for (;;) {
    mhzSerial.write((uint8_t)0xFF);
    mhzSerial.write((uint8_t)0x01);
    mhzSerial.write((uint8_t)0x86);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x00);
    mhzSerial.write((uint8_t)0x79);

    int response = mhzSerial.read();
    if (response == 0xFF && mhzSerial.read() == 0x86) {
      high = mhzSerial.read();
      low = mhzSerial.read();
      co2 = (high << 8) + low;
      Serial.println("CO2: " + String(co2) + " ppm");
    }

    delay(1000);
  }
}

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
    delay(1000);
  }
}

void noProblem(){
    // Change la couleur de la LED en vert
    leds[0] = CRGB::Green;
    FastLED.show();
  }

  void warning(){    // fait clignoter la LED en orange
    // Change la couleur de la LED en vert
    leds[0] = CRGB::Orange;
    FastLED.show();
    delay(1000);
    // Etteint la LED
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(1000);
  }

  void danger(){    // fait clignoter la LED en rouge
    // Change la couleur de la LED en rouge
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(250);
    // Etteint la LED
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(250);
  }

  void turnOff(){
    // Etteint la LED
    leds[0] = CRGB::Black;
    FastLED.show();
  }

void TaskAlertLed(void *pvParamaters) {
  for (;;) {
    if (co2 >= 800 or humidity >= 65 or temperature >= 25){
      danger();
    } else if (co2 >= 730 or humidity >= 60 or temperature >= 23){
      warning();
    } else {
      noProblem();
    }

    delay(1000);
  }
}

void TaskEnvoieDonnee(void *pvParamaters) {
  for (;;) {

    char co2Str[6];
    snprintf(co2Str, sizeof(co2Str), "%.2f", co2); // convertit la variable humidity en une chaîne de caractères
    mqttClient.publish("co2", co2Str); //"humidity" = nom du topic
    delay(1000);

    /**char humidityStr[6];
    snprintf(humidityStr, sizeof(humidityStr), "%.2f", humidity); // convertit la variable humidity en une chaîne de caractères
    mqttClient.publish("humidity", humidityStr); //"humidity" = nom du topic
    delay(1000);

    char temperatureStr[6];
    snprintf(temperatureStr, sizeof(temperatureStr), "%.2f", temperature); // convertit la variable temperature en une chaîne de caractères
    mqttClient.publish("temperature", temperatureStr); //"temperature" = nom du topic
    delay(10000);**/
  }
}

void setup() {
  mhzSerial.begin(9600, SERIAL_8N1, MHZ19_RXD_PIN, MHZ19_TXD_PIN);
  Serial.begin(9600);

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
      //Serial.println("Envoie du message");            
      //mqttClient.publish("test_co2", "Debut de 'envoie: "); //"test_co2" = nom du topic, "test_publish" = valeur à envoyer
    } else {
      Serial.print("Failed to connect to MQTT server with state ");
      Serial.println(mqttClient.state());
      delay(2000);
    }
  }

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  dht.setup(17, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
  display.init();
  xTaskCreate(TaskPrint, "Affiche la temp et l'humid", 10000, NULL, 2, NULL);
  xTaskCreate(TaskTemp, "Prise de l'Humidité/Température", 10000, NULL, 3, NULL);
  xTaskCreate(TaskOxy, "Prise du taux de CO2", 10000, NULL, 4, NULL);
  xTaskCreate(TaskAlertLed, "Etat alerte led", 10000, NULL, 5, NULL);
  xTaskCreate(TaskEnvoieDonnee, "Envoie les donnees au serveur MQTT", 10000, NULL, 6, NULL);
}

void loop() {
  mqttClient.loop();
}