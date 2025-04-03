/*
NOMES: Gui, Madu 3, Richard
DATA: 28/03/2025
PROJETO: JESUS TE AMA

*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define pinLed 2
#define botao1 23
#define botao2 19
#define botao3 4

// ******* criacao do nosso emoji

char fase = 1;
byte coracao[] = {
    B00000,
    B00000,
    B11011,
    B10101,
    B10001,
    B01010,
    B00100,
    B00000};

// *********** variaveis globais **********

unsigned long tempoInicial = 0;

// *********** final das variaveis globais *******

void setup()
{
  lcd.init();
  lcd.createChar(0, coracao);
  lcd.backlight();
  pinMode(pinLed, OUTPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);
}

void loop()
{

  static bool estadoLed = 1;

  unsigned long tempoAtual = millis();

  const unsigned long tempoFiltro = 50;

  // * ******** INICIO DO BOTAO 1 ************
  bool estadoAtual1 = digitalRead(botao1);
  static bool estadoAnterior1 = 1;
  static bool ultimaAcaoBotao1 = 0;
  static unsigned long tempoUltimaAlteracaoBotao1 = 0;
  static bool fraseBotao1 = 0;

  if (estadoAtual1 != estadoAnterior1)
  {
    tempoUltimaAlteracaoBotao1 = tempoAtual;
  }

  if ((tempoAtual - tempoUltimaAlteracaoBotao1) > tempoFiltro)
  {
    if (estadoAtual1 != ultimaAcaoBotao1)
    {
      ultimaAcaoBotao1 = estadoAtual1;
      if (estadoAtual1 == 0)
      {
        fraseBotao1 = !fraseBotao1;
      }
    }
  }
  estadoAnterior1 = estadoAtual1;
  // ********* FIM DO BOTAO 1 ***********

  // * ******** INICIO DO BOTAO 2 ************
  bool estadoAtual2 = digitalRead(botao2);
  static bool estadoAnterior2 = 1;
  static bool ultimaAcaoBotao2 = 0;
  static unsigned long tempoUltimaAlteracaoBotao2 = 0;
  static bool fraseBotao2 = 0;

  if (estadoAtual2 != estadoAnterior2)
  {
    tempoUltimaAlteracaoBotao2 = tempoAtual;
  }

  if ((tempoAtual - tempoUltimaAlteracaoBotao2) > tempoFiltro)
  {
    if (estadoAtual2 != ultimaAcaoBotao2)
    {
      ultimaAcaoBotao2 = estadoAtual2;
      if (estadoAtual2 == 0)
      {
        fraseBotao2 = !fraseBotao2;
      }
    }
  }
  estadoAnterior2 = estadoAtual2;
  // ********* FIM DO BOTAO 2 ***********

  // * ******** INICIO DO BOTAO 3 ************
  bool estadoAtual3 = digitalRead(botao3);
  static bool estadoAnterior3 = 1;
  static bool ultimaAcaoBotao3 = 0;
  static unsigned long tempoUltimaAlteracaoBotao3 = 0;
  static bool fraseBotao3 = 0;

  if (estadoAtual3 != estadoAnterior3)
  {
    tempoUltimaAlteracaoBotao3 = tempoAtual;
  }

  if ((tempoAtual - tempoUltimaAlteracaoBotao3) > tempoFiltro)
  {
    if (estadoAtual3 != ultimaAcaoBotao3)
    {
      ultimaAcaoBotao3 = estadoAtual3;
      if (estadoAtual3 == 0)
      {
        fraseBotao3 = !fraseBotao3;
      }
    }
  }
  estadoAnterior3 = estadoAtual3;
  // ********* FIM DO BOTAO 3 ***********

  // *********TRATAMENTO DO DISPLAY ***********

  // quando botao 1 precionado

  if (fraseBotao1)
  {
    lcd.setCursor(2, 1);
    lcd.print("JESUS");
  }
  else
  {
    lcd.setCursor(2, 1);
    lcd.print("     ");
  }

  // quando botao 2 precionado

  if (fraseBotao2)
  {
    lcd.setCursor(3, 2);
    lcd.print("TE AMA");
  }
  else
  {
    lcd.setCursor(3, 2);
    lcd.print("       ");
  }

  // quando botao 3 precionado

  if (fraseBotao3)
  {
    if (tempoAtual - tempoInicial >= 200)
    {
      if (!estadoLed)
      {

        digitalWrite(pinLed, LOW);
        lcd.setCursor(8, 1);
        lcd.print(" ");
        lcd.setCursor(10, 2);
        lcd.print(" ");
        lcd.setCursor(2, 2);
        lcd.print(" ");
        lcd.setCursor(1, 1);
        lcd.print(" ");

        estadoLed = 1;
      }
      else
      {

        digitalWrite(pinLed, HIGH);
        lcd.setCursor(8, 1);
        lcd.write(0);
        lcd.setCursor(10, 2);
        lcd.write(0);
        lcd.setCursor(2, 2);
        lcd.write(0);
        lcd.setCursor(1, 1);
        lcd.write(0);

        estadoLed = 0;
      }
      tempoInicial = tempoAtual;
    } 
  }
}