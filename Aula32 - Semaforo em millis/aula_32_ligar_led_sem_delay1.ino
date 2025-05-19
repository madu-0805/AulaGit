/* Maria Eduarda Silva
07/03/2025
ATIVIDADE : ligar o led sem o delay
*/

#define pinLedVermelho 13

unsigned long tempoInicial =0;
bool estadoLed= 1;



void setup()
{
    pinMode(pinLedVermelho, OUTPUT);
}

void loop()
{
  unsigned long tempoAtual = millis ();
  
  if(tempoAtual - tempoInicial >= 1000){
    
    if (!estadoLed){
  digitalWrite(pinLedVermelho, HIGH);
    estadoLed= 1;  
  }
  
  else{digitalWrite(pinLedVermelho,LOW);
       estadoLed =0;
    }
    tempoInicial = tempoAtual;
  }
 
}