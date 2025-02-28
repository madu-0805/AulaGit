/* Maria Eduarda
27/02/2025
Atividade:
*/
#define pinLedVermelho 10
#define pinLedAzul 13
#define pinLedLaranja 8

int temperatura = 32;
float bateria = 10;  
float valor = 0;
int resultado =  0;


void setup()
{
  // ATIVIDADE 1
  Serial.begin(9600);
  pinMode(pinLedAzul,OUTPUT);
  
  if ( temperatura > 30){
  digitalWrite(pinLedAzul, HIGH);
  Serial.println("acender Led azul");
  }
  
   // ATIVIDADE 2
  if (bateria <20){
 
    pinMode(pinLedVermelho,OUTPUT); 
    digitalWrite(pinLedVermelho,HIGH);
    Serial.println("ligar o led vermelho");
  }
   
  // ATIVIDADE 3 
   
  int numero = 4;
  int resultado2= numero % 2;
   
  pinMode(pinLedLaranja,OUTPUT);
  if (resultado2 == 0){
  digitalWrite(pinLedLaranja, HIGH);
  }
  
  // ATIVIDADE 4

  int numeroI = -5;
  
  if (numeroI >0){
    Serial.println("numero positivo");
  }else if (numeroI < 0){
    Serial.println("numero negativo");
    }
  
  // ATIVIDADE 5
  
  int salario = 200;
  int resultado = 0;
  
  if (salario < 1000){
    resultado = salario * 10 / 100;}
  
  Serial.println("NOME: MARIA ");
  Serial.println("CARGO:estagio");
  Serial.println("o acrecimo eh de");
  Serial.println(resultado);
  
  //ATIVIDADE 6
  
  int salario1=  500;
  int resultado1= 0;
  
   if (salario1< 500){
    resultado1 = salario1 * 30 / 100;}
  
  Serial.println("NOME: Ana ");
  Serial.println("CARGO: jovem aprediz");
  Serial.println("o acrecimo eh de");
  Serial.println(resultado1);   
  
  
  
  // ATIVIDADE 7
   
  int valor1= 500;
  int valor2= 499;
  
  if(valor1>valor2){
    Serial.println("Valor1 E MAIOR");
    
  }else if(valor1<valor2){
    Serial.println("Valor1 e menor");
    }
    
   	// ATIVIDADE 8

int nota1 = 5;
int nota2 = 8;
int nota3 = 6;
int nota4 = 7;
float media = 4;
  
 media =(nota1+nota2+nota3+nota4)/ 4.0;
    if (media>=7){
    Serial.println("APROVADO");
    }else if (media<=7){
    Serial.println("REPROVADO");
    }
}

  void loop ()
  {
  }
 
 