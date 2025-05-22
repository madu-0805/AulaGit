#ifndef BOTAO_H
#define BOTAO_H

#include <Arduino.h>

class Botao {
  private:
    int pino;
    bool estadoAnterior;        // Estado anterior 
    bool estadoBotao;            // Estado atual do botão
    bool Pressionado;          // pressionado
    bool Solto;                //  solto
    unsigned long ultimaMudanca; // Tempo da última
    unsigned long intervalo; // Intervalo  em milissegundos
    

  public:
    Botao(int pino);
    void setIntervalo(unsigned long intervaloNovo);
    void tratamento();
    bool pressionado();   // Está pressionado?
    bool solto();         // Está solto?
    bool mudanca();         // Houve mudança de estado?
    bool pressionando();
    unsigned long getIntervalo();
};
#endif