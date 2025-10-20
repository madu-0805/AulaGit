
#include <Arduino.h>

#define enM2A 7
#define enM2B 15

const int8_t tabelaTransicao[4][4] = {
    {0, 1, -1, 0},
    {-1, 0, 0, 1},
    {1, 0, 0, -1},
    {0, -1, 1, 0}
    // VALOR ATUAL

};

#define pinMotor0 14

void setup()
{
    Serial.begin(9600);
    pinMode(48, INPUT);
    pinMode(47, INPUT);
}

void loop()
{

    bool estadoAtualA = gpio_get_level((gpio_num_t)48);
    bool estadoAtualB = gpio_get_level((gpio_num_t)47);

    int estadoAtualEncoder = ((estadoAtualA << 1) | estadoAtualB);

    static int estadoAnteriorEncoder = 3;
    static int contador = 0;
    static int acumuladorMovimento = 0;

    if (estadoAtualEncoder != estadoAnteriorEncoder)
    {
        acumuladorMovimento += tabelaTransicao[estadoAtualEncoder][estadoAnteriorEncoder];
        estadoAnteriorEncoder = estadoAtualEncoder;
        Serial.println(acumuladorMovimento);
    }
}