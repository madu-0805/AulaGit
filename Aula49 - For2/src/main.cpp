#include <Arduino.h>
#define pinLed 2
#define pinBotao 0
/*maria eduarda silva
aula 49*/
void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);
  Serial.begin(9600);

  for (int j = 0; j < 11; j++) // e um laco de repeticao
  {
    for (int i = 0; i < 11; i++)
    {
      Serial.print(j);
      Serial.print(" x");
      Serial.print(i);
      Serial.print("=");
      Serial.println(j * i);
    }
    Serial.println("-------------------------");
  }
}

void loop()
{
}