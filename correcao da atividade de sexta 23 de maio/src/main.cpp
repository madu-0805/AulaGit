#include <Arduino.h>
#include "temporizador.h"
#include "led.h"
#include "botao.h"

Botao btn_boot(2);

Temporizador tempo_10s(1000);
Led led_placa(2);

void setup()
{
  btn_boot.mudanca();
}

void loop()
{
  btn_boot.tratamento();
  led_placa.update();
 

  if (btn_boot.pressionado())
  {
    if (!tempo_10s.estaAtivo())
      tempo_10s.iniciar();

    else
      tempo_10s.reiniciar();

    led_placa.piscar(3);
  }

  if (tempo_10s.estaPronto())
  {
    led_placa.desligar();
    tempo_10s.parar();
  }
}
