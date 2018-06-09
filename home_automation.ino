#include "config.h" // contains wifi-ssid and wifi-password
#include <ESP8266WiFi.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

int wifiStatus;
 
void setup() 
{  
  Serial.begin(115200);\
  delay(200);
  
  Serial.println("\n\nProgram-Setup started.");
  Serial.println("Starting WiFi-Setup.");
  connectWiFi();

  Serial.println("Program-Setup completed. Starting Main-Program.\n");
}   


void loop() 
{
  
  
  checkWiFiStatus();
  delay(100);
}


void connectWiFi()
{
  Serial.print("Connect to WiFi with SSID ");
  Serial.println(ssid);
  Serial.print("Connecting");
  
  WiFi.begin(ssid, password);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    counter = counter + 1;
    if(counter > 10) {
      Serial.println("\nMaximum number of attempts reached. Restarting System...");
      ESP.restart();
    }
  }

  wifiStatus = WiFi.status();

  if(wifiStatus == WL_CONNECTED)
  {
     Serial.println("\nWiFi-Connection established!");  
     Serial.print("Local IP address is: ");
     Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("\nEstablishing connection failed!");
  }
}

void checkWiFiStatus()
{
  wifiStatus = WiFi.status();

  if(wifiStatus != WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi-connection interrupted.");
    Serial.println("Initiate reconnect to WiFi.");
    connectWiFi();
  }
  else
  {
    //Serial.println("WiFi-status OK.");
  }
}

