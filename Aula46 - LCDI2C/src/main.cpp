/**
ATIVIDADE : INICIA O TRATAMENTO DE RUIDO DO BOTAO
MARIA EDUARDA SILVA


*/
#include <Arduino.h>




#define pinLed 2
#define pinButton 21
unsigned long tempoIncial = 0;
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

  static unsigned long tempoUltimaAltercao = 0;
  unsigned long tempoAtual = millis();
  const unsigned long tempoFiltro = 50;

  static bool estadoLed = 0;
  //! INICIA O TRATAMENTO DE RUIDO DO BOTAO

  //* detecta  mudanca no estado do botao
  if (estadoAtualBotao != estadoAnteriorBotao)
  {
    tempoUltimaAltercao = tempoAtual; //* atualiza o tempo da ultima mudanca
  }

  //* verifica se o novo estado se mantever estavel por tempo suficiente
  if ((tempoAtual - tempoUltimaAltercao) > ultimaAcao)
  {
    //* Verifica se ainda nao processamos essa nova acao
    if (estadoAtualBotao != ultimaAcao)
    {
      ultimaAcao = estadoAtualBotao; //* atualizar o estado ja processado para etivar acoes repetidas

      //*Se o botao foi pressionado (nivel logico LOW)

      if (!estadoAtualBotao)
      {
        estadoLed = !estadoLed;
        digitalWrite(pinLed, estadoLed);
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
