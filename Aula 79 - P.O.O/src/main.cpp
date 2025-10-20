#include <Arduino.h>
/*Madu Santos 
19/05/25
P.o.o
*/  

#include"Led.h"

Led ledESP(2);
Led ledVermelho(23);
Led ledBranco (4);
Led ledAmarelo(5);

void setup()
{
  ledESP.piscar(2);
  ledVermelho.piscar(5);
  ledBranco.piscar(4);
  ledAmarelo.piscar(3);

}

void loop()
{
ledESP.update();
ledVermelho.update();
ledAmarelo.update();
ledBranco.update();

}
