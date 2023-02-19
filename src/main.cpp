#include <Arduino.h>
#include "defination.h"
#include "functions.h"
#include <WiFiClient.h>
#include <DHT_U.h>
#include <DHT.h>
#include <WiFi.h>
#include <HttpClient.h>

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  Serial.println("Connecting to WiFi..");
  pinMode(DHTPIN, INPUT);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(500);
  }

  Serial.println("WiFi Connected");
  Serial.println("Local IP: " + WiFi.localIP().toString());
  dht.begin();
}

void loop()
{

  if (WiFi.status() == WL_CONNECTED)
  {
    printData(dht.readHumidity(), dht.readTemperature());
    sendData(dht.readHumidity(), dht.readTemperature());
  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
  delay(3000);
}

void sendData(float humidity, float temperature)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HttpClient http(client, HOST, PORT);
    http.beginRequest();
    // sending post request with json data
    http.post(ENDPOINT, "application/json", "{\"humidity\":" + String(humidity) + ",\"temperature\":" + String(temperature) + ",\"symbol\":\"" + String(DEGREE_SYMBOL) + "\"}");
    http.endRequest();
    Serial.println(http.responseBody());
  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
}