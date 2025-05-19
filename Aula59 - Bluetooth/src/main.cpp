/*Maria Eduarda Santos
14/04/25
aula continuacao de sexta feira*/

#include <Arduino.h>
#define pinLed 2
void setup()
{
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
}

void loop()
{
  //  Declara variáveis estáticas para manter o estado entre as iterações do loop

  static bool estadoLed = false; // Estado do LED (ligado ou desligado)
  static bool pisca = false;     // Define se o LED deve piscar ou não
  static bool pisca  = false;     // Define se o LED deve piscar ou não
  static int velocidade = 200;   // Velocidade do pisca-pisca (inicialmente 200ms)

  // Verifica se há dados disponíveis na porta serial
  if (Serial.available())
  {
    String texto = Serial.readStringUntil('\n');  // Lê a entrada serial até encontrar uma quebra de linha ('\n')
    Serial.printf("Voce digitou: %s\n\r", texto); // Imprime o texto recebido na serial para o usuário
    texto.trim();                                 // Remove espaços em branco no início e no final da string
    texto.toLowerCase();                          // Converte a string para minúsculas para facilitar a comparação

    if (texto.equals("liga")) // Compara os comandos recebidos e altera o estado do LED e do pisca-pisca
    {
      // Liga o LED e desativa o pisca-pisca
      estadoLed = true;
      pisca = false;
    }

    else if (texto.equals("desliga")) // Desliga o LED e desativa o pisca-pisca
    {
      estadoLed = false;
      pisca = false;
    }

    else if (texto.equals("pisca")) // Ativa o pisca-pisca
    {
      pisca = true;
    }

    else if (texto.equals("mais devagar")) // Diminui a velocidade do pisca-pisca
    {
      pisca = true;
      velocidade -= 100; // Diminuindo o tempo de espera, fazendo o LED piscar mais devagar
    }

    else if (texto.equals("mais devagar")) // Aumenta a velocidade do pisca-pisca
    {
      pisca = true;
      velocidade += 100; // Aumentando o tempo de espera, fazendo o LED piscar mais rápido
    }

    else if (texto.startsWith("velocidade = ")) //   Extraí o valor da velocidade da string
    {
      int tamanho = texto.length();
      String extracao = texto.substring(13, tamanho);
      int valor = extracao.toInt(); // Converte o valor extraído para um número inteiro

      if (valor >= 0 && valor <= 100) //  Se o valor estiver entre 0 e 100, ajusta a velocidade
      {
        velocidade = map(valor, 0, 100, 1000, 50); // Mapeia o valor para um intervalo de 50ms a 1000ms
      }
      else
      {
        Serial.println("valores aceitos somente entre 0 e 100"); // Se o valor estiver fora do intervalo, avisa o usuário
      }
    }
    else
    {
      Serial.println("comando nao encontrado"); // Se o comando não for reconhecido, informa ao usuário
    }
  }
  if (pisca == true) // Se o LED deve piscar
  {
    unsigned long tempoAtual = millis();
    static unsigned long tempoInicial = 0; // Marca o tempo do último piscar

    if (tempoAtual - tempoInicial >= velocidade) // Se o tempo passado desde o último piscar for maior ou igual à velocidade definida
    {
      estadoLed = !estadoLed;    // Altera o estado do LED (liga ou desliga)
      tempoInicial = tempoAtual; // Atualiza o tempo inicial para o novo ciclo de piscar
    }
  }
  digitalWrite(pinLed, estadoLed);
}
