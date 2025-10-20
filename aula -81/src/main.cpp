/*
Madu Santos
23/05/25
Classe temporizador
*/
#include <PubSubClient.h>
#include <WiFi.h>
#include "Temporizador.h"
#include "Internet.h"


WiFiClient espClient;
PubSubClient client(espClient);
Temporizador tempo(1000);

const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *mqtt_client_id = "senai134_esp_maduSantos";
const char *mqtt_topic_sub = "senai134/mesa03/espMadu/subs";
const char *mqtt_topic_pub = "senai134/mesa03/esppMadu/public";

void setup()
{
    Serial.begin(9600);
    conectaWifi();
    tempo.iniciar();
}

void loop()
{
    checkWifi();
    client.loop();

    if (tempo.estaPronto())
    {
        client.publish(mqtt_topic_pub, "Mensagem enviada!");
        Serial.print("Mensagem enviada!");
        Serial.println(tempo.estaPronto());
        tempo.reiniciar();
    }
}
