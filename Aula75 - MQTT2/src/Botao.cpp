#include "Botao.h"

Botao::Botao(int pin)
{
    pino = pin;                  // Define o pino do botão
    pinMode(pino, INPUT_PULLUP); // Configura o pino
    estadoAnterior = false;      // Armazena o estado anterior da leitura
    ultimaMudanca = 0;           // Armazena o tempo da última mudança de estado
    estadoBotao = false;         // Estado atual do botão (pressionado ou não)
    intervalo = 50;              // Tempo para o debounce (50 milissegundos)
    Pressionado = false;         // evento  para detectar se foi pressionado
    Solto = false;               // evento para detectar se foi solto
}

/**
 * @brief Tratamento de ruido
 * Deve ser chamada periodicamente no loop
 */
void Botao::tratamento() // Lê o estado atual do botão (invertido, pois usamos INPUT_PULLUP)
{
    bool leituraAtual = digitalRead(pino) == LOW;

    if (leituraAtual != estadoAnterior) // Se o estado mudou desde a última leitura
    {
        ultimaMudanca = millis();      // Atualiza o tempo da última mudança
        estadoAnterior = leituraAtual; // Atualiza o tempo da última mudança
    }

    if ((millis() - ultimaMudanca) >= intervalo) // Se o tempo desde a última mudança for maior que o intervalo
    {
        if (leituraAtual != estadoBotao) // Se o estado estabilizado mudou
        {
            estadoBotao = leituraAtual; // Atualiza o estado atual

            if (estadoBotao)
            {
                Pressionado = true; // Marca como pressionado
            }
            else
            {
                Solto = true; // Marca como solto
            }
        }
    }
}

bool Botao::pressionado() // Retorna true apenas uma vez quando o botão é pressionado
{
    if (Pressionado)
    {
        Pressionado = false; // Reseta a flag após a leitura

        return true;
    }
    return false;
}

bool Botao::solto() // Retorna o estado atual do botão
{
    if (Solto)
    {
        Solto = false;
        return true;
    }
    return false;
}

bool Botao::pressionando() // Altera o tempo de debounce
{
    return estadoBotao;
}

void Botao::setIntervalo(unsigned long intervaloNovo) // Altera o tempo de debounce
{
    intervalo = intervaloNovo;
}

unsigned long Botao::getIntervalo() // Retorna o tempo atual de debounce
{
    return intervalo;
}