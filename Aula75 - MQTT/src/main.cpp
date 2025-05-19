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
#include <Bounce2.h>
#include <DHT.h>
#include "Led.h"

//* ----------- PROTOTIPAGEM ----------

void callback(char *, byte *, unsigned int);
void conectmqtt(void);

//* ------- CRIACAO DE OBJETOS
Timezone tempo;
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(5, DHT22);
Bounce Boot = Bounce();
JsonDocument doc;
Led ledESP(2);
Led ledVermelho(23);
Led ledBranco (4);
Led ledAmarelo(5);


//* ---------------------------------------------
//*     VARIAVEIS
//* ---------------------------------------------
const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *mqtt_client_id = "senai134_esp_maduSantos";
const char *mqtt_topic_sub = "senai134/mesa02/espMadu/subs";
const char *mqtt_topic_pub = "senai134/mesa02/esppMadu/public";

static bool piscaLed = false;
static bool estadoLed = false;
unsigned long tempoPisca = 500; // Tempo de piscamento do LED, em milissegundos


void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  Boot.attach(0, INPUT_PULLUP);

  dht.begin();

  Serial.println(dht.readHumidity());
  Serial.println(dht.readTemperature());

  conectaWifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{
  Boot.update();
  checkWifi();

  bool atualizacao = false;
  bool estadoBotao = false;

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
    doc["temperatura"] = temperatura;
    doc["umidade"] = umidade;
    doc["timestamp"] = millis();

    // Criar string para armazenar o JSON
    String mensagem;
    serializeJson(doc, mensagem); 

    // Publica os dados
    client.publish(mqtt_topic_pub, mensagem.c_str());
    Serial.print("Publicado: ");
    Serial.println(mensagem);

    tempoAnterior = tempoAtual;
  }

  if (Boot.changed())
  {
    estadoBotao = !Boot.read(); 
    
    doc["estadoBotao"] = estadoBotao;

   
    String mensagemBotao;
    serializeJson(doc, mensagemBotao);

    client.publish(mqtt_topic_pub, mensagemBotao.c_str());
    Serial.print("Publicado: ");
    Serial.println(mensagemBotao);
  }

  static unsigned long tempoAnteriorPisca = 0;

  if (piscaLed == true)
  {
    if (tempoAtual - tempoAnteriorPisca > tempoPisca)
    {
      estadoLed = !estadoLed;
      tempoAnteriorPisca = tempoAtual;
    }
    digitalWrite(2, estadoLed);
  }
}



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
  DeserializationError erro = deserializeJson(doc, mensagem);

  if (erro)
  {
    Serial.printf("Erro %s no formato json", erro.f_str());
  }
  else
  {
    if (!doc["estadoLed"].isNull())
    {
      int acaoLed = doc["estadoLed"];

      switch (acaoLed)
      {
      case 0:
        estadoLed = false;
        piscaLed = false;
        break;

      case 1:
        estadoLed = true;
        piscaLed = false;
        break;

      case 2:
        piscaLed = true;
        break;

      default:
        Serial.print("opcao nao implementada");
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