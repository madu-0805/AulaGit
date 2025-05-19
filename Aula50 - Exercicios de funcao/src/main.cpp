#include <Arduino.h>
const int pinbotao = 3;
/*Madu Silva 
cria funcao*/

///  Prototipos dos funções
void ligaLed(int);
void desligaLed(int);
void piscaLed(int, unsigned long);
int somaDeDoisNumero(int, int);

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  piscaLed(2, 100);
  int resultadoSoma = somaDeDoisNumero(4, 8);
  Serial.println(resultadoSoma);
}

void ligaLed(int pin)

{
  digitalWrite(2, HIGH);
}

void desligaLed(int pin)
{
  digitalWrite(pin, LOW);
}
void piscaLed(int pin, unsigned long tempo)
{
  ligaLed(pin);
  delay(tempo);
  desligaLed(pin);
  delay(tempo);
}
int somaDeDoisNumeros(int numeroA, int numeroB) // criacao  da somaDeDoisNumeros)
{
  int resultado = numeroA + numeroB;
  return resultado;
}