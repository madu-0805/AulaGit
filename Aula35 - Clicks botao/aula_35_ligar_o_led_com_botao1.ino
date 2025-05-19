/* Maria Eduarda Silva
12/03/2025
ATIVIDADE: led/botao
AULA 35
*/ 
#define pinBotao 11
#define pinLed 2

int estadoBotao = 0;
int estadoAnterior= LOW;
int estadopinLed= 0;
void setup()
{
 pinMode(pinBotao,INPUT);
 pinMode(pinLed,OUTPUT);
}

void loop()// SEMPRE PARA PENSAR NO PROBLEMA
{
    int estadoAtual= digitalRead(pinBotao); // READ= LER
    if(estadoAtual== HIGH && estadoAnterior == LOW){
    estadoBotao++;
    estadopinLed= !estadopinLed;
    digitalWrite(pinLed,estadopinLed);
    Serial.println(estadoBotao);
  }
  estadoAnterior = estadoAtual;
}


/*bool estadoAtual= digitalRead(pinBotao);
 static bool estadoLed=0;
 
 if(estadoAtual== 1 && estadoAnterior == 0)
 {
  estadoLed=!estadoLed;
  digitalWrite(pinLed,estadopinLed);
 }
  */

