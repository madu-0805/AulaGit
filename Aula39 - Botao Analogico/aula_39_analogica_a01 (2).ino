/*#include <LiquidCrystal_I2C.h>

Maria Eduarda Silva
14/03/2025
ATIVIDADE A0
aula:37
continuacao de sexta feira

#define Botao1   0
#define Botao2  145 
#define Botao3  329
#define Botao4  505
#define Botao5  741
LiquidCrystal_I2C lcd (0x27,16,2);


void setup()
{
 Serial.begin(96000); 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("<LED A");
  lcd.setCursor(0,1);
  lcd.print("LED B OFF");
  
}

void loop()
{
 int Botao = analogRead(A0);
    Serial.println(Botao);
 
    
  if(Botao == Botao1) 
  {
  lcd.setCursor(0,0);
  lcd.print("Ligado");     
  }
  
  
  if (Botao>= Botao2 * 0.9 && Botao<= Botao2 *1.1)
  {
  lcd.setCursor(0,0);
  lcd.print("ligado");  
  lcd.setCursor(0,1);
   lcd.print(">");    
  }
  
  
  
  if(Botao == Botao3)
  
  {
  if (Botao>=Botao3 *0.9 && Botao<= Botao3* 1.1)
  lcd.setCursor(0,0);
  lcd.print("Ligado");
  }
  
  
  
  if (Botao == Botao4)
  {
  if(Botao>= Botao4 * 0.9 && Botao <= Botao4 * 1.1)
  lcd.setCursor(0,0);
  lcd.print("ligado");
  }
  
  
  
  if(Botao== Botao5)
  {
  if(Botao>= Botao5 *0.9 && Botao <= Botao5 * 1.1)
  lcd.setCursor(0,0);
  lcd.print("ligado");
  }
  
    
  if (Botao ==1023) 
  {
    
  lcd.setCursor(0,0);
  lcd.print("desligado"); 
  }
 
 
  
   
 
  if (Botao == Botao1)
  {
  lcd.setCursor(0,0);
  lcd.print( ">");
  }
   
   if (Botao == Botao2)
  {
  lcd.setCursor(0,0);
  lcd.print( "     ");
  }
   
  
  if (Botao == Botao2)
  {
  lcd.setCursor(0,1);
  lcd.print(">");
  }
 
  
    if (Botao == Botao1)
  {
  lcd.setCursor(0,1);
  lcd.print("       ");
   }     
 
 
  
  
  
  
  
  // OUTRA FORMA DE FAZER if 2
  
  if( Botao== Botao1)
  {
  lcd.setCursor(0,0);
  lcd.print(">");
  lcd.setCursor(0,1);
  lcd.print("    ");
  }  
  if(Botao == Botao2)
  {
  lcd.setCursor(0,1);
  lcd.print(">");
  lcd.setCursor(0,0);
  lcd.print("    ");
  }

  
}  

 */ 



#include <LiquidCrystal_I2C.h>
#define valorBotao1 0
#define valorBotao2 145  
#define valorBotao3 329  
#define valorBotao4 505
#define valorBotao5 741
#define valorSolto 1023
#define pinLedA 9
#define pinLedB 8
static int estadoLedA = 0;
static int estadoLedB = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(">LED A OFF");
  lcd.setCursor(0,1);
  lcd.print(" LED B OFF");
  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedB, OUTPUT);
}

void loop()
{
    int valorLeituraAnalogica = analogRead(A0);
    static int valorAnterior = 1023;
    static bool posicao = 0;
     static bool estadoLedA = 0;
     static bool estadoLedB =0 ;
 
  //***** TRATAMENTO DOS BOTOES *******
  // NENHUM BOTAO
  if (valorLeituraAnalogica == valorSolto)
   {
     
   }
 
  //BOTAO 1 PRESSIONADO
     else if(valorLeituraAnalogica == valorBotao1 &&
             valorAnterior == 1023)
    {
      posicao = 0;
    }
 
   //BOTAO 2 PRESSIONADO
      else if(valorLeituraAnalogica >= valorBotao2 * 0.9  &&
            valorLeituraAnalogica <= valorBotao2 * 1.1 &&
            valorAnterior == 1023)
    {
      posicao = 1;
    }
 
   //BOTAO 3 PRESSIONADO
    else if(valorLeituraAnalogica >= valorBotao3 * 0.9  &&
            valorLeituraAnalogica <= valorBotao3 * 1.1 &&
            valorAnterior == 1023)
    {
     
    }
   
   //BOTAO 4 PRESSIONADO
   else if(valorLeituraAnalogica >= valorBotao4 * 0.9  &&
            valorLeituraAnalogica <= valorBotao4 * 1.1 &&
            valorAnterior == 1023)
    {
     
    }
 
   //BOTAO 5 PRESSIONADO
      else if(valorLeituraAnalogica >= valorBotao5 * 0.9  &&
            valorLeituraAnalogica <= valorBotao5 * 1.1 &&
            valorAnterior == 1023)
    {
        if( posicao == 0)
        {
      estadoLedA = !estadoLedA; 
       } 
        
     else
       {
   estadoLedB = !estadoLedB;
      }
   
   
      }
   
  valorAnterior = valorLeituraAnalogica;

  //****** FIM DO TRATAMENTO DOS BOTOES ******
 
 
  // ***** ATUALIZA DISPLAY ******
 
        if(posicao == 0)
  {
    lcd.setCursor(0,0);
    lcd.print(">");
    lcd.setCursor(0,1);
    lcd.print(" ");
    
  
  lcd.setCursor(7,0);
    if (estadoLedA)
   {
        
    
     
     lcd.print("ON ");
      
   }  
   else
   {
   lcd.print("OFF");
   } 
     }    
        
  else
    {
    lcd.setCursor(0,1);
    lcd.print(">");
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.setCursor(7,1);
    
    
    if (estadoLedB){
    
    lcd.print("ON ");
    
    }
    else{  
    lcd.print("OFF");
    
    }
    }
         
        
 
  //***** ATUALIZACAO DOS LED ******
digitalWrite(pinLedA,estadoLedA);
digitalWrite(pinLedB,estadoLedB);
  
}



