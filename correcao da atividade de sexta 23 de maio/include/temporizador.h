#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <Arduino.h>

class Temporizador

{

private:
unsigned long inicio;
unsigned long intervalo;
bool ativo;





public:
    Temporizador(unsigned long tempo_ms);
    void iniciar();
    void parar();
    bool estaPronto();
    void reiniciar();
 bool estaAtivo();
    void definirIntervalo(unsigned long tempo_ms);
};

#endif
