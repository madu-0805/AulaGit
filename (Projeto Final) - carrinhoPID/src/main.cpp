#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

#define pinM0Dir 18
#define pinM0Esq 3

#define pinM1Dir 10
#define pinM1Esq 46

#define pinM2Dir 13
#define pinM2Esq 14

#define pinM3Dir 12
#define pinM3Esq 11

#define I2C_SDA 8
#define I2C_SCL 9

#define erroLinha INT16_MAX
#define frequenciaPWM 20000
#define resolucaoPWM 8
#define pinSeguidorHabilitado 8

Adafruit_MCP23X17 mcp;

void iniciarSeguidorLinha();
void acionaOmini(float vx, float vy, float omega);
void confMotores();
void acionaMotor();
void acionaRodasOmini(float vx, float vy, float omega);
void pararTodosMotores();
float atualizarPID(float erro, float dt);
float calcularErroLinha(uint8_t mascara);
uint8_t lerSeguidorLinha();
uint8_t porcentagemPWM(uint8_t velocidade);

const uint8_t pinMotor[4][2] = {
    {pinM0Esq, pinM0Dir},
    {pinM1Esq, pinM1Dir},
    {pinM2Esq, pinM2Dir},
    {pinM3Esq, pinM3Dir}};

const uint8_t pinSeguidor[8] = {0, 1, 2, 3, 4, 5, 6, 7};

const uint8_t chMotor[4][2] =
    {
        {0, 1},
        {2, 3},
        {4, 5},
        {6, 7}};
// VARIAVIES PID
float kp = 4.0f;
float ki = 0.5f;
float kd = 1.2f;

float velocidadeFrente = 20.0f;
float omegaMax = 40.0f;

float errooAnterior = 0.0f;
float integraAcumulada = 0.0f;
uint32_t instateAnteriorMs = 0;

void setup()
{
  Serial.begin(115200);
  iniciarSeguidorLinha();
  confMotores();
}

void loop()
{

  uint32_t agoraMs = millis();
  float dt = (agoraMs - instateAnteriorMs) / 100.0f;
  instateAnteriorMs = agoraMs;
  uint8_t mascara = lerSeguidorLinha();
  int erro = calcularErroLinha(mascara);

  if (erro == erroLinha)
  {
    acionaRodasOmini(0.0f, 10.0f, errooAnterior > 0 ? 12.0f : -12.0f);
    return;
  }
  float omega = atualizarPID((float)erro, dt);
  acionaRodasOmini(0.0f, velocidadeFrente, omega);
}
void iniciarSeguidorLinha()
{
  for (char i = 0; i <= 7; i++)
    mcp.pinMode(pinSeguidor[i], INPUT);
  mcp.pinMode(pinSeguidorHabilitado, OUTPUT);
  mcp.digitalWrite(pinSeguidorHabilitado, HIGH);
}
void confMotores()
{
  for (char i = 0; i < 4; i++)   // 4 motores
    for (char j = 0; j < 2; j++) // Cada um com 2 pinos
    {
      pinMode(pinMotor[i][j], OUTPUT);
      ledcSetup(chMotor[i][j], frequenciaPWM, resolucaoPWM); // Configura canal PWM
      ledcAttachPin(pinMotor[i][j], chMotor[i][j]);
      ledcWrite(chMotor[i][j], 0);
    }
}

uint8_t lerSeguidorLinha()
{
  uint8_t gpa = mcp.readGPIOA(); // Lê os 8 bits do registrador GPIOA (sensores de linha)
  return gpa;
}
float calcularErroLinha(uint8_t mascara)
{
  if (mascara == 0)
    return erroLinha;
  const int pesos[8] = {-7, -5, -3, -1, 1, 3, 5, 7};
  int somaPesos = 0;
  int contarLinhas = 0;

  for (char i = 0; i < 8; i++)
  {
    if (mascara & (1 << i))
    {

      somaPesos += pesos[i];
      contarLinhas++;
      return (float)somaPesos / contarLinhas;
    }
  }
}
uint8_t porcentagemPWM(uint8_t velocidade)
{
  return velocidade != 0
             ? map(velocidade, 1, 100, 150, 255)
             : 0;
}
void acionaMotor(int indiceMotor, int velocidadePercentual)
{
  uint8_t dutyCicle = porcentagemPWM(velocidadePercentual);
  if (velocidadePercentual >= 0)
  {
    ledcWrite(chMotor[indiceMotor][0], dutyCicle);
    ledcWrite(chMotor[indiceMotor][1], dutyCicle);
  }
}
void acionaRodasOmini(float vx, float vy, float omega)
{
  float v[4];
  v[0] = vy + vx + omega;
  v[1] = vy - vx - omega;
  v[2] = vy - vx + omega;
  v[3] = vy + vx - omega;
  // fabs e o modulo de um float-> valor negativo vira positivo
  // max retorna o maior entre dois numeros

  float maiorVelocidade = max(max(fabs(v[0]), fabs(v[1])), max(fabs(v[2]), fabs(v[3])));

  if (maiorVelocidade > 100.0f)
    for (int i = 0; i < 4; i++)
      v[i] = (v[i] / maiorVelocidade) * 100.0f;

  for (int i = 0; i < 4; i++)
    acionaMotor(i, (int)roundf(v[i]));
}
void pararTodosMotores()
{
  for (char i = 0; i < 4; i++)
  {
    ledcWrite(chMotor[i][0], 0);
    ledcWrite(chMotor[i][1], 0);
  }
}
float atualizarPID(float erro, float dt)
{
  integraAcumulada += erro * dt;
  const float limiteIntegral = 100.0f / max(0.001f, ki);

  integraAcumulada = constrain(integraAcumulada, -limiteIntegral, limiteIntegral);

  float derivada = (erro - errooAnterior) / max(dt, 0.001f);
  errooAnterior = erro;

  float omega = kp * erro + ki * integraAcumulada + kd * derivada;
  omega = constrain(omega, -omegaMax, omegaMax);
  return omega;
}