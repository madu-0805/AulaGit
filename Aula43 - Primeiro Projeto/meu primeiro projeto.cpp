#include <Arduino.h>
/**meu primeiro projeto
 * Maria Eduarda
 * */

#define pinLed 2
#define pinButton 19
unsigned long tempoIncial = 0;
bool estadoLed = 0;
int estadoAnterior = 1;
bool estadoBotao = 0;

void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  bool estadoAtualBotao = digitalRead(pinButton);
  static bool estadoAnteriorBotao = 1;
  static bool ultimaAcao = 1;

  static unsigned long tempoUltimaAlteracao = 0;
  unsigned long tempoAtual = millis();
  const unsigned long tempoFiltro = 50;

  static int contagem = 0;

  //! INICIA O TRATAMENTO DE RUIDO DO BOTAO

  //* detecta  mudanca no estado do botao
  if (estadoAtualBotao != estadoAnteriorBotao)
  {
    tempoUltimaAlteracao = tempoAtual; //* atualiza o tempo da ultima mudanca
  }

  //* verifica se o novo estado se mantever estavel por tempo suficiente
  if ((tempoAtual - tempoUltimaAlteracao) > tempoFiltro)
  {
    //* Verifica se ainda nao processamos essa nova acao
    if (estadoAtualBotao != ultimaAcao)
    {
      ultimaAcao = estadoAtualBotao; //* atualizar o estado ja processado para etivar acoes repetidas

      //*Se o botao foi pressionado (nivel logico LOW)

      if (!estadoAtualBotao)
      {
        contagem++;
        Serial.println(contagem);
      }
      //* Se o botao foi solto (nivel logico HIGH), nenhuma acao por enquanto

      else
      {
      }
    }
  }
  //* ATUALIZA O ESTADO ANTERIOR PARA A PROXIMA LITERACAO
  estadoAnteriorBotao = estadoAtualBotao;
}