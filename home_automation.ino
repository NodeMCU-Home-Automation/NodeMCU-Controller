#include "config.h" // contains wifi-ssid and wifi-password
#include "wifi-lib.h"
//#include <ESP8266WiFi.h>

#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

//int wifiStatus;

ESP8266WebServer http_rest_server(80);

void setup() 
{  
  Serial.begin(115200);\
  delay(200);
  
  Serial.println("\n\nProgram-Setup started.");
  Serial.println("Starting WiFi-Setup.");
  connectWiFi(ssid, password);
  
  Serial.println("Configurate REST Server Routing.");
  config_rest_server_routing();

  Serial.println("Starting HTTP REST Server...");
  http_rest_server.begin();
  Serial.println("HTTP REST Server Started");

  Serial.println("Setup Led on Pin D6.");
  pinMode(D6, OUTPUT);
  
  Serial.println("Program-Setup completed. Starting Main-Program.\n");
}   

void loop() 
{
  http_rest_server.handleClient();
  checkWiFiStatus(ssid, password);
}

void config_rest_server_routing()
{
  http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.send(200, "text/html",
            "Welcome to the ESP8266 REST Web Server");
    });
  http_rest_server.on("/toggleLed", HTTP_PUT, toggleLed);
}


void toggleLed()
{
  Serial.println("Toggle Led triggered!");
  if(digitalRead(D6) == HIGH)
  {
    digitalWrite(D6, LOW);
  }
  else
  {
    digitalWrite(D6, HIGH);
  }
  http_rest_server.send(200);
}

