#include <WiFi.h>

const char* ssid = "AP_SNIR";
const char* password = "Snir2018";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void loop()
{

}
