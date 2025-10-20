#include <Arduino.h>
#include <VL53L0X.h>

VL53L0X sensor;
//*ENDERECO PADRAO 0X29
void setup()
{
  Serial.begin(9600);

  Wire.begin(8, 9);       //* Vai fazer a comunicacao I2c(SDA,SCL)
  if (!sensor.init(0x2A)) //* Caso o sensor nao inicie
  {
    Serial.print("Falha no Sensor");
    while (1)
      ;
  }
  // sensor.setAddress(0x2A);

  /*sensor.setMeasurementTimingBudget(20000); //* tempo maximo de leitura do sensor em microSeguando
  sensor.startContinuous(25);               //* Ativa a leitura automatica do sensor a cada 25 ms
  sensor.setTimeout(100);                   //*Limita o tempo de leitura com erro para nao travar
  */
}

void loop()
{
 /*uint16_t distancia = sensor.readRangeContinuousMillimeters();
  Serial.println(distancia);
  delay(1000);

  if (sensor.timeoutOccurred())
  {
    Serial.println("Timeout na leitura do sensor");
  }
  else
  {
    Serial.printf("Distancia: %.2f mm \n", distancia);
    delay(200);
  }*/ 
}
