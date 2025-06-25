/*Aula led rgb
11/06/2025*/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel ledRGB(1,48,NEO_GRB); // quantidade de led tem,o pino e o tipo

int r=0;
int g=0;
int b=0;

void setup()
{
  ledRGB.begin();
  ledRGB.setBrightness(32); // ele vai de 0 ~ 255 intensidade do brilho
  ledRGB.setPixelColor(0,ledRGB.Color(0,0,0));
  ledRGB.show();
}

void loop()
{
   ledRGB.setPixelColor(0,ledRGB.Color(r,g,b)); // numero das cores
  ledRGB.show();
}
