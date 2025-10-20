#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;
bool leituraBit(uint8_t valor, uint8_t bit);
void setup()
{
  Serial.begin(9600);
  mcp.begin_I2C();

  for (int p = 0; p <= 7; p++) // entradas
    // qnd a uma linha so nao precisa de {} so quando ha mais linhas
    mcp.pinMode(p, INPUT);

  mcp.pinMode(8, OUTPUT);
  mcp.digitalWrite(8, HIGH); // ligar os leds infraRed(INFRA VERMELHO)
}

void loop()
{
  uint8_t leitura = mcp.readGPIOA(); // a recebe todos ao mesmo tempo
  for (int b = 0; b <= 7; b++)
    Serial.print((leitura >> b) & 0x01);

  Serial.print("\t");
  Serial.println(leitura, HEX);
}

bool leituraBit(uint8_t valor, uint8_t bit)
{
  return ((valor >> bit) & 0x01);
}
///logico E 
//1 e 0 = 0
//1 e 1 =1