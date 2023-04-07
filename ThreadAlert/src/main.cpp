#include <Arduino.h>
#include <FastLED.h>
#include "clientBroker.h"
#include "DHTesp.h"
#include "SSD1306Wire.h"
#include <Wire.h>
#include <HardwareSerial.h>

clientBroker *cB = new clientBroker;

#ifdef ESP32
// Code spécifique pour l'ESP32
#endif

QueueHandle_t xQueue;
DHTesp dht;
SSD1306Wire display(0x3c, SDA, SCL);

#define MHZ19_RXD_PIN 37
#define MHZ19_TXD_PIN 36

#define LED_PIN  18
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

HardwareSerial mhzSerial(1);

const char* ssid = "AP_SNIR";           //Nom du réseau wifi
const char* password = "Snir2018";      //Mot de passe du réseau wifi

const char* mqttServer = "172.20.233.80"; //adresse IP de la raspberry
const int mqttPort = 1883;
const char* mqttUser = "root";
const char* mqttPassword = "root";

float humidity;
float temperature;
int high;
int low;
int co2;

void TaskTemp(void *pvParameters) {
  for (;;) {
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
    vTaskDelay(pdMS_TO_TICKS(250));
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
    vTaskDelay(pdMS_TO_TICKS(250));
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
    vTaskDelay(pdMS_TO_TICKS(250));
  }
}

void TaskMqtt(void *pvParameters) {
  for (;;) {
    cB->client(humidity, temperature, co2);
    vTaskDelay(pdMS_TO_TICKS(250));
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
    vTaskDelay(pdMS_TO_TICKS(1000));
    // Etteint la LED
    leds[0] = CRGB::Black;
    FastLED.show();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }

  void danger(){    // fait clignoter la LED en rouge
    // Change la couleur de la LED en rouge
    leds[0] = CRGB::Red;
    FastLED.show();
    vTaskDelay(pdMS_TO_TICKS(500));
    // Etteint la LED
    leds[0] = CRGB::Black;
    FastLED.show();
    vTaskDelay(pdMS_TO_TICKS(500));
  }

  void turnOff(){
    // Etteint la LED
    leds[0] = CRGB::Black;
    FastLED.show();
  }

void TaskAlertLed(void *pvParamaters) {
  for (;;) {
    if (co2 >= 800){
      danger();
    } else if (co2 >= 730){
      warning();
    } else {
      noProblem();
    }

    vTaskDelay(pdMS_TO_TICKS(4000));
  }
}

void setup() {
  mhzSerial.begin(9600, SERIAL_8N1, MHZ19_RXD_PIN, MHZ19_TXD_PIN);
  Serial.begin(9600);

  cB->connexionWIFI(ssid, password);
  cB->connexionMQTT(mqttServer, mqttPort, mqttUser, mqttPassword);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  dht.setup(17, DHTesp::DHT22); // Connect DHT sensor to GPIO 17
  display.init();
  xTaskCreate(TaskPrint, "Affiche la temp et l'humid", 10000, NULL, 2, NULL);
  xTaskCreate(TaskTemp, "Prise de l'Humidité/Température", 10000, NULL, 3, NULL);
  xTaskCreate(TaskOxy, "Prise du taux de CO2", 10000, NULL, 4, NULL);
  xTaskCreate(TaskMqtt, "MQTT", 10000, NULL, 5, NULL);
  xTaskCreate(TaskAlertLed, "Etat alerte led", 10000, NULL, 6, NULL);

}




void loop() {}