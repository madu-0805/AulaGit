#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <Arduino.h>

class Temporizador
{
private:
    unsigned long tempo_ms = 1000;
    unsigned long inicio;
    unsigned long UltimoTempo;
    bool ativo;

    unsigned long intervalo;

public:
    Temporizador(unsigned long tempo_ms = 1000);
    void iniciar();
    void parar();
    void reiniciar();
    void definirIntervalo(unsigned long tempo_ms);

    bool estaAtivo();
    bool estaPronto();
};

#endif