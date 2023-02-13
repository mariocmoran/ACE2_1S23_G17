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

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature   (C): ");
  Serial.println((float)DHT11.temperature, 2);

  //BMP280 --------------------------------------------
  /*
  TEMPERATURA = bmp.readTemperature();
  PRESION = bmp.readPressure()/100; //Pascales
  */
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