#include <WiFi.h>        //Libs wifi et envoie de données
#include <PubSubClient.h>

// Définition de la classe MaClasse
class clientBroker 
{
    public:
        WiFiClient wifiClient;

        void connexionWIFI(const char* ssid, const char* password);
        
        void connexionMQTT(const char* mqttServer, const int mqttPort, const char* mqttUser, const char* mqttPassword, const int idEsp, const char* versionEsp, const int numSalle, const char* batiment, const int etage, const int capaMax);
        
        void client(float humidity, float temperature, int co2);

};
