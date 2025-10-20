#include <Arduino.h> // Biblioteca principal para programação em C++ no Arduino

//* --------- MAPEAMENTO DOS MOTORES ---------------
// Cada motor tem dois pinos (direita e esquerda) para controle de rotação (sentido horário/anti-horário)

#define pinM0dir 18
#define pinM0Esq 3
#define pinM1dir 10
#define pinM1Esq 46
#define pinM2dir 13
#define pinM2Esq 14
#define pinM3dir 12
#define pinM3Esq 11

//* --------- CONFIGURAÇÕES DE PWM ---------------
#define frequenciaPWM 20000  // Frequência de PWM (20 kHz) — evita ruído audível nos motores
#define resolucaoPWM 8       // Resolução de 8 bits → valores de 0 a 255
#define VELOCIDADE_PADRAO 30 // Velocidade base usada nas rampas (% de 0 a 100)
#define TEMPO_RAMPA 15       // Tempo (ms) entre cada passo de aceleração/desaceleração
#define PASSOS_RAMPA 20      // Número de passos da rampa — mais passos = movimento mais suave

// -------- MATRIZES DE PINOS E CANAIS ---------
// Estruturas para facilitar o controle de 4 motores com 2 pinos PWM cada

const uint8_t pinMotor[4][2] = {
    {pinM0Esq, pinM0dir},
    {pinM1Esq, pinM1dir},
    {pinM2Esq, pinM2dir},
    {pinM3Esq, pinM3dir}};

const uint8_t chMotor[4][2] = {
    {0, 1}, // Motor 0 usa canais 0 e 1
    {2, 3}, // Motor 1 usa canais 2 e 3
    {4, 5}, // Motor 2 usa canais 4 e 5
    {6, 7}  // Motor 3 usa canais 6 e 7
};

// -------- FUNÇÕES AUXILIARES --------

// Função para converter valor percentual (0–100%) em valor PWM (0–255)
uint8_t velocidade(uint8_t valor)
{
  return valor != 0
             ? map(valor, 0, 100, 150, 255) // Garante que motores não girem muito fraco (<150)
             : 0;
}

// Função para parar todos os motores
void parar()
{
  for (int i = 0; i < 4; i++)
  {
    ledcWrite(chMotor[i][0], 0);
    ledcWrite(chMotor[i][1], 0);
  }
}

// -------- MOVIMENTOS BÁSICOS --------

// Movimento para frente — todos motores giram no mesmo sentido
void frente(uint8_t vel)
{
  for (int i = 0; i < 4; i++)
  {
    ledcWrite(chMotor[i][1], velocidade(vel)); // Liga lado direito
    ledcWrite(chMotor[i][0], 0);               // Desliga lado esquerdo
  }
}

// Movimento para trás — inverte sentido de rotação
void tras(uint8_t vel)
{
  for (int i = 0; i < 4; i++)
  {
    ledcWrite(chMotor[i][0], velocidade(vel)); // Liga lado esquerdo
    ledcWrite(chMotor[i][1], 0);               // Desliga lado direito
  }
}

// Movimento lateral para a direita
void direita(uint8_t vel)
{
  // Cada motor combina direção diferente para gerar o movimento lateral
  ledcWrite(chMotor[0][1], velocidade(vel));
  ledcWrite(chMotor[0][0], 0);

  ledcWrite(chMotor[1][0], velocidade(vel));
  ledcWrite(chMotor[1][1], 0);

  ledcWrite(chMotor[2][0], velocidade(vel));
  ledcWrite(chMotor[2][1], 0);

  ledcWrite(chMotor[3][1], velocidade(vel));
  ledcWrite(chMotor[3][0], 0);
}

// Movimento lateral para a esquerda
void esquerda(uint8_t vel)
{
  ledcWrite(chMotor[0][0], velocidade(vel));
  ledcWrite(chMotor[0][1], 0);

  ledcWrite(chMotor[1][1], velocidade(vel));
  ledcWrite(chMotor[1][0], 0);

  ledcWrite(chMotor[2][1], velocidade(vel));
  ledcWrite(chMotor[2][0], 0);

  ledcWrite(chMotor[3][0], velocidade(vel));
  ledcWrite(chMotor[3][1], 0);
}

// -------- MOVIMENTOS DIAGONAIS --------

// Frente-direita → apenas motores M1 e M2 empurram
void diagonalFrenteDireita(uint8_t vel)
{
  ledcWrite(chMotor[0][1], 0);
  ledcWrite(chMotor[0][0], 0);

  ledcWrite(chMotor[1][1], velocidade(vel));
  ledcWrite(chMotor[1][0], 0);

  ledcWrite(chMotor[2][1], velocidade(vel));
  ledcWrite(chMotor[2][0], 0);

  ledcWrite(chMotor[3][1], 0);
  ledcWrite(chMotor[3][0], 0);
}

// Frente-esquerda → apenas motores M0 e M3 empurram
void diagonalFrenteEsquerda(uint8_t vel)
{
  ledcWrite(chMotor[0][1], velocidade(vel));
  ledcWrite(chMotor[0][0], 0);

  ledcWrite(chMotor[1][1], 0);
  ledcWrite(chMotor[1][0], 0);

  ledcWrite(chMotor[2][1], 0);
  ledcWrite(chMotor[2][0], 0);

  ledcWrite(chMotor[3][1], velocidade(vel));
  ledcWrite(chMotor[3][0], 0);
}

