#include <Arduino.h>
#include <ArduinoJson.h>

JsonDocument doc;

void setup()
{
  Serial.begin(9660);
}

void loop()
{
  float temperatura = doc["temperatura"];
  int umidade = doc["umidade"];
  String estados = doc["estados"];
  int botao = doc["pressionamentos"];

  if (Serial.available())
  {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    deserializeJson(doc, msg);

    if (!doc["temperatura "].isNull())
      temperatura = doc["temperatura"];

    if (!doc["umidade"].isNull())
      umidade = doc["umidade"];

      if(!doc["estado"].isNull())
      estados=doc["estado"].as<String>();

      if(!doc["pressionamentos"].isNull())
      botao=doc["pressionamentos"];

    Serial.printf("a temperatura e  %f\n\r ", temperatura);
    Serial.printf("a umidade esta em %d%\n\r", umidade);
    Serial.printf("o estado esta %s\n\r", estados);
    Serial.printf("o botao foi pressionado %d vezes\n\r", botao);
  }
}
