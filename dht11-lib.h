#include <DHTesp.h>

class DHT11Manager
{
  DHTesp DHT;
  int pin;
  
  float humidity;
  float temperature;
  
  public:
    DHT11Manager(int dataPin)
    {
      pin = dataPin;
    }
    
    void setup()
    {
      Serial.print("DHT11-Sensor Setup");
      DHT.setup(pin, DHTesp::DHT11);
    }

    void loop()
    {
      // debug
      //Serial.println(String(DHT.getTemperature(), 0));
    }

    float getHumidity()
    {
      return DHT.getHumidity();
    }

    float getTemperature()
    {
      return DHT.getTemperature();
    }

    boolean isStatusOk()
    {
      if(DHT.getStatus() == DHT.ERROR_NONE)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
};



