#include <WiFi.h>
#include <iostream>
using namespace std;

class wifi
{
    const char* ssid = "AP_SNIR";
    const char* password = "Snir2018";

    void setup() 
    {
    Serial.begin(9600);
    delay(1000);

    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    
    Serial.println("Connected to WiFi network");
    }

    void loop() 
    {
    // Utilise la connexion Wi-Fi pour envoyer et recevoir des données
    }
}; 

int main()
{


    return 0;
}