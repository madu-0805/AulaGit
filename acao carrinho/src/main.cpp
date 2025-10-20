#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

void temperaturaMotores();


//* ===========================================================
//*                 CONFIGURAÇÕES DOS MOTORES
//* ===========================================================

//* Pinos dos motores (cada motor tem 2 pinos: direita e esquerda)
#define pinM0dir 14
#define pinM0Esq 13

#define pinM1dir 10
#define pinM1Esq 46

#define pinM2dir 3
#define pinM2Esq 18

#define pinM3dir 12
#define pinM3Esq 11

Adafruit_ADS1115 ads;

//* Configuração do PWM
#define frequenciaPWM 20000 //* 20 kHz — alta frequência, evita ruído nos motores
#define resolucaoPWM 8      //* 8 bits (valores de 0 a 255)

//* Mapeamento dos pinos dos motores: [motor][0=Esq,1=Dir]
const uint8_t pinMotor[4][2] = {
    {pinM0Esq, pinM0dir},
    {pinM1Esq, pinM1dir},
    {pinM2Esq, pinM2dir},
    {pinM3Esq, pinM3dir}};

//* Canais PWM correspondentes para cada pino
const uint8_t chMotor[4][2] = {
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7}};

//* Parâmetros de controle
const uint8_t velocidadeMax = 200; //* Velocidade máxima (ajustável)
const uint8_t incremento = 5;      //* Passo de incremento da rampa
const int tempoRampa = 20;         //* Intervalo entre passos da rampa (ms)
const int tempoMovimento = 10000;  //* Tempo de movimento (10 segundos)

//*===========================================================
//*                 DECLARAÇÃO DE FUNÇÕES
//* ===========================================================

void parar();
void rampaAcelera(const uint8_t motor[][2], const uint8_t canal[][2], int dir[4]);
void rampaDesacelera(const uint8_t motor[][2], const uint8_t canal[][2], int dir[4]);

//* Movimentos básicos
void frente();
void tras();
void direita();
void esquerda();
void girarEixo();

//* Movimentos diagonais
void diagonalFrenteDireita();
void diagonalFrenteEsquerda();
void diagonalTrasDireita();
void diagonalTrasEsquerda();

//* ===========================================================
//*                 FUNÇÃO DE AJUSTE DE VELOCIDADE
//*===========================================================

//* Retorna o valor mapeado da velocidade (garante mínimo de força ao motor)
uint8_t velocidade(uint8_t valor)
{
  return valor != 0 ? map(valor, 0, 255, 150, 255) : 0;
}

//* ===========================================================
//*                         SETUP
//* ===========================================================

void setup()
{
  Serial.begin(9600);

  //*Configuração dos pinos e canais PWM
  for (char i = 0; i < 4; i++)
  {
    for (char j = 0; j < 2; j++)
    {
      pinMode(pinMotor[i][j], OUTPUT);
      ledcSetup(chMotor[i][j], frequenciaPWM, resolucaoPWM);
      ledcAttachPin(pinMotor[i][j], chMotor[i][j]);
    }
  }

  Serial.println("Iniciando sequência de movimentos...");

  //*Sequência de testes de movimento
  frente();
  tras();
  direita();
  esquerda();
  girarEixo();
  diagonalFrenteDireita();
  diagonalFrenteEsquerda();
  diagonalTrasDireita();
  diagonalTrasEsquerda();

  parar();
  Serial.println("Sequência finalizada!");
}

//* ===========================================================
//**                            LOOP
//* ===========================================================

void loop()
{
  //* Vazio — os movimentos são executados apenas uma vez no setup()
}

//*===========================================================
//*                   FUNÇÕES AUXILIARES DE CONTROLE
//* ===========================================================

//* Aplica a direção de rotação para cada motor:
//* 1 = frente, -1 = ré, 0 = parado
void aplicarDirecao(int dir[4])
{
  for (int i = 0; i < 4; i++)
  {
    if (dir[i] == 1)
    { //* Frente
      ledcWrite(chMotor[i][0], 0);
      ledcWrite(chMotor[i][1], velocidadeMax);
    }
    else if (dir[i] == -1)
    { //* Ré
      ledcWrite(chMotor[i][0], velocidadeMax);
      ledcWrite(chMotor[i][1], 0);
    }
    else
    { //* Parado
      ledcWrite(chMotor[i][0], 0);
      ledcWrite(chMotor[i][1], 0);
    }
  }
}

//* Aceleração progressiva (rampa de subida)
void rampaAcelera(const uint8_t motor[][2], const uint8_t canal[][2], int dir[4])
{
  for (int v = 0; v <= velocidadeMax; v += incremento)
  {
    for (int i = 0; i < 4; i++)
    {
      if (dir[i] == 1)
      {
        ledcWrite(canal[i][0], 0);
        ledcWrite(canal[i][1], v);
      }
      else if (dir[i] == -1)
      {
        ledcWrite(canal[i][0], v);
        ledcWrite(canal[i][1], 0);
      }
      else
      {
        ledcWrite(canal[i][0], 0);
        ledcWrite(canal[i][1], 0);
      }
    }
    delay(tempoRampa);
  }
}

//* Desaceleração progressiva (rampa de descida)
void rampaDesacelera(const uint8_t motor[][2], const uint8_t canal[][2], int dir[4])
{
  for (int v = velocidadeMax; v >= 0; v -= incremento)
  {
    for (int i = 0; i < 4; i++)
    {
      if (dir[i] == 1)
      {
        ledcWrite(canal[i][0], 0);
        ledcWrite(canal[i][1], v);
      }
      else if (dir[i] == -1)
      {
        ledcWrite(canal[i][0], v);
        ledcWrite(canal[i][1], 0);
      }
      else
      {
        ledcWrite(canal[i][0], 0);
        ledcWrite(canal[i][1], 0);
      }
    }
    delay(tempoRampa);
  }
}

//* ===========================================================
//*                      FUNÇÕES DE MOVIMENTO
//*===========================================================

//* ---- Movimentos básicos ----
void frente()
{
  Serial.println("Frente");
  int dir[4] = {1, 1, 1, 1};
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

void tras()
{
  Serial.println("Trás");
  int dir[4] = {-1, -1, -1, -1};
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

void direita()
{
  Serial.println("Direita");
  int dir[4] = {1, -1, -1, 1};
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

void esquerda()
{
  Serial.println("Esquerda");
  int dir[4] = {-1, 1, 1, -1};
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

void girarEixo()
{
  Serial.println("Girar no próprio eixo");
  int dir[4] = {1, -1, 1, -1};
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

//*---- Movimentos diagonais ----
void diagonalFrenteDireita()
{
  Serial.println("Diagonal Frente Direita");
  int dir[4] = {0, 1, 1, 0};
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

void diagonalFrenteEsquerda()
{
  Serial.println("Diagonal Frente Esquerda");
  int dir[4] = {1, 0, 0, 1};
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

void diagonalTrasDireita()
{
  Serial.println("Diagonal Trás Direita");
  int dir[4] = {1, 0, 0, 1}; //* ⚠️ (mesma direção da frente esq, pode revisar conforme montagem)
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

void diagonalTrasEsquerda()
{
  Serial.println("Diagonal Trás Esquerda");
  int dir[4] = {0, -1, -1, 0};
  rampaAcelera(pinMotor, chMotor, dir);
  delay(tempoMovimento);
  rampaDesacelera(pinMotor, chMotor, dir);
}

//*---- Parar ----
void parar()
{
  Serial.println("Parar");
  int dir[4] = {0, 0, 0, 0};
  aplicarDirecao(dir);
}

void temperaturaMotores() 
{
  int leitura = ads.readADC_SingleEnded(0);// de 0 ate 3 
float tempC = leitura * 0.01875; // converter em temperatura de LM35

Serial.printf("Temperatura: %.2f °C \n, tempC");// %.2f 4 um float com 2 casa decimais 
delay(1000);
}