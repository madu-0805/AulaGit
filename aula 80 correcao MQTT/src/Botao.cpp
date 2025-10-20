#include "Botao.h"
/**
 * @brief Construtor da classe botao
 *
 *@param p Numero do pino digital ao qual o botao esta concetado
 */
Botao::Botao(uint8_t p) : pino(p) {}

/**
 * @brief Inicializa o botao
 *
 * Configura o pino como entrada. O modo pull up padrao
 *
 */
void Botao::begin()
{
    pinMode(pino, INPUT_PULLUP);
    estadoAtual = digitalRead(pino);
    estadoAnterior = estadoAtual;
    estadoConfirmado = estadoAtual;
    tempoInicioEstado = millis();
}
/**
 * @brief Define o tempo de filtro (debounce) para estabilitar as leituras do botao
 * @param tempo Tempo de debounce em milissegundos
 */
void Botao::configuraFiltro(unsigned long tempo)
{
    tempoFiltro = tempo;
}
/**
 * @brief atualiza o estado interno do botao
 * Deve ser chamada frequqntimente dentro do loop principal
 * Detecta mudanca de estado e aciona ad flags internas de eventos
 * (pressionado,solto,mudanca de estado)
 */
void Botao::update()
{
    unsigned long agora = millis();
    estadoAtual = digitalRead(pino);
    flagAltercao = false;
    flagPressionado = false;
    flagSolto = false;

    if (estadoAtual != estadoAnterior)
        tempoUltimaMudanca = agora;
    if ((agora - tempoUltimaMudanca) > tempoFiltro)
    {
        if (estadoAtual != estadoConfirmado)
        {
            estadoConfirmado = estadoAtual;
            duracaoestado = agora - tempoInicioEstado;
            tempoInicioEstado = agora;
            flagAltercao = true;
            if (estadoAtual) //*Botao pressionado
            {
                flagPressionado = true;
            }
            else //* botao solto
            {
                flagSolto = true;
            }
        }
    }
    estadoAnterior = estadoAtual;
}
/**
 * @brief verifica se o botao acabou de ser pressionado
 *
 * @return true se houver uma transicao para o estado pressionado
 *  na ultima atualicao
 */
bool Botao::pressionado()
{
    return flagPressionado;
}
/**
 * @brief verifica se o botoa acabou de ser solto
 *
 * @return true se houve uma transicao para o estado solto na
 * ultima atualizacao
 */
bool Botao::solto()

{
    return flagSolto;
}
/**
 * @brief Verifica se houve uma mundanca de estado do botao
 *
 * @return true se o estado do botao mudou (pressiondo ou solto)
 * na ultima atualizaco
 */
bool Botao::alteracaoEstado()
{
    return flagPressionado;
}
/**
 * @brief retorna a duracao do ultimo estado(pressionado ou solto)
 * 
 * @return tempo em millissegundos que o botao permanceu no ultimo estado
 * 
 */
unsigned long Botao::duracaoUltimoEstado()
{
    return duracaoestado;
}