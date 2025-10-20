/*
Maria Eduarda Silva dos Santos
29/07/25
Segundo semetres
*/

#include <Arduino.h>
#include <Bounce2.h>
#include <Adafruit_NeoPixel.h>
#define botao 0

Adafruit_NeoPixel ledRGB(1, 48, NEO_GBR);
Bounce bounce = Bounce();

uint32_t ledVerde = ledRGB.Color(0, 255, 0);
uint32_t ledAmarelo = ledRGB.Color(255, 255, 0);
uint32_t ledLaranja = ledRGB.Color(255, 165, 0);
uint32_t ledVermelho = ledRGB.Color(255, 0, 0);
uint32_t ledMagenta = ledRGB.Color(255, 0, 255);
uint32_t ledLimao = ledRGB.Color(173, 255, 47);
uint32_t ledVinho = ledRGB.Color(128, 0, 32);
uint32_t ledCoral = ledRGB.Color(255, 127, 80);
uint32_t ledCinza = ledRGB.Color(128, 128, 128);
uint32_t ledMarinho = ledRGB.Color(0, 0, 128);
uint32_t corAtual;

uint32_t cores[10] = {
    ledVerde, ledAmarelo, ledLaranja, ledVermelho,
    ledCinza, ledLimao, ledVinho, ledCoral, ledMarinho, ledMagenta};

int contagem = 0;

void setup()
{
  Serial.begin(9600);
  bounce.attach(botao, INPUT_PULLUP);
  bounce.interval(25); // Define o intervalo de debounce para 25 milissegundos (evita leituras falsas ao pressionar)

  ledRGB.begin();
  ledRGB.setBrightness(32);                       // ele vai de 0 ~ 255 intensidade do brilho
  ledRGB.setPixelColor(0, ledRGB.Color(0, 0, 0)); // 235, 52, 52
  ledRGB.show();
}

void loop()
{
  bounce.update();

  if (bounce.fell())
  {
    contagem++;
    if (contagem > 10)
    {
      contagem = 0;
    }

    ledRGB.setPixelColor(0, cores[contagem]);
    ledRGB.show();
  }
}