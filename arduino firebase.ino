#include "DHT.h" // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#include "MQ135.h"
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
const char *ssid =  "realme X7 5G S";     // Enter your WiFi Name
const char *pass =  "shubhamdipta"; // Enter your WiFi Password
const char* server = "api.thingspeak.com";
#define FIREBASE_HOST "esp8266-9d40f-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "MtkRq9ycF5lpPbrxqCB5duQmgQJRhX4FL8siYZ4A"
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 
int air_quality;

WiFiClient client;
void setup(void)
{ 
  dht.begin();
  Serial.begin(115200);
  Serial.println("Humidity and temperature\n\n");
  delay(300);
     Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
       while (WiFi.status() != WL_CONNECTED) 
     {
            delay(700);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
        Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}
void loop() {
    MQ135 gasSensor = MQ135(A0);
     air_quality = gasSensor.getPPM();
      Firebase.setInt("air quality", air_quality);
       if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
       float h = dht.readHumidity();
    float t = dht.readTemperature();       
    Firebase.setFloat("Humidity",h);
    Firebase.setFloat("Temperature",t);  
     if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
  delay(300);
        if (client.connect(server,80))   
                      {     Serial.println("Air Quality: ");
                             Serial.print(air_quality);
                        }
}
