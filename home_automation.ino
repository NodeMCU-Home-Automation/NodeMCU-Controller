#include "config.h" // contains wifi-ssid and wifi-password
#include "wifi-lib.h"
#include "dht11-lib.h"

#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

ESP8266WebServer http_rest_server(80);

WiFiManager wifiManager(ssid, password);

DHT11Manager dht11Manager(D1);

void setup() 
{  
  Serial.begin(115200);\
  delay(200);
  
  Serial.println("\n\nProgram-Setup started.");
  wifiManager.setup();

  // REST Server Setup
  Serial.println("Configurate REST Server Routing.");
  config_rest_server_routing();

  Serial.println("Starting HTTP REST Server...");
  http_rest_server.begin();
  Serial.println("HTTP REST Server Started");

  // Functionality Setup
  Serial.println("Setup Led on Pin D6.");
  pinMode(D6, OUTPUT);

  dht11Manager.setup();
  
  Serial.println("Program-Setup completed. Starting Main-Program.\n");
  
}   

void loop() 
{
  http_rest_server.handleClient();
  wifiManager.loop();
  dht11Manager.loop();
}

void config_rest_server_routing()
{
  http_rest_server.on("/", HTTP_GET, []() 
  {
        http_rest_server.send(200, "text/html",
            "Welcome to the ESP8266 REST Web Server");
    });
  http_rest_server.on("/toggleLed", HTTP_PUT, toggleLed);
  http_rest_server.on("/temperature", HTTP_GET, []()
  {
    http_rest_server.send(200, "text/html", 
    String(dht11Manager.getTemperature(), 4));
  });
  http_rest_server.on("/humidity", HTTP_GET, []()
  {
    http_rest_server.send(200, "text/html", 
    String(dht11Manager.getHumidity(), 4));
  });
}

void toggleLed()
{
  Serial.println("Toggle Led triggered!");
  digitalWrite(D6, !digitalRead(D6));
  http_rest_server.send(200);
}
