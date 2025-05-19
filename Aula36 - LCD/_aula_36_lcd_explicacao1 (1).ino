#include <LiquidCrystal_I2C.h>

/*Maria Eduarda
14/03/25
ATIVIDADE:LCD 
aula 36
*/
LiquidCrystal_I2C lcd(0x27,16,2);
int estadoAnterior = 0 ;
int estadopinLed = 0;
int estadoBotao = 0;
#define pinLed 13
#define Botao 3
//#include <LiquidCrystal_I2C.h> nao tem lcd.serCursor
void setup()
{
lcd.init();
lcd.backlight();
pinMode(pinLed,OUTPUT);
pinMode(Botao,INPUT);
}

void loop()
{
  bool estadoAtual= digitalRead(Botao);
  if (estadoAtual== 1 && estadoAnterior== 0 )
  {
  estadopinLed = !estadopinLed ;
  }
  digitalWrite(pinLed, estadopinLed);
  if(estadopinLed)
  {
  lcd.setCursor(0,0);// CURSOR E O lugar
  lcd.print("ligado   "); //
  }
  else 
  {
  lcd.setCursor(0,0);
  lcd.print("desligado");
  }
  estadoAnterior = estadoAtual;
}






//#include <LiquidCrystal_I2C.h> nao tem lcd.serCursor
/* 
void loop
{
bool estadoAtualBotao= digitalRead(pinBotao);
static bool estadoAnteriorBotao ==0;
static bool estadoLed=0;

if(estadoAtualBotao == 1 && estadoAnterior== 0 )
{
estadoLed =!estadoLed;
digitalWrite(pinLed,estadoLed);

if (estadoLed == 1)
{
lcd.setCursor(0,0);
lcd.print("ligado   ");
}
else
{
lcd.setCursor(0,0);
lcd.print("desligado");
}
estadoAnterior = estadoAtual;
}
{
*/