// Trás-direita → inverso da frente-esquerda
void diagonalTrasDireita(uint8_t vel)
{
  ledcWrite(chMotor[0][0], velocidade(vel));
  ledcWrite(chMotor[0][1], 0);

  ledcWrite(chMotor[1][0], 0);
  ledcWrite(chMotor[1][1], 0);

  ledcWrite(chMotor[2][0], 0);
  ledcWrite(chMotor[2][1], 0);

  ledcWrite(chMotor[3][0], velocidade(vel));
  ledcWrite(chMotor[3][1], 0);
}

// Trás-esquerda → inverso da frente-direita
void diagonalTrasEsquerda(uint8_t vel)
{
  ledcWrite(chMotor[0][0], 0);
  ledcWrite(chMotor[0][1], 0);

  ledcWrite(chMotor[1][0], velocidade(vel));
  ledcWrite(chMotor[1][1], 0);

  ledcWrite(chMotor[2][0], velocidade(vel));
  ledcWrite(chMotor[2][1], 0);

  ledcWrite(chMotor[3][0], 0);
  ledcWrite(chMotor[3][1], 0);
}

// -------- GIROS --------

// Gira o robô no sentido horário (direita)
void girarDireita(uint8_t vel)
{
  ledcWrite(chMotor[0][1], velocidade(vel));
  ledcWrite(chMotor[0][0], 0);

  ledcWrite(chMotor[1][0], velocidade(vel));
  ledcWrite(chMotor[1][1], 0);

  ledcWrite(chMotor[2][1], velocidade(vel));
  ledcWrite(chMotor[2][0], 0);

  ledcWrite(chMotor[3][0], velocidade(vel));
  ledcWrite(chMotor[3][1], 0);
}

// Gira o robô no sentido anti-horário (esquerda)
void girarEsquerda(uint8_t vel)
{
  ledcWrite(chMotor[0][0], velocidade(vel));
  ledcWrite(chMotor[0][1], 0);

  ledcWrite(chMotor[1][1], velocidade(vel));
  ledcWrite(chMotor[1][0], 0);

  ledcWrite(chMotor[2][0], velocidade(vel));
  ledcWrite(chMotor[2][1], 0);

  ledcWrite(chMotor[3][1], velocidade(vel));
  ledcWrite(chMotor[3][0], 0);
}

// -------- FUNÇÕES DE RAMPA --------
// Acelera progressivamente até a VELOCIDADE_PADRAO
void rampaAcelerar(void (*movimento)(uint8_t))
{
  for (int v = 0; v <= VELOCIDADE_PADRAO; v += (VELOCIDADE_PADRAO / PASSOS_RAMPA))
  {
    movimento(v); // Aplica o movimento com velocidade crescente
    delay(TEMPO_RAMPA);
  }
}

// Desacelera progressivamente até parar
void rampaDesacelerar(void (*movimento)(uint8_t))
{
  for (int v = VELOCIDADE_PADRAO; v >= 0; v -= (VELOCIDADE_PADRAO / PASSOS_RAMPA))
  {
    movimento(v);
    delay(TEMPO_RAMPA);
  }
  parar(); // Garante que todos motores parem
}

// -------- CONFIGURAÇÃO INICIAL --------
void setup()
{
  Serial.begin(9600); // Inicializa o monitor serial
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      pinMode(pinMotor[i][j], OUTPUT);                       // Define pinos como saída
      ledcSetup(chMotor[i][j], frequenciaPWM, resolucaoPWM); // Configura PWM para o canal
      ledcAttachPin(pinMotor[i][j], chMotor[i][j]);          // Liga canal PWM ao pino correspondente
    }
  }
  Serial.println("Carrinho inicializado!");
}

// -------- LOOP DE TESTE AUTOMÁTICO --------
// Executa cada tipo de movimento com aceleração e desaceleração
void loop()
{
  Serial.println("Frente");
  rampaAcelerar(frente);
  delay(3000);
  rampaDesacelerar(frente);
  delay(1000);

  Serial.println("Trás");
  rampaAcelerar(tras);
  delay(3000);
  rampaDesacelerar(tras);
  delay(1000);

  Serial.println("Diagonal Frente Direita");
  rampaAcelerar(diagonalFrenteDireita);
  delay(3000);
  rampaDesacelerar(diagonalFrenteDireita);
  delay(1000);

  Serial.println("Diagonal Frente Esquerda");
  rampaAcelerar(diagonalFrenteEsquerda);
  delay(3000);
  rampaDesacelerar(diagonalFrenteEsquerda);
  delay(1000);

  Serial.println("Diagonal Trás Direita");
  rampaAcelerar(diagonalTrasDireita);
  delay(3000);
  rampaDesacelerar(diagonalTrasDireita);
  delay(1000);

  Serial.println("Diagonal Trás Esquerda");
  rampaAcelerar(diagonalTrasEsquerda);
  delay(3000);
  rampaDesacelerar(diagonalTrasEsquerda);
  delay(1000);

  Serial.println("Girar Direita");
  rampaAcelerar(girarDireita);
  delay(3000);
  rampaDesacelerar(girarDireita);
  delay(1000);

  Serial.println("Girar Esquerda");
  rampaAcelerar(girarEsquerda);
  delay(3000);
  rampaDesacelerar(girarEsquerda);
  delay(1000);
}
