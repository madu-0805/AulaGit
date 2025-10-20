#ifndef BOTAO_h
#define BOTAO_
#include <Arduino.h>
class Botao
{
private:
    uint8_t pino;
    bool estadoAtual = HIGH;
    bool estadoAnterior = HIGH;
    bool estadoConfirmado = HIGH;
    bool flagAltercao = false;
    bool flagPressionado= false;
    bool flagSolto= false;

    unsigned long tempoFiltro = 50;
    unsigned long tempoInicioEstado = HIGH;
    unsigned long tempoUltimaMudanca = 0;
    unsigned long duracaoestado = 0;

public:
    Botao(uint8_t p); // construtor
    void begin();
    void update();

    

    bool pressionado();
    bool solto();
    bool alteracaoEstado();
    unsigned long duracaoUltimoEstado();
    void configuraFiltro(unsigned long tempo);
};

#endif