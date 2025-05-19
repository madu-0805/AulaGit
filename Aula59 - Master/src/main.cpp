/*Maria Eduarda Santos
15/04/25
aula 59 master
*/
//*O MASTER INICIA A COMUNICACAO PARA O SLAVE
#include <Arduino.h>
#include <BluetoothSerial.h>
#define pinLed 2

BluetoothSerial BT; // criar um objeto

uint8_t endSlave[] = {0x08, 0x3A, 0xF2, 0x8F, 0xA8, 0xDA}; // endereco dispositivo escravo

void setup()
{
  Serial.begin(9600);

  //!                   ↓ indica que e master , Inicia o Bluetooth como master (mestre)
  if (BT.begin("EspSantos", true))
  {
    Serial.println("Bluetooth iniciado com sucesso");
  }

  else
  {
    Serial.println("erro ao iniciar o bluetooth");
  }
  // Tenta conectar ao dispositivo Bluetooth escravo
  if (BT.connect(endSlave))
  {
    Serial.println("conectado com sucesso");
  }
  else
  {
    Serial.println("Nao foi possivel conectar o dispositivo bluetooth");
  }
  pinMode(pinLed, OUTPUT);

  //*Serial.println(BT.getBtAddressString()); // mostra o endereco do bluetooh
}
void loop()
{
  static bool pisca = false;
  static bool estadoLed = false;
  static int velocidade = 200;

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
      estadoLed = true;
      pisca = false;
    }
    else if (mensagemRecebida.equals("desliga"))
    {
      estadoLed = false;
      pisca = false;
    }
    else if (mensagemRecebida.equals("pisca"))
    {
      pisca = true;
    }
    else if (mensagemRecebida.equals("mais rapido "))
    {
      pisca = true;
      velocidade -= 100;
      if (velocidade < 50)
      {
        velocidade = 50;
      }
    }

    else if (mensagemRecebida.equals("mais devagar"))
    {
      pisca = true;
      velocidade += 100;
      if (velocidade > 1000)
      {
        velocidade = 1000;
      }
    }

    else if (mensagemRecebida.startsWith("velocidade = "))
    {
      int tamanho = mensagemRecebida.length();
      String extracao = mensagemRecebida.substring(13, tamanho);
      int valorVel = extracao.toInt();

      if (valorVel >= 0 && valorVel <= 100)
      {
        velocidade = map(valorVel, 0, 100, 1000, 50);
      }
      else
      {
        Serial.println("valores aceitos somente entre 0 e 100");
      }
    }
  }
  if (pisca == true)
  {
    unsigned long tempoAtual = millis();
    static unsigned long tempoInicial = 0;

    if (tempoAtual - tempoInicial >= velocidade)
    {
      estadoLed = !estadoLed;
      tempoInicial = tempoAtual;
    }
  }

  digitalWrite(pinLed, estadoLed);
}
