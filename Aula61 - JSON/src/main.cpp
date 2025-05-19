#include <Arduino.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#define pinBotaoBoot 0
/*madu silva
 aula Josn e Bounce*/
Bounce botaoBoot = Bounce();
JsonDocument doc;

void setup()
{
  Serial.begin(9600);
  botaoBoot.attach(pinBotaoBoot, INPUT_PULLUP);
  randomSeed(analogRead(5));
}

void loop()
{
  botaoBoot.update();
  static int contagem = 0;
  if (botaoBoot.fell())
    contagem++;

  const char *estados[] = {"ok", "alerta", "erro"};

  float temperatura = random(200, 350) / 10.0; // random e aleatorio
  int umidade = random(40, 80);
  int opcoes = random(0, 3);

  doc["temperatura"] = temperatura;
  doc["umidade"] = umidade;
  doc["estados"] = estados[opcoes];
  doc["pressionamentos"] = contagem;

  unsigned long tempoAtual = millis();
  static unsigned long tempoInicial = 0;

  if (tempoAtual - tempoInicial > 500)
  {
    serializeJson(doc, Serial);
    Serial.println("");
    tempoInicial = tempoAtual;
   
  }
}
