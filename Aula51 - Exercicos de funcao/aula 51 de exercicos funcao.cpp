#include <Arduino.h>
/*Maria Eduarda Silva
ATIVIDADE : pitagoras E Celsius e Fahrenheit
03/04/25
*/

float pitagoras(float, float);
float celsius(float graus);
float medidas(float milimetros);
float tamanho(float polegadas);
float televisao(float altura);
float visor(float polegadas);

void setup()
{

  // float hipotenusa = pitagoras(3, 4);
  // Serial.println(hipotenusa);
  Serial.begin(9600);
  float temperatura = celsius(50);
  Serial.println(temperatura);

  float comprimento = medidas(100);
  Serial.println(comprimento);

  float centimentros = tamanho(50);
  Serial.println(centimentros);

  float tv = televisao(72);
  Serial.println(tv);
}

void loop()
{
}

// float pitagoras(float catetoA, float catetoB)
//{
// float resultado = sq(catetoA) + sq(catetoB);
// return sqrt(resultado);
//}
float celsius(float gruas)
{

  return (gruas * 9 / 5) + 32;
}

float medidas(float milimetros)
{
  return (milimetros / 25.4);
}
float tamanho(float polegadas)
{
  return (25.4 * polegadas);
}
float visor(float polegadas)
{
  return (polegadas * 2.54);
}

float televisao(float altura)
{

  float conversao = sq(visor(50)) - sq(altura);
  return sqrt(conversao);
}