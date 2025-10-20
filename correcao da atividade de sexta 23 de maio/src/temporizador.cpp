#include "temporizador.h"

Temporizador::Temporizador(unsigned long tempo_ms)
{
    intervalo = tempo_ms;
    ativo = false;
}
void Temporizador::iniciar()
{
    inicio = millis();
    ativo = true;
}
void Temporizador::parar()
{
    ativo = false;
}

bool Temporizador::estaPronto()
{
    return ativo && (millis() - inicio >= intervalo);
}
void Temporizador ::reiniciar()
{
    inicio = millis();
    ativo= true;

}

bool Temporizador::estaAtivo()
{
return ativo;
}
void Temporizador::definirIntervalo(unsigned long tempo_ms)
{
    intervalo = tempo_ms;
}