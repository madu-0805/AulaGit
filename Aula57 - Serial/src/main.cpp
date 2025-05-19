#include <Arduino.h>
#define pinLed 2
/**madu silva
 aula 57
*/
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop()
{

  static bool estadoLed = false;

  static bool pisca = false;
  static int velocidade = 700;

  if (Serial.available())
  {
    String texto = Serial.readStringUntil('\n');
    Serial.printf("Voce digitou: %s\n\r", texto);
    texto.trim();

    if (texto.equals("liga"))
    {
      estadoLed = true;
      pisca = false;
    }

    else if (texto.equals("desliga"))
    {
      estadoLed = false;
      pisca = false;
    }

    else if (texto.equals("pisca"))
    {
      pisca = true;
    }

    else if (texto.equals("mais rapido"))
    {
      velocidade = velocidade - 50;
      if(velocidade < 50) velocidade = 50;
      Serial.println(velocidade);

    }

    else if (texto.equals("mais lento"))
    {
      velocidade = velocidade + 50;
      if(velocidade > 1000) velocidade = 1000;
      Serial.println(velocidade);
    }

    else
    {
      Serial.println("comando não encontrado");
    }
  }

  if (pisca == true)
  {
    unsigned long tempoAtual = millis();
    static unsigned long tempoInicial = 0;

    if (tempoAtual - tempoInicial >= velocidade)
    {
      estadoLed = !estadoLed;
      tempoInicial = tempoAtual;
    }
  }

  // AGORA EU SEI OQUE FAZER

  digitalWrite(pinLed, estadoLed);
}

//* LER APENAS UM CARACTER
// void loop()
// {
//  if (Serial.available())
//    {
//        char caracter = Serial.read();
//        Serial.printf("Recebido letra: %c\n\r", caracter);

//        if (caracter == 'a')
//        {
//          digitalWrite(pinLed, HIGH);
//        }

//        else if (caracter == 'b')
//        {
//          digitalWrite(pinLed, LOW);
//        }
//    }
// }
