#include <LiquidCrystal_I2C.h>

/*Maria Eduarda Silva
14/03/2025
ATIVIDADE
aula:37
continuacacao de sexta feira
*/
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
}

void loop()
{
 int Botao = analogRead(A0);
    Serial.println(Botao);
 
  
  
  if(Botao == Botao1) 
  {
  lcd.setCursor(0,0);
  lcd.print("ligado       ");     
  }
  
  
  if (Botao>= Botao2 * 0.9 && Botao<= Botao2 *1.1)
  {
  lcd.setCursor(0,0);
    lcd.print("ligado       "); 
  }
  
  
  
  if(Botao == Botao3)
  {
  if (Botao>=Botao3 *0.9 && Botao<= Botao3* 1.1)
  lcd.setCursor(0,0);
    lcd.print("ligado      ");
  }
  
  
  
  if (Botao == Botao4)
  {
    if(Botao>= Botao4 * 0.9 && Botao <= Botao4 * 1.1)
  lcd.setCursor(0,0);
  lcd.print("ligado      ");
  }
  
  
  
  if(Botao== Botao5)
  {
  if(Botao>= Botao5 *0.9 && Botao <= Botao5 * 1.1)
  lcd.setCursor(0,0);
  lcd.print("ligado         ");
  }
  
    
  if (Botao ==1023) 
  {
    
  lcd.setCursor(0,0);
  lcd.print(" desligado"); 
  }
  
  
}

