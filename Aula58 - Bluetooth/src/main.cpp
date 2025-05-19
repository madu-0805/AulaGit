/*Maria Eduarda Santos
14/04/25
atividade: BLUETOOH
aula 58
*/

#include <Arduino.h>
#include <BluetoothSerial.h>
#define pinLed 2

BluetoothSerial BT;

void setup()
{
  pinMode(pinLed, OUTPUT);

  BT.begin("ESPSantos");
}

void loop()
{

  static bool estadoLed = false;
  static bool pisca = false;

  if (BT.available())
  {
    String mensagem = BT.readStringUntil('\n');
    mensagem.trim();

    if (mensagem.equals("liga"))
    {
      estadoLed = true;
      BT.println("led ligado");
      pisca = false;
    }
    else if (mensagem.equals("desligado"))
    {
      estadoLed = false;
      BT.println("led desligado");
      pisca = false;
    }
    else if (mensagem.equals("pisca"))
    {
      pisca = true;
    }
  }
  if (pisca == true)
  {
    unsigned long tempoAtual = millis();
    static unsigned long tempoInicial = 0;

    if (tempoAtual - tempoInicial >= 300)
    {
      estadoLed = !estadoLed;
      tempoInicial = tempoAtual;
      BT.println("pisca led");
    }
    digitalWrite(pinLed, estadoLed);
  }
}
