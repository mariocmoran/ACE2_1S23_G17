//DHT11
#include <dht11.h>
#define DHT11PIN 4
dht11 DHT11;
//BMP280
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define BMP_SCK (52)
#define BMP_MISO (50)
#define BMP_MOSI (51)
#define BMP_CS (53)
Adafruit_BMP280 bmp;
Adafruit_BMP280 sensor(BMP_CS);
float TEMPERATURA;
float PRESION;
//ANEMOMETRO
volatile int contador = 0;
float rads = 0;
float linealv = 0;
//HUMEDAD ABSOLUTA
float RH;          // humedad relativa
float AH;           // humedad absoluta; densidad de vapor de agua
float T;            // Temperatura
float DS;           // DENSIDAD DE VAPOR SATURADO; se busca en tabla
//PUNTO DE ROCÍO
float potencia = 1.00000/8.00000;  //Para simular una raiz octava; NO SE CAMBIA
float octava;
float Inoctava;
float PT;

void   setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando:");
  //dht11 (nothing)
  //bmp280c
  if (!sensor.begin()) {
    Serial.println("BMP280 no encontrado.");
    while(1);
  }
  //anemometro
  attachInterrupt(0, interrupcion0, RISING);
}

void loop()
{
  //DHT 11 --------------------------------------------
  Serial.println();
  int chk = DHT11.read(DHT11PIN);
  RH = (float)DHT11.humidity;
  Serial.print("Humidity (%): ");
  Serial.println(RH, 2);
  T = (float)DHT11.temperature;
  Serial.print("Temperature   (C): ");
  Serial.println(T, 2);
  
  //HUMEDAD ABSOLUTA ----------------------------------
  if ((T >= 0.00) && (T < 4.00)){
    DS = 0.004847;
  }else if((T >= 5.00) && (T < 9.00)){
    DS = 0.006796;
  }else if((T >= 10.00) && (T < 14.00)){
    DS = 0.009401;
  }else if((T >= 15.00) && (T < 19.00)){
    DS = 0.01283;
  }else if((T >= 20.00) && (T < 24.00)){
    DS = 0.01730;
  }else if((T >= 25.00) && (T < 29.00)){
    DS = 0.02305;
  }else if((T >= 30.00) && (T < 34.00)){
    DS = 0.03038;
  }else if((T >= 35.00) && (T < 39.00)){
    DS = 0.03964;
  }
  AH = (RH*DS)/100;
  Serial.print("Humedad Absoluta: ");
  Serial.print(AH);
  Serial.print(" kg/m3");
  Serial.println("");
  //PUNTO DE ROCÍO
  Inoctava = RH/100;
  octava = pow(Inoctava, potencia);
  PT = octava*(112+(0.9*T))+(0.1*T)-112;
  Serial.print("Punto de Rocio: ");
  Serial.print(PT);
  Serial.print(" C td");
  Serial.println("");

  //BMP280 --------------------------------------------
  /* TEMPERATURA = bmp.readTemperature();
  PRESION = bmp.readPressure()/100; //Pascales */
  Serial.print("Temperatura (BPM280): ");
  Serial.print(sensor.readTemperature());
  Serial.print(" (C)");
  Serial.println("");
  
  Serial.print("Presion: ");
  Serial.print((sensor.readPressure()/133.3));
  Serial.print(" mmHg");
  Serial.println("");

  //ANEMOMETRO ---------------------------------------
  // V = w*r
  rads = (contador*20)*(2*3.1416)/60;
  linealv = (rads*0.0375)*3600/1000;
  Serial.print(linealv);
  Serial.println(" km/h");
  contador = 0;

  delay(2000);
}

void interrupcion0() {
  contador++;  
}