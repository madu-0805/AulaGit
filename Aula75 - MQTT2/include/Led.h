#ifndef LED_H
#define LED_H// Garante que esse arquivo só seja carregado uma vez


#include <Arduino.h>

class Led //criei uma  classe chamdo "LED" e uma descricao de um objeto
{
private: // ATRIBUTUOS (caracteristicas)  isso ninguem precisa saber // Parte privada: só a própria classe pode usar
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
    int getPino();// atributuos
    unsigned long getIntervalo();

};

#endif