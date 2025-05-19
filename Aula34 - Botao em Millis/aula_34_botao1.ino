/* Maria Eduarda Silva
11/03/2025
ATIVIDADE : ligar o botao
aula 34 
*/
//READ LER
// bool estadoBotao= digitalRead(pinBotao);
//digitalWrite(pinLedVermelho, estadoBotao);

#define pinBotao 10
#define pinLedVermelho 2

unsigned long  tempoInicial = 0;
bool estadoLedVermelho = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(pinLedVermelho,OUTPUT);
  pinMode(pinBotao,INPUT);
}
void loop()
{
  
 /* bool estadoBotao= digitalRead(pinBotao);
  digitalWrite(pinLedVermelho, estadoBotao);
 */ 
  
   unsigned long tempoAtual = millis ();
  
  bool estadoBotao = digitalRead(pinBotao); 
  Serial.println(estadoBotao);
 
  if(estadoBotao){ //ligar o led
    
  if(tempoAtual - tempoInicial >= 200){
  estadoLedVermelho = !estadoLedVermelho;
  digitalWrite(pinLedVermelho, estadoLedVermelho);
   tempoInicial = tempoAtual;
  }
  }else 
    digitalWrite(pinLedVermelho,LOW);
  
}
    