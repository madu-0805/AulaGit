#include "temporizador.h"
#include <Arduino.h>
/**
 *
 */
Temporizador::Temporizador(unsigned long tempo_ms)
{
    intervalo = tempo_ms;
    inicio = 0;
    ativo = false;
}
/**
 * @brief Inicia o temporizador.
 *
 */
void Temporizador::iniciar()
{
    UltimoTempo = millis();
    Serial.println("temporizador iniciado com sucesso");
    ativo = true;
}
/**
 *@brief Para o temporizador.
 */
void Temporizador::parar()
{
    ativo = false;
}
/**
 *@brief  Reinicia o contador a partir de millis().
 */
void Temporizador::reiniciar()
{
    inicio = millis();
    UltimoTempo = millis();
}
/**
 *@brief Retorna true se estiver ativo.
 */
bool Temporizador::estaAtivo()
{
    return ativo = true;
}
/**
 * @brief Retorna true se o intervalo tiver passado desde o inicia
 */
bool Temporizador::estaPronto()
{
    if (!ativo)
        return false;
    return (millis() - inicio >= intervalo);
}
void Temporizador ::definirIntervalo(unsigned long tempo_ms)
{
intervalo = tempo_ms;
}