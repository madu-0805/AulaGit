#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
/*Madu Silva
joystick*/

//**         DEFINICOES  */

//char enderecoSlave[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
#define num_botoes 7
#define pinBotaoA 13
#define pinBotaoB 12
#define pinBotaoC 14
#define pinBotaoD 27
#define pinBotaoE 26
#define pinBotaoF 25
#define pinBotaoK 33
#define pinAnalogicoX 35
#define pinAnalogicoY 34

const char pinJoystick[] = {
    pinBotaoA,
    pinBotaoB,
    pinBotaoC,
    pinBotaoD,
    pinBotaoE,
    pinBotaoF,
    pinBotaoK}; //**A,B,C,D,E,F,K,X,Y */
// TODO fazer os analogicos X e Y

//***OBJETOS */

BluetoothSerial BT;
Bounce *joystick = new Bounce[num_botoes];
JsonDocument doc;
LiquidCrystal_I2C lcd(0x27, 20, 4);
//*VARIAVES */

//**PROTOTIPOS  */

void reconectardBT(); // Declaração de funções antes de usá-las no código
void iniciarBT();     // Chama a função para iniciar o Bluetooth
enum pinsBotoes
{
  botaoA = 0,
  botaoB = 1,
  botaoC = 2,
  botaoD = 3,
  botaoE = 4,
  botaoF = 5,
  botaoK = 6
};

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.print("teste");
  Serial.begin(9600); // Verifica se o Bluetooth está conectado
  iniciarBT();

  for (char i = 0; i < num_botoes; i++) // Corrige todos os botões definidos em 'num_botoes
  {
    joystick[i].attach(pinJoystick[i], INPUT); // Associa cada objeto 'joystick[i]' ao pino correspondente em 'pinJoystick[i]' como entrada
  }
  joystick[botaoA]; // Acesse o joystick específico correspondente ao botão A (possivelmente para fazer algo depois, mas falta o código aqui)
}

void loop()
{
  bool atualizacao = false;
  bool mudancaBotoes[num_botoes] = {0, 0, 0, 0, 0, 0, 0};
  bool estadoBotoes[num_botoes] = {0, 0, 0, 0, 0, 0, 0};

  static int analogicoAnterior[2] = {9, 9};
  int analogicoAtual[2] = {analogRead(pinAnalogicoX) / 200, analogRead(pinAnalogicoY) / 200};

  doc.clear(); // limpar o doc

  for (char j = 0; j < num_botoes; j++)
  {
    joystick[j].update();      /// o for nao pode ficar muito longo , mas sim ter quer ser rapido
    if (joystick[j].changed()) // Verifica se o estado do joystick na posição j mudou desde a última aula
    {
      char chave[10];
      sprintf(chave, "botao%d", j);
      doc[chave] = !joystick[j].read();
      mudancaBotoes[j] = 1;
      estadoBotoes[j] = !joystick[j].read();
      atualizacao = true;
    }
  }
  if (analogicoAtual[0] != analogicoAnterior[0])
  {
    doc["anX"] = analogicoAtual[0];
    atualizacao = true;
  }

  if (analogicoAtual[1] != analogicoAnterior[1])
  {
    doc["anY"] = analogicoAtual[1];
    atualizacao = true;
  }
  analogicoAnterior[0] = analogicoAtual[0];
  analogicoAnterior[1] = analogicoAtual[1];

  String payload;
  if (atualizacao)
  {

    serializeJson(doc, payload);
    Serial.println(payload);
  }

  if (BT.connected()) // Caso esteja conectado, o loop pode realizar ações específicas (não há nada dentro ainda)
  {
  }
  else // Caso não esteja conectado, o loop pode executar ações (também sem nada dentro neste caso)
  {
    reconectardBT();
  }
  if (atualizacao)
  {
    for (int i = 0; i < num_botoes; i++)
    {
      if (mudancaBotoes[i])
      {
      lcd.setCursor(0,0);
      lcd.printf("botao%d esta %s", i estadoBotoes?"Pressionado ": "solto");

      }
    }
  }
}

void reconectardBT() // Função para reconectar o Bluetooth caso ele perca a conexão
{
  if (BT.connected()) // Verifica se o Bluetooth já está conectado, caso sim, sai da função
  {
    return; // Sai da função se já estiver conectado
  }
  Serial.println("Tentando reconectar"); // Caso não esteja conectado, tenta reconectar
  BT.end();                              // Finaliza a conexão atual do Bluetooth
  delay(1000);                           // Atraso de 1 segundo para garantir que a desconexão seja processada antes de tentar reconectar
  iniciarBT();                           // Chama a função para iniciar o Bluetooth novamente
}

void iniciarBT()
{
  Serial.println("ESP32 iniciado");
  bool inicioSucesso = BT.begin("MASTER DUDA SANTOS", true); // Tentando iniciar o Bluetooth como master
  if (inicioSucesso)
  {
    Serial.println("O bluetooth iniciou como master com sucesso"); // Caso o Bluetooth tenha iniciado com sucesso como master
  }
  else
  {
    Serial.println("Erro ao iniciar o bluetooth como master");
    Serial.println("O esp32 sera reiniciado em :");
    for (char i = 5; i > 0; i--) // Contagem regressiva antes de reiniciar o ESP32
    {
      Serial.printf("%d......\n\r", i);
      delay(1000); // Espera 1 segundo antes de imprimir o próximo número
    }
    ESP.restart(); // Reinicia o ESP32
  }
  if (BT.connect(enderecoSlave))
  {
    Serial.println("conectado ao slave com sucesso");
  }
  else
  {
    Serial.println("nao foi possivel conectar ao slave");
  }
}
