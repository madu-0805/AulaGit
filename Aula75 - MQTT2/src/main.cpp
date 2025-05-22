/*Madu Silva
12/05/25 , 13/05/25 e 15/05/25 desafio final
MQTT
*/

#include <Arduino.h>
#include <ezTime.h>
#include "internet.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include <DHT.h>
#include "Led.h"
#include "Botao.h"

//* ----------- PROTOTIPAGEM ----------

void callback(char *, byte *, unsigned int);
void conectmqtt(void);

//* ------- CRIACAO DE OBJETOS
Timezone tempo;
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(23, DHT22);
Botao Boot(0);
JsonDocument doc;
Led ledESP(2);
Led ledVermelho(4);
Led ledBranco(22);
Led ledAmarelo(19);

//* ---------------------------------------------
//*     VARIAVEIS
const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *mqtt_client_id = "senai134_esp_maduSantos";
const char *mqtt_topic_sub = "senai134/mesa03/espMadu/subs";
const char *mqtt_topic_pub = "senai134/mesa03/esppMadu/public";
int freqEsp = 3;
int freqVermelho = 3;
int freqAmarelo = 3;
int freqBranco = 3;

float temperaturaLed = dht.readTemperature();
static bool piscaLed = false;
static bool estadoLed = false;
unsigned long tempoPisca = 500; // Tempo de piscamento do LED, em milissegundos
unsigned long contador = 0;
//* ---------------------------------------------

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);

  dht.begin();

  Serial.println(dht.readHumidity());
  Serial.println(dht.readTemperature());

  conectaWifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{

  Boot.tratamento();

  if (Boot.pressionado())
  {
    contador++;
    Serial.print("Botao foi pressionado : ");
    Serial.println(contador);
  }

  if (Boot.pressionando())
  {
    ledESP.ligar();
  }

  if (Boot.solto())
  {
    Serial.println("Botao Solto");
    ledESP.desligar();
  }

  ledESP.update();
  ledVermelho.update();
  ledAmarelo.update();
  ledBranco.update();

  Boot.tratamento();
  checkWifi();

  bool pressionado = false;

  if (!client.connected())
  {
    conectmqtt();
  }

  client.loop();

  static unsigned long tempoAnterior = 0;
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior > 2000)
  {
    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();

    if (temperatura < 0 || temperatura > 80 || umidade < 0 || umidade > 100)
    {
      Serial.println("Leitura fora do intervalo esperado!");
      return;
    }

    //  JSON
    doc["temperaturaLed"] = temperaturaLed;
    doc["temperatura"] = temperatura;
    doc["umidade"] = umidade;
    doc["timestamp"] = millis();

    // Criar string para armazenar o JSON
    String mensagem;
    serializeJson(doc, mensagem);

    // Publica os dados
    client.publish(mqtt_topic_pub, mensagem.c_str());
    // Serial.print("Publicado: ");
    // Serial.println(mensagem);

    tempoAnterior = tempoAtual;
  }
  /*if (Boot.mudanca())
    {
      pressionado = !Boot.solto();

      doc["estadoBotao"] = pressionado;

      String mensagemBotao;
      serializeJson(doc, mensagemBotao);

      client.publish(mqtt_topic_pub, mensagemBotao.c_str());
      // Serial.print("Publicado: ");
      // Serial.println(mensagemBotao);
    }*/

  static unsigned long tempoAnteriorPisca = 0;

  if (tempoAtual - tempoAnteriorPisca > 500)
  {
    float temperatura = dht.readTemperature();

    if (temperatura < 30 && temperatura > 27) // LED amarelo
    {

      piscaLed = true;
      ledAmarelo.piscar(freqAmarelo);
      ledVermelho.desligar();
      ledBranco.desligar();
    }
    else if (temperatura > 30) // led vermelho
    {

      piscaLed = true;
      ledVermelho.piscar(freqVermelho);
      ledAmarelo.desligar();
    }
    else if (temperatura > 0 && temperatura < 27) // led branco
    {

      piscaLed = true;
      ledBranco.ligar();
      ledAmarelo.desligar();
      ledVermelho.desligar();
    }

    else
    {
      ledBranco.desligar();
      ledVermelho.desligar();
      ledAmarelo.desligar();
    }

    tempoAnteriorPisca = tempoAtual;
  }
}

/*static unsigned long tempoAnteriorPisca = 0;

if (piscaLed == true)
{
  if (tempoAtual - tempoAnteriorPisca > tempoPisca)
  {
    estadoLed = !estadoLed;
    tempoAnteriorPisca = tempoAtual;
  }
  digitalWrite(2, estadoLed);
}*/

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensagem recebida em ");
  Serial.print(topic);
  Serial.print(": ");

  String mensagem = "";
  for (int i = 0; i < length; i++)
  {
    mensagem += (char)payload[i];
  }
  Serial.println(mensagem);

  JsonDocument doc;
  DeserializationError LedESP = deserializeJson(doc, mensagem);

  if (LedESP)
  {
    Serial.printf("Erro %s no formato json", LedESP.f_str());
  }
  else
  {
    if (!doc["estadoLed"].isNull())
    {
      int acaoLed = doc["estadoLed"];

      switch (acaoLed)
      {
      case 0:
        ledESP.desligar();
        ledAmarelo.desligar();
        ledBranco.desligar();
        ledVermelho.desligar();

        break;

      case 1:
        ledESP.ligar();
        ledAmarelo.ligar();
        ledBranco.ligar();
        ledVermelho.ligar();
        break;

      case 2:
        if (!doc["frequenciaLed"].isNull())
        {
          JsonObject freq = doc["frequenciaLed"];

          if (freq["esp"])
            freqEsp = freq["esp"];
          if (freq["vermelho"])
            freqVermelho = freq["vermelho"];
          if (freq["amarelo"])
            freqAmarelo = freq["amarelo"];
          if (freq["branco"])
            freqBranco = freq["branco"];
        }

        break;

        ledESP.piscar(freqEsp);
        ledAmarelo.piscar(freqAmarelo);
        ledBranco.piscar(freqBranco);
        ledVermelho.piscar(freqVermelho);

        break;
        Serial.print("opcao nao implementada");
      default:

        break;
      }
    }

    if (!doc["tempo"].isNull())
    {
      tempoPisca = doc["tempo"];
      Serial.print("Novo tempo de piscamento: ");
      Serial.println(tempoPisca);
    }
  }
}

void conectmqtt()
{
  while (!client.connected())
  {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(mqtt_client_id))
    {
      Serial.println("Conectado");
      client.subscribe(mqtt_topic_sub);
    }
    else
    {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s");
      delay(5000);
    }
  }
}