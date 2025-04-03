#include <Arduino.h>
const int pinbotao = 3; // Definição de uma constante para o pino do botão

///  Prototipos dos funções
void ligaLed(int); // Definição de uma constante para o pino do botão

void desligaLed(int); // Definição de uma constante para o pino do botão

void piscaLed(int, unsigned long); // Definicao global para piscar o led

int somaDeDoisNumero(int, int); // Definição para somar dois

void setup()
{
  pinMode(2, OUTPUT); // OUTPUT  e a saida do pinLed
  Serial.begin(9600); // mostrar as mensagem no serial
}

void loop()
{
  // função para piscar o LED no pino 2 com um tempo de 100 milissegundos
  piscaLed(2, 100);                           // funcao para ligar o led
  int resultadoSoma = somaDeDoisNumero(4, 8); // funcao para somar 4 e o 8
  Serial.println(resultadoSoma);              // mostrar no serial a soma do resultado
}

//Função para ligar o LED 
void ligaLed(int pin) // criacao do ligaLed

{
  digitalWrite(2, HIGH); // definicao de ligar o pinLed
}

//Função para desligar o LED
void desligaLed(int pin) // criacao de desligaLed
{
  digitalWrite(pin, LOW); // definicao de desligar o Led
}

// Função para piscar o LED
void piscaLed(int pin, unsigned long tempo) // criacao de piscaLed
{
  ligaLed(pin);    // ligar o led
  delay(tempo);    // Espera novamente pelo tempo especificado
  desligaLed(pin); // desligar o lid
  delay(tempo);    // Espera novamente pelo tempo especificado
}
// Função para somar dois números
int somaDeDoisNumeros(int numeroA, int numeroB) // criacao  da somaDeDoisNumeros
{
  int resultado = numeroA + numeroB; // soma dos dois numero
  return resultado;                  // retornar o resultado
}