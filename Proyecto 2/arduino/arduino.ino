#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

WiFiClient wifiClient;
const char* ssid="CLARO1_6DBA95";
const char* password="64081QiSvy";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("Conectando a la red wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("¡Conexión exitosa!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    // llamar a la peticion
    HTTPClient http;
    http.begin(wifiClient, "http://grupo17.pythonanywhere.com");
    int httpCod = http.GET();
    Serial.print("Codigo HTTP: ");
    Serial.println(httpCod);
    // se verifica la respuesta
    if (httpCod > 0){
      // se lee la respuesta
      const size_t document = JSON_OBJECT_SIZE(15);
      DynamicJsonDocument jsonDocument (document);
      auto error = deserializeJson(jsonDocument, http.getString());
      if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return;
      }
      // se obtiene la respuesta
      const char* message = jsonDocument["message"];

      Serial.print("mensaje: ");
      Serial.println(message);
    }
    http.end(); //Close connection
  }
  delay(5000);
  Serial.println("");
}
