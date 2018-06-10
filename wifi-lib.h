#include <ESP8266WiFi.h>

class WiFiManager
{
  const char* ssid;
  const char* password;

  public:
    WiFiManager(const char* wifi_ssid, const char* wifi_password)
    {  
      ssid = wifi_ssid;
      password = wifi_password;  
    }

    void setup()
    {
      Serial.println("Starting WiFi-Setup.");
      connectWiFi();
    }

    void loop()
    {
      checkWiFiStatus();
    }
  
    void connectWiFi()
    {
      Serial.print("Connect to WiFi with SSID ");
      Serial.println(ssid);
      Serial.print("Connecting");
    
      // use led on D0 as status led
      pinMode(D0, OUTPUT);
    
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
    
      int retries = 0;
      while (WiFi.status() != WL_CONNECTED)
      {
        retries++;
        delay(200);
        Serial.print(".");
        // toggle status led
        digitalWrite(D0, !digitalRead(D0));
        
        if(retries > 20)
        {
          Serial.println("\nMaximum number of attempts reached. Restarting System...");
          ESP.restart();
        }
      }
      digitalWrite(D0, HIGH);
    
      if(WiFi.status() == WL_CONNECTED)
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
      if(WiFi.status() != WL_CONNECTED)
      {
        Serial.println("");
        Serial.println("WiFi-connection interrupted.");
        Serial.println("Initiate reconnect to WiFi.");
        connectWiFi();
      }
    }
};
