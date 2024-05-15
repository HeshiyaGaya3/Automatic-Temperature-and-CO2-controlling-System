#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>


#include <ArduinoJson.h>
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3uHMwcJgN"
#define BLYNK_TEMPLATE_NAME "mini project"
#define BLYNK_AUTH_TOKEN "_MHSngk3aIN3V8T6VvbKCLmEUJQ4yKTG"

#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "POCO M5";
char pass[] = "prisha5.";
#include <DHT.h>
#define DHT_SENSOR_PIN  D2 // The ESP8266 pin D7 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);


#define MQ2Pin A0
#define relayPin 3
#define BUZZ 4

void setup() {

   dht_sensor.begin(); // initialize the DHT sensor
  pinMode(relayPin, OUTPUT);
  Serial.begin(115200);
  pinMode(BUZZ, OUTPUT);

   Serial.print("hi");
  //pinMode(D0, OUTPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
 
}

void loop()
{
  Blynk.run();
  
    float humi  = dht_sensor.readHumidity();
    float temperature_C = dht_sensor.readTemperature();
    float temperature_F = dht_sensor.readTemperature(true);

  
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(temperature_C);
    Serial.print("°C  ~  ");
    Serial.print(temperature_F);
    Serial.println("°F");
  
  float CO2Value = analogRead(MQ2Pin);
  Serial.println("CO2");
  Serial.println(CO2Value);
  
  
  Blynk.virtualWrite(V0, temperature_C);
  Blynk.virtualWrite(V1, CO2Value);
  
  if (temperature_C > 32.0) {
    digitalWrite(relayPin, LOW); // Turn on cooling device
  } else {
    digitalWrite(relayPin, HIGH); // Turn off cooling device
  }

  if (CO2Value > 800) {
    digitalWrite(BUZZ, HIGH); // Turn on ventilation or air purifier
  } else {
    digitalWrite(BUZZ, LOW); // Turn off ventilation or air purifier
  }
}



