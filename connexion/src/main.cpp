#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "ESP32_AP";
const char* password = "password";

WebServer server(80);

String username;

void handleRoot() {
  if (server.hasArg("username")) {
    username = server.arg("username");
    server.send(200, "text/html", "<html><body><p>Thank you, " + username + "!</p></body></html>");
  } else {
    server.send(200, "text/html", "<html><body><form method=\"post\"><label for=\"username\">Enter your name:</label><input type=\"text\" id=\"username\" name=\"username\"><button type=\"submit\">Submit</button></form></body></html>");
  }
}

void setup() {
  Serial.begin(115200);
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