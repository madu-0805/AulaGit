#include <Arduino.h>
#include "Botao.h"

Botao btn_boot(0);

void setup()
{
  Serial.begin(9600);
  btn_boot.begin();
}

void loop()
{
  btn_boot.update();

  if (btn_boot.pressionado())
  {
    Serial.println("botao pressionado");
  }

  if (btn_boot.solto())
  {
    Serial.printf("o botao ficou pressionado %.02f segundos\n\r", btn_boot.duracaoUltimoEstado()/100);
  }
}
