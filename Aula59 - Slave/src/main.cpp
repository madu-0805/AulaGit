#include <Arduino.h>
#include <BluetoothSerial.h>
/**madu silva 
 * aula slave
 */
BluetoothSerial BT;

void setup()
{
  Serial.begin(9600);

  if (BT.begin("ESPSLAVEMadu"))
  {
    Serial.println("Bluetooth iniciado com sucesso");
  }
  else
  {
    Serial.println("Erro ao iniciar o Bluetooth");
 }
}

void loop()
{
   if (Serial.available()) // Lê a entrada do monitor serial até encontrar o caractere de nova linha ('\n')
  {
    String mensagemEnviar = Serial.readStringUntil('\n'); // vai ler a serial
    mensagemEnviar.trim();                                // vai tirar espaco \n \r
    BT.println(mensagemEnviar);
  }
  if (BT.available())
  {
    String mensagemRecebida = BT.readStringUntil('\n');
    mensagemRecebida.trim();
    Serial.println("Mensagem Recebida" + mensagemRecebida); // o + esta ajuntado as duas frases

    if (mensagemRecebida.equals("liga"))
    {
    }
    else if (mensagemRecebida.equals("desliga"))
    {
    }
  }
}
