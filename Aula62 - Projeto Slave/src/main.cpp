#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
/*madu silva
projeto controle slave*/
BluetoothSerial BT;
LiquidCrystal_I2C lcd(0x27, 20, 4);
JsonDocument doc;
#define pinLed1 2
#define pinLed 4

/*char SetaDireita = 3;
byte SetaD[] =
    {
        B00000,
        B00000,
        B00100,
        B00110,
        B11111,
        B00110,
        B00100,
        B00000};

char SetaEsquerda = 4;

byte SetaE[] =
    {
        B00000,
        B00000,
        B00100,
        B01100,
        B11111,
        B01100,
        B00100,
        B00000};
*/
void setup()
{
  Serial.begin(9600);



  pinMode(pinLed1, OUTPUT);

  if (BT.begin("EspSlaveMaduh"))
  {
    Serial.println("Bluetooth Iniciado com Sucesso");
    Serial.println(BT.getBtAddressString());
  }

  else
  {
    Serial.println("Erro ao iniciar o Bluetooth");
  }
}

void loop()
{
  if (BT.available())
  {
    String payload = BT.readStringUntil('\n');
    payload.trim();
    Serial.println(payload);
  }
}
