#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>
/*controle do projeto em grupo
madu silva*/
Bounce botao1 = Bounce();
Bounce botao2 = Bounce();
Bounce botao3 = Bounce();
Bounce botao4 = Bounce();
Bounce botao5 = Bounce();
Bounce botao6 = Bounce();
Bounce botao7 = Bounce();
Bounce botao8 = Bounce();
Bounce botao9 = Bounce();

LiquidCrystal_I2C lcd(0x27, 20, 4);
#define botaoA 13
#define botaoB 12
#define botaoC 14
#define botaoD 27
#define botaoE 26
#define botaoF 25
#define botaoK 32
#define botaoX 35
#define botaoY 34
#define pinLed 2

char VL1 = 1;
byte velocimetro1[] =
    {
        B00000,
        B00000,
        B00000,
        B00011,
        B00100,
        B01000,
        B10000,
        B10001};

char VL2 = 2;
byte velocimetro2[] =
    {B00000,
     B00000,
     B00000,
     B00011,
     B00100,
     B01000,
     B10000,
     B10001};

char VL3 = 3;
byte velocimetro3[] =
    {B00000,
     B00000,
     B00000,
     B11000,
     B00100,
     B10010,
     B10001,
     B10001};

char VL4 = 4;
byte velocimetro4[] =
    {B10001,
     B10000,
     B01000,
     B00100,
     B00011,
     B00000,
     B00000,
     B00000};

char setaDireita = 5;
byte seta1[] =
    {B00000,
     B00000,
     B00100,
     B00110,
     B11111,
     B00110,
     B00100,
     B00000};

char setaEsquerda = 6;
byte seta2[] =
    {B00000,
     B00000,
     B00100,
     B01100,
     B11111,
     B01100,
     B00100,
     B00000};

void setup()
{
    lcd.init();
    lcd.backlight();

    lcd.begin(16, 2);

    lcd.createChar(0, velocimetro1);
    lcd.setCursor(6, 0);
    lcd.write(0);

    lcd.createChar(1, velocimetro1);
    lcd.setCursor(6, 0);
    lcd.write(1);

    lcd.createChar(2, velocimetro1);
    lcd.setCursor(6, 1);
    lcd.write(2);

    lcd.createChar(3, velocimetro1);
    lcd.setCursor(7, 1);
    lcd.write(3);

    //**VELOCIMETRO1 */

    lcd.createChar(0, velocimetro2);
    lcd.setCursor(7, 0);
    lcd.write(0);

    lcd.createChar(1, velocimetro2);
    lcd.setCursor(6, 0);
    lcd.write(1);

    lcd.createChar(2, velocimetro2);
    lcd.setCursor(6, 1);
    lcd.write(2);

    lcd.createChar(3, velocimetro2);
    lcd.setCursor(7, 1);
    lcd.write(3);

    //**VELOCIMETRO2 */

    lcd.createChar(0, velocimetro3);
    lcd.setCursor(6, 1);
    lcd.write(0);

    lcd.createChar(1, velocimetro3);
    lcd.setCursor(6, 0);
    lcd.write(1);

    lcd.createChar(2, velocimetro3);
    lcd.setCursor(7, 0);
    lcd.write(2);

    lcd.createChar(3, velocimetro3);
    lcd.setCursor(7, 1);
    lcd.write(3);

    //**VELOCIMETRO3 */

    lcd.createChar(0, velocimetro4);
    lcd.setCursor(7, 1);
    lcd.write(0);

    lcd.createChar(1, velocimetro4);
    lcd.setCursor(6, 0);
    lcd.write(1);

    lcd.createChar(2, velocimetro4);
    lcd.setCursor(7, 0);
    lcd.write(2);

    lcd.createChar(3, velocimetro4);
    lcd.setCursor(6, 1);
    lcd.write(3);

    //**VELOCIMETRO4 */

    lcd.createChar(0, seta1);
    lcd.write(0);
    //**SETA1 */

    lcd.createChar(0, seta2);
    lcd.write(0);
    //**SETA2 */

    pinMode(botaoA, INPUT_PULLUP);
    pinMode(botaoB, INPUT_PULLUP);
    pinMode(pinLed,OUTPUT);
    botao1.attach(botaoA, INPUT_PULLUP);
    botao2.attach(botaoB, INPUT_PULLUP);
    botao3.attach(botaoC, INPUT_PULLUP);
    botao4.attach(botaoD, INPUT_PULLUP);
    botao5.attach(botaoE, INPUT_PULLUP);
    botao6.attach(botaoF, INPUT_PULLUP);

    
}
void loop()
{
    //**tratamento dos ruidos dos botoes

    botao1.update();
    botao2.update();
    botao3.update();
    botao4.update();
    botao5.update();
    botao6.update();
}
