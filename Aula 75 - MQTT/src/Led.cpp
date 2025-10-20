#include "Led.h"


Led ::Led(int pin)
{
    pino = pin;
    estadoLed = false;
    pinMode(pino, OUTPUT);
    digitalWrite(pino, LOW);
}

/**
 * @brief Liga o Led
 */
void Led::ligar()
{
    estadoLed = true;
    modoPiscar = false;
    digitalWrite(pino, HIGH);
}
/**
 * @brief Desligar o led
 */
void Led::desligar()
{
    estadoLed = false;
    modoPiscar = false;
    digitalWrite(pino, LOW);
}
/**
 * @brief inverter o estado do led
 */
void Led::inverter()
{
    estadoLed = !estadoLed;
    digitalWrite(pino, estadoLed);
}
/**
 * @brief piscar o Led
 * @param frequencia frequencia em Hz que o led devera piscar
 */
void Led::piscar(float frequencia)// Faz o LED piscar com uma frequência (Hz)
{
    if (frequencia == 0)
        return;
    intervalo = 1000.0 / (frequencia * 2); // ou seja 1000/4 que e igual 250
    ultimaTroca = millis();
    modoPiscar = true;
}
/**
 * 
 @brief funcao que atualiza o estado do led no moodo piscar
 */
void Led::update()
{
    if (!modoPiscar)
        return;
    unsigned long agora = millis();
    if (agora - ultimaTroca >= intervalo)
    {
        inverter();
        ultimaTroca = agora;
    }
}

int Led::getPino()
{
    return pino;
}

unsigned long  Led:: getIntervalo()
{
    return intervalo;
}