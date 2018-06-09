#include <ESP8266WebServer.h>

void connectWiFi(const char* ssid, const char* password)
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
    Serial.print(".");
    // toggle status led
    if(digitalRead(D0) == HIGH) { digitalWrite(D0, LOW); }
    else { digitalWrite(D0, HIGH); }
    delay(200);
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

void checkWiFiStatus(const char* ssid, const char* password)
{
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi-connection interrupted.");
    Serial.println("Initiate reconnect to WiFi.");
    connectWiFi(ssid, password);
  }
}
