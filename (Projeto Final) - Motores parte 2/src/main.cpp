#include <Arduino.h>

#define pinM0Dir 14
#define pinM0Esq 13
#define pinM1Dir 10
#define pinM1Esq 46
#define pinM2Dir 3
#define pinM2Esq 18
#define pinM3Dir 12
#define pinM3Esq 11

#define frequenciaPWM 20000
#define resolucaoPWM 8

const uint8_t pinMotor[4][2] = {
  {pinM0Esq, pinM0Dir},
  {pinM1Esq, pinM1Dir},
  {pinM2Esq, pinM2Dir},
  {pinM3Esq, pinM3Dir}
};
  
const uint8_t chMotor [4][2] = 
{
  {0,1},
  {2,3},
  {4,5},
  {6,7}
};


uint8_t velocidade (uint8_t);

void setup() 
{
  Serial.begin(9600);
  for(int i = 0; i < 4; i++)
   for(char j = 0; j < 2; j++)
  {
   pinMode(pinMotor[i][j], OUTPUT);
   ledcSetup(chMotor[i][j], frequenciaPWM, resolucaoPWM);
   ledcAttachPin(pinMotor[i][j], chMotor[i][j]);
  }
}

void loop() 
{
 for(char i = 0; i <= 100; i++)
 {
  ledcWrite(chMotor[0][0], velocidade(i));
  ledcWrite(chMotor[1][0], velocidade(i));
  ledcWrite(chMotor[2][0], velocidade(i));
  ledcWrite(chMotor[3][0], velocidade(i));
  delay(10);
 }
}


uint8_t velocidade (uint8_t valor)
{
  return valor != 0  
  ? map(valor, 0, 100, 150, 255)
  : 0;
}