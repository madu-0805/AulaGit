#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup()
{
  Serial.begin(9600);
  ads.begin();
}

void loop()
{
int leitura = ads.readADC_SingleEnded(0);// de 0 ate 3 
float tempC = leitura * 0.01875; // converter em temperatura de LM35

Serial.printf("Temperatura: %.2f °C \n, tempC");// %.2f 4 um float com 2 casa decimais 
delay(1000);
}
