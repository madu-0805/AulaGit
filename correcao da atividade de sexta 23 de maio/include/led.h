#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led //criei uma  classe chamdo "LED"
{
private: // ATRIBUTUOS ()
    int pino;
    bool estadoLed;
    bool modoPiscar = false;
    unsigned long ultimaTroca = 0;
    unsigned long intervalo = 0;

public:// METODOS(ACOES)
    Led(int pin); // metodo construtor tem o nome da classe

    void ligar();
    void desligar();
    void inverter();

    void piscar(float frequencia);
    void update();
    int getPino();
    unsigned long getIntervalo();

};

#endif