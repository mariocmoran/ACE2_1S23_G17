// dht11
#include <DHT.h>
#include <DHT_U.h>

// conexion wifi
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

DHT dht(D2, DHT11);

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
  // conexion al wifi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a la red wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("¡Conexión exitosa!");
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

      // se guarda la activación y el tiempo actual
      POSTupdate(activacion, tiempo);
    } else { // está desactivado
      POSTupdate(activacion, 0);
    }

    // calculos
    Serial.println("calculos: ");
    calcularDHT11();
    Serial.println("");
    // se guardan los datos
    POST();

    // si esta activado y el tiempo tambien esta activado y el tiempo se acabó -> se apaga todo
    if (activacion == 1 && tiempo > 0 && contadorTiempo >= tiempo) { 
      POSTupdate(0, 0);
      Serial.println("apagando");
    }
  }

  dht.begin();
  delay(1000);
  Serial.println("");
}

void calcularDHT11() {
  int chk = DHT11.read(DHT11PIN);
  humedad = (int)DHT11.humidity;
  Serial.print("Humidity (%): ");
  Serial.println(humedad);
  tempInterna = (int)DHT11.temperature;
  Serial.print("Temperature (C): ");
  Serial.println(tempInterna);
}

void POST() {
  HTTPClient http;
  http.begin(wifiClient, hostPOST);
  http.addHeader("Content-Type", "application/json");

  // Data to send with HTTP POST
  String data = "{\"temperatura_externa\":"+String(humedad);
  data += ", \"temperatura_interna\":"+String(tempExterna);
  data += ", \"humedad_tierra\":"+String(tempInterna);
  data += ", \"porcentaje\":"+String(porcentajeAgua)+"}";

  // Send HTTP POST request
  int httpResponseCode = http.POST(data);

  //Serial.print(data);
  Serial.print("HTTP POST Response code: ");
  Serial.println(httpResponseCode);
    
  // Free resources
  http.end();
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
