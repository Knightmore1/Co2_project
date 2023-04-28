#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "ESP32_AP";
const char* password = "password";

WebServer server(80);

String ssidWifi;
String passwordWifi;

void handleRoot() {
  if (server.hasArg("ssidWifi") && server.hasArg("passwordWifi")) {
    ssidWifi = server.arg("ssidWifi");
    passwordWifi = server.arg("passwordWifi");
    
    Serial.println(ssidWifi);
    Serial.println(passwordWifi);

    server.send(200, "text/html", "<html>   <body>   <p>SSID du wifi: " + ssidWifi + "</p></br>   <p>mot de passe du wifi: " + passwordWifi + "</p>   </body>   </html>");
  } else {
    server.send(200, "text/html", "<html>   <body>   <form method=\"post\">   <label for=\"ssidWifi\">entrez l'SSID et le mot de passe du wifi:</label>   <input type=\"text\" id=\"ssidWifi\" name=\"ssidWifi\"></br>   <label for=\"passwordWifi\">entrez le mot de passe du wifi: </label>   <input type=\"password\" id=\"passwordWifi\" name=\"passwordWifi\"></br>   <button type=\"submit\">Submit</button>   </form>   </body>   </html>");
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  WiFi.softAP(ssid, password);

  IPAddress apIP(192, 168, 4, 1);
  IPAddress netMsk(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, netMsk);

  server.on("/", handleRoot);

  server.begin();

  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}