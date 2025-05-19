#include <Arduino.h>
/*MARIA EDUARDA SILVA
AULA 50 WHILE
02/04/25
*/

#define pinBotao 5
#define pinLed 2
void setup()
{

  delay(2000);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);

  while (digitalRead(5) == 0)
  {
    digitalWrite(pinLed, HIGH);
    delay(200);
    digitalWrite(pinLed, LOW);
    delay(200);
  }
}

void loop() {}
