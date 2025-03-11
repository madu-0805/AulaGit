/* Maria Eduarda Silva
10/03/2025
ATIVIDADE: Semaforo sem delay
*/ 

#define pinLedVermelho 13
#define pinLedAmarelo 12
#define pinLedVerde 11

#define tempoVermelho 5000;
#define tempoAmarelo 2000;
#define tempoVerde 3000;

unsigned long tempoInicial = 0;
char faseSemaforo =0;



void setup() 
  
{ 
 pinMode(pinLedVermelho,OUTPUT);
 pinMode(pinLedAmarelo, OUTPUT);
 pinMode(pinLedVerde,OUTPUT);
}

void loop()
{
  unsigned long tempoAtual = millis();

  if (faseSemaforo==0)
  {
    digitalWrite(pinLedVermelho, HIGH);
    digitalWrite(pinLedAmarelo,LOW);
    digitalWrite(pinLedVerde,LOW);

    if(tempoAtual - tempoInicial  >= 5000)
    {
      faseSemaforo = 1;
      tempoInicial =tempoAtual;
  	}
  }
else if (faseSemaforo ==1)
{
digitalWrite(pinLedVermelho,LOW);
digitalWrite(pinLedAmarelo, LOW);
digitalWrite(pinLedVerde,HIGH);
if(tempoAtual - tempoInicial >= 3000)
 {
faseSemaforo=2;
tempoInicial= tempoAtual;
}

}
 else if (faseSemaforo ==2)
 {
  digitalWrite(pinLedVermelho,LOW);
  digitalWrite(pinLedAmarelo,HIGH);
  digitalWrite(pinLedVerde,LOW);
   if(tempoAtual-tempoInicial >= 2000)
   {
     faseSemaforo= 0;
     tempoInicial = tempoAtual;
     
   }
 }
}