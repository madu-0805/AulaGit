/* Maria Eduarda Silva
06/03/2025
ATIVIDADE:
*/
#define pinLedVermelho 13
#define pinLedLaranja 12
#define pinLedAzul 11
#define pinLedAmarelo 10
#define pinLedVerde 9
#define pinLedBranco 8
int escolha = 4;

void setup()
  
{
  pinMode(pinLedVermelho,OUTPUT);
  pinMode(pinLedLaranja, OUTPUT);
  pinMode(pinLedAmarelo, OUTPUT);
  pinMode(pinLedAzul, OUTPUT);
  pinMode(pinLedVerde,OUTPUT);
  pinMode(pinLedBranco, OUTPUT);
  Serial.begin(9600);
  int qualidadeAr =0;

  
 switch(qualidadeAr)
 {
  case 0:
   digitalWrite(pinLedVermelho,HIGH);
  Serial.println("pessimo");
   break;

  
 case 1:
 digitalWrite(pinLedLaranja,HIGH);
  Serial.println("ruim");
  break;
  
  
  case 2:
  digitalWrite(pinLedAzul,HIGH);
  Serial.println("normal");
  break;
  
  
  case 3:
  digitalWrite(pinLedAmarelo,HIGH);
  Serial.println("boa");
  break; 
  
  
  case 4:
  digitalWrite(pinLedVerde,HIGH);
  Serial.println("execelente");
  break;
  
  
  default:
 digitalWrite(pinLedBranco,HIGH);
  Serial.println("erro");
 }
 }
void loop()
{
}