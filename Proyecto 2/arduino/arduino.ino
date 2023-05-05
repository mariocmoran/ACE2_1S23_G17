// dht11
#include <DHT.h>
#include <DHT_U.h>

//BMP280
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// conexion wifi
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

DHT dht(0, DHT11);
Adafruit_BMP280 bmp;
const int bomba = 14; // D0
const int trigger = 12; // D6
const int echo = 13; // D7

WiFiClient wifiClient;
const char* ssid="CLARO1_6DBA95";
const char* password="64081QiSvy";
const String hostGET = "http://grupo17.pythonanywhere.com/estadoRiego";
const String hostPOST = "http://grupo17.pythonanywhere.com/add";
const String hostPOSTupdate = "http://grupo17.pythonanywhere.com/update";

// VARIABLES GET
int activacion = 0;
int tiempo = 0; // segundos
int contadorTiempo = 0; // segundos transcurridos

// VARIABLES DE MEDICIONES
int humedad = 0;
int tempExterna = 0;
int tempInterna = 0;
int porcentajeAgua = 0;

void setup() {
  Serial.begin(115200);
  pinMode(bomba, OUTPUT);
  digitalWrite(bomba, LOW);
  // conexion al wifi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a la red wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  dht.begin();
  bmp.begin(0x76);
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
  Serial.println("");
  Serial.println("¡Conexión exitosa!");
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);
}

void loop() {
  // se verifica la conexion
  if (WiFi.status() == WL_CONNECTED){
    GET(); // se obtiene la activación y el tiempo
    if (activacion == 1) { // esta activado
      Serial.print("contadorTiempo: ");
      Serial.println(contadorTiempo);

      if (tiempo > 0) { // activado con un tiempo establecido
        contadorTiempo += 1;
      } else { // esta activado por tiempo indefinido
        contadorTiempo = 0;
        tiempo = 0;
      }
      digitalWrite(bomba, HIGH);
      // se guarda la activación y el tiempo actual
      POSTupdate(activacion, tiempo);
    } else { // está desactivado
      digitalWrite(bomba, LOW);
      POSTupdate(activacion, 0);
      contadorTiempo = 0;
    }

    // calculos
    Serial.println("calculos: ");
    calcularDHT11();
    calcularBMP280();
    Serial.println("");
    // se guardan los datos
    POST();

    // si esta activado y el tiempo tambien esta activado y el tiempo se acabó -> se apaga todo
    if (activacion == 1 && tiempo > 0 && contadorTiempo > tiempo) { 
      POSTupdate(0, 0);
      digitalWrite(bomba, LOW);
      contadorTiempo = 0;
      Serial.println("apagando");
    }
  }

  
  delay(1000);
  Serial.println("");
}

void calcularBMP280() {
  tempExterna = (int)bmp.readTemperature();
  Serial.print("tempExterna (C): ");
  Serial.println(tempExterna);
}

void calcularDHT11() {
  humedad = (int)dht.readHumidity();
  Serial.print("Humidity (%): ");
  Serial.println(humedad);
  tempInterna = (int)dht.readTemperature();
  Serial.print("Temperature (C): ");
  Serial.println(tempInterna);
}

void POST() {
  if (humedad <= 100 && tempExterna <= 65) {
    HTTPClient http;
    http.begin(wifiClient, hostPOST);
    http.addHeader("Content-Type", "application/json");

    // Data to send with HTTP POST
    String data = "{\"temperatura_externa\":"+String(tempExterna);
    data += ", \"temperatura_interna\":"+String(tempInterna);
    data += ", \"humedad_tierra\":"+String(humedad);
    data += ", \"porcentaje\":"+String(porcentajeAgua)+"}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(data);

    //Serial.print(data);
    Serial.print("HTTP POST Response code: ");
    Serial.println(httpResponseCode);
      
    // Free resources
    http.end();
  }
}

void POSTupdate(int tiempo, int activacion) {
  HTTPClient http;
  http.begin(wifiClient, hostPOSTupdate);
  http.addHeader("Content-Type", "application/json");

  // Data to send with HTTP POST
  String data = "{\"tiempoActivacion\":"+ String(activacion) + ", \"activacionBomba\":" + String(tiempo) + "}";           
  // Send HTTP POST request
  int httpResponseCode = http.POST(data);

  Serial.print("HTTP POSTupdate Response code: ");
  Serial.println(httpResponseCode);
    
  // Free resources
  http.end();
}

void GET() {
  // llamar a la peticion GET
  HTTPClient http;
  http.begin(wifiClient, hostGET);
  int httpCod = http.GET();
  Serial.print("Codigo HTTP GET: ");
  Serial.println(httpCod);
  if (httpCod > 0) {// se verifica la respuesta
    const size_t document = JSON_OBJECT_SIZE(255);  // se lee la respuesta
    DynamicJsonDocument jsonDocument (document);
    auto error = deserializeJson(jsonDocument, http.getString());
    //Serial.print("json: ");
    //Serial.println(http.getString());
    if (error) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
      return;
    }
    activacion = (int)jsonDocument["activacion"]; // se obtiene la respuesta
    tiempo = (int)jsonDocument["tiempo"]; // se obtiene la respuesta
    Serial.print("activacion: ");
    Serial.println(activacion);
    Serial.print("tiempo: ");
    Serial.println(tiempo);
  }
  http.end(); //Close connection
}
