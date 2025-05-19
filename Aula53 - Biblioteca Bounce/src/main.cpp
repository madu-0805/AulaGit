/*MADU SANTOS E GUI
07/04/25
ATIVIDADE:
AULA 53
*/
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <Bounce2.h>

/// intensidades
int intensidadeLedAmarelo = 0;
int intensidadeLedBranco = 0;
int intensidadeLedVermelho = 0;
int intensidadeLedVerde = 0;

//***** instancias */
Bounce botao1 = Bounce();
Bounce botao2 = Bounce();
Bounce botao3 = Bounce();

/// DEFINFICAO DOS LEDS
#define pinLedAmarelo 15
#define pinLedBranco 18
#define pinLedVermelho 19
#define pinLedVerde 23

/// DEFINICAO DOS BOTOES
#define pinbotao1 4
#define pinbotao2 2
#define pinbotao3 5

// VARIAVES GLOBAIS

int contagem = 0;
static bool modoSelecao;

void setup()
{
  Serial.begin(9600);
  //******* Saidas */

  pinMode(pinLedAmarelo, OUTPUT);
  pinMode(pinLedBranco, OUTPUT);
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);

  //****** Entradas */

  pinMode(pinbotao1, INPUT_PULLUP);
  pinMode(pinbotao2, INPUT_PULLUP);
  pinMode(pinbotao3, INPUT_PULLUP);

  //****** tratamento dos botoes */

  botao1.attach(pinbotao1, INPUT_PULLUP);
  botao2.attach(pinbotao2, INPUT_PULLUP);
  botao3.attach(pinbotao3, INPUT_PULLUP);

  //*******inicializacao do display */
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("<");
  lcd.setCursor(0, 1);
  lcd.print(">");
}

void loop()
{
  //***** tratamento  leds ******
  botao1.update();
  botao2.update();
  botao3.update();
  static bool estadoLedAmarelo = 1;
  static bool estadoLedBranco = 1;
  static bool estadoLedVermelho = 1;
  static bool estadoLedVerde = 1;
  static bool estadoLed = 0;

  static bool posicao = 0;
  // * ******** INICIO DO BOTAO 1 ************

  if (botao1.fell())
  {
    contagem++;
    if (contagem > 3)
    {
      contagem = 0;
    }
    Serial.println(contagem);
  }
  if (botao2.fell())
  {
    contagem--;
    if (contagem < 0)
    {
      contagem = 3;
    }
    Serial.println(contagem);
  }
  if (botao3.fell())
  {

    if (posicao == 0)
    {
      if (intensidadeLedAmarelo < 100)
        ;
    }
    intensidadeLedAmarelo += 10;
    Serial.println(intensidadeLedAmarelo);
  }
  
  else
  {
    if (intensidadeLedBranco < 100)
    {
      intensidadeLedBranco += 10;
      Serial.println(intensidadeLedBranco);
    }
  }
}
