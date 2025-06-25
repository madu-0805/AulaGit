#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include "Internet.h"
#include "certificados.h"

const int mqtt_port = 8883;
const char *mqtt_id = "idDoEsp32";
const char *mqtt_SUB = "senai134/comandos";
const char *mqtt_PUB = "senai134/sensores";

WiFiClientSecure espClient;
PubSubClient mqtt(espClient);

void Callback(char *topic, byte *payload, unsigned int length);
void conectaMQTT();

void setup()
{
    Serial.begin(9600);
    conectaWifi();

    espClient.setCACert(AWS_ROOT_CA);
    espClient.setCertificate(AWS_CERT);
    espClient.setPrivateKey(AWS_KEY);

    mqtt.setServer(AWS_BROKER, mqtt_port);
    mqtt.setCallback(Callback);
}

void loop()
{
    checkWifi();
    if (!mqtt.connected())
    {
        conectaMQTT();
    }
    mqtt.loop();

    static unsigned long tempo_pub = 0;
    unsigned long agora = millis();

    if (agora - tempo_pub > 2000)
    {
        JsonDocument doc;

        doc["msg"] = "ooiee";

        String mensagem;
        serializeJson(doc, mensagem);
        mqtt.publish(mqtt_PUB, mensagem.c_str());
        tempo_pub = agora;
    }
}
void Callback(char *topic, byte *payload, unsigned int length)
{
    String msg((char *)payload, length);
    Serial.printf("Mensagem recebida (topico:[%s]):%s \n\r", topic, msg.c_str());
}
void conectaMQTT()
{
    while (!mqtt.connected())
    {
        Serial.print("Conectando ao AWS IoT Core ...");
        if (mqtt.connect(mqtt_id))
        {
            Serial.println("conectado.");
            mqtt.subscribe(mqtt_SUB);
        }
        else
        {
            Serial.printf("falhou(%d).Tentando novamente em 5s \n\r", mqtt.state());
            delay(5000);
        }
    }
}