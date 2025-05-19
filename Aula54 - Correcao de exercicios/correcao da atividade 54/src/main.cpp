/*Maria Eduarda Santos
09/04/2025
CORRECAO NO DIA 07/04
*/

#include <Arduino.h>
#include <Bounce2.h>
#include <LiquidCrystal_I2C.h>

#define LedA 15
#define LedB 2
#define LedC 4
#define LedD 5

#define botaoA 9
#define botaoB 10
#define botaoC 11
LiquidCrystal_I2C lcd(0x27, 20, 4);

//*instancia de objeto
Bounce botao1 = Bounce();
Bounce botao2 = Bounce();
Bounce botao3 = Bounce();

void setup()
{
  Serial.begin(9600);
  botao1.attach(botaoA, INPUT_PULLUP);
  botao2.attach(botaoB, INPUT_PULLUP);
  botao3.attach(botaoC, INPUT_PULLUP);

  lcd.init();      // inicar
  lcd.backlight(); // ligar a luz
  lcd.setCursor(0, 0);
  lcd.print(">LED 1 0%");
  lcd.setCursor(0, 1);
  lcd.print(">LED 2 0%");
  lcd.setCursor(0, 2);
  lcd.print(">LED 3 0%");
  lcd.setCursor(0, 3);
  lcd.print(">LED 4 0%");

  pinMode(LedA, OUTPUT);
  pinMode(LedB, OUTPUT);
  pinMode(LedC, OUTPUT);
  pinMode(LedD, OUTPUT);
}

void loop()
{
  static bool modoSelecao = 1;
  static int contador = 0;
  static int itnsLedA = 0;
  static int itnsLedB = 0;
  static int itnsLedC = 0;
  static int itnsLedD = 0;
  static bool alteracao = 0;

  botao1.update();
  botao2.update();
  botao3.update();
  //**Botao C */

  if (!botao3.fell())
  {
    modoSelecao = !modoSelecao; // quando for inverter o numero e so colocar !
  }

  //**botao B */
  if (botao2.fell())
  {
    if (modoSelecao)
    {
      contador++;
      // contador += 1;       //contador = contador + 1;     // qualquer um vai funcionar
      //*if (contador >3)contador = 0;

      if (contador > 3)
      {
        contador = 0;
      }
    }
    else
    {
      switch (contador)
      {
      case 0:
        if (itnsLedA > 0)
          itnsLedA -= 10;
        break;

      case 1:
        if (itnsLedB > 0)
          itnsLedB -= 10;
        break;

      case 2:
        if (itnsLedC > 0)
          itnsLedC -= 10;
        break;

      case 3:
        if (itnsLedD > 0)
          itnsLedD -= 10;
        break;

      default:
        break;
      }
    }
  }

  //*botao A
  if (botao1.fell())
  {
    if (modoSelecao)
    {
      contador--;
      // contador -= 1;       //contador = contador - 1;     // qualquer um vai funcionar
      //*if (contador >3)contador = 0;

      if (contador < 0)
      {
        contador = 3;
      }
    }
    else
    {
      switch (contador)
      {
      case 0:
        if (itnsLedA <= 90)
          itnsLedA += 10;
        break;

      case 1:
        if (itnsLedB <= 90)
          itnsLedB += 10;
        break;

      case 2:
        if (itnsLedC <= 90)
          itnsLedC += 10;
        break;

      case 3:
        if (itnsLedD <= 90)
          itnsLedD += 10;
        break;

      default:
        break;
      }
    }
  }

  //*LCD
  if (alteracao)
  {

    alteracao = 0;
    if (modoSelecao)
    {
    }
  }

  if (contador == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(">");

    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(0, 3);
    lcd.print(" ");

    lcd.setCursor(10, 0);
    lcd.print("intnsLedA ");
  }
  else if (contador == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print(">");

    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(0, 2);
    lcd.print(" ");

    lcd.setCursor(10, 1);
    lcd.print("intnsLedB ");
  }
  else if (contador == 2)
  {
    lcd.setCursor(0, 2);
    lcd.print(">");

    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(0, 3);
    lcd.print(" ");

    lcd.setCursor(10, 2);
    lcd.print("intnsLedC");
  }
  else
  {
    lcd.setCursor(0, 3);
    lcd.print(">");

    lcd.setCursor(0, 2);
    lcd.print(" "); // apagando
    lcd.setCursor(0, 0);
    lcd.print(" "); // apagando

    lcd.setCursor(10, 3);
    lcd.print("intnsLedD ");
  }
  //* Leds
  analogWrite(LedA, itnsLedA * 2.55);
  analogWrite(LedB, itnsLedB * 2.55);
  analogWrite(LedC, itnsLedC * 2.55);
  analogWrite(LedA, itnsLedD * 2.55);
}