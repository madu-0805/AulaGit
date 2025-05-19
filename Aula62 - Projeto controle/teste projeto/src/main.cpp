#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
/* teste projeto em grupo
madu silva*/

// ********************** DEFINICOES *********************

const char enderecoMaster[] = {};  // Endereço do dispositivo mestre
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

#define ledBotaoA 32
#define ledBotaoB 33
#define ledBotaoC 34
#define ledBotaoD 35
#define ledBotaoE 36
#define ledBotaoF 39
#define ledBotaoK 4

const char pinJoyStick[num_botoes] = {
    pinBotaoA, pinBotaoB, pinBotaoC, pinBotaoD, pinBotaoE, pinBotaoF, pinBotaoK
};

// *********************   OBJETOS   *********************

BluetoothSerial BT;
Bounce *joystick = new Bounce[num_botoes];
JsonDocument doc;
LiquidCrystal_I2C lcd(0x27, 20, 4);

// *********************  VARIAVEIS  *********************
int mudancaBotoes[num_botoes] = {0, 0, 0, 0, 0, 0, 0};
int estadoBotoes[num_botoes] = {0, 0, 0, 0, 0, 0, 0};

static int analogicoAnterior[2] = {9, 9};
int analogicoAtual[2] = {0, 0};

// **************** PROTOTIPO DAS FUNCOES ************
void reconectarBT();
void IniciarBT();

enum pinsBotoes {
  botaoA = 0, botaoB = 1, botaoC = 2, botaoD = 3, botaoE = 4, botaoF = 5, botaoK = 6,
};

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Slave Conectado");

  IniciarBT();

  for (char i = 0; i < num_botoes; i++) {
    joystick[i].attach(pinJoyStick[i], INPUT);
  }

  // Configura os pinos dos LEDs como saída
  pinMode(ledBotaoA, OUTPUT);
  pinMode(ledBotaoB, OUTPUT);
  pinMode(ledBotaoC, OUTPUT);
  pinMode(ledBotaoD, OUTPUT);
  pinMode(ledBotaoE, OUTPUT);
  pinMode(ledBotaoF, OUTPUT);
  pinMode(ledBotaoK, OUTPUT);
}

void loop() {
  bool atualizacao = false;

  int analogicoAtual[2] = {analogRead(pinAnalogicoX) / 200, analogRead(pinAnalogicoY) / 200};
  doc.clear();

  for (char j = 0; j < num_botoes; j++) {
    joystick[j].update();

    if (joystick[j].changed()) {
      char chave[10];
      sprintf(chave, "botao%d", j);
      doc[chave] = !joystick[j].read();
      mudancaBotoes[j] = 1;
      estadoBotoes[j] = !joystick[j].read();
      atualizacao = true;

      // Controle dos LEDs de acordo com o botão pressionado
      if (estadoBotoes[j] == 1) {
        switch (j) {
          case botaoA: digitalWrite(ledBotaoA, HIGH); break;
          case botaoB: digitalWrite(ledBotaoB, HIGH); break;
          case botaoC: digitalWrite(ledBotaoC, HIGH); break;    
          case botaoD: digitalWrite(ledBotaoD, HIGH); break;
          case botaoE: digitalWrite(ledBotaoE, HIGH); break;
          case botaoF: digitalWrite(ledBotaoF, HIGH); break;
          case botaoK: digitalWrite(ledBotaoK, HIGH); break;
        }
      } else {
        switch (j) {
          case botaoA: digitalWrite(ledBotaoA, LOW); break;
          case botaoB: digitalWrite(ledBotaoB, LOW); break;
          case botaoC: digitalWrite(ledBotaoC, LOW); break;
          case botaoD: digitalWrite(ledBotaoD, LOW); break;
          case botaoE: digitalWrite(ledBotaoE, LOW); break;
          case botaoF: digitalWrite(ledBotaoF, LOW); break;
          case botaoK: digitalWrite(ledBotaoK, LOW); break;
        }
      }
    }
  }

  if (analogicoAtual[0] != analogicoAnterior[0]) {
    doc["anX"] = analogicoAtual[0];
    atualizacao = true;
  }

  if (analogicoAtual[1] != analogicoAnterior[1]) {
    doc["anY"] = analogicoAtual[1];
    atualizacao = true;
  }

  analogicoAnterior[0] = analogicoAtual[0];
  analogicoAnterior[1] = analogicoAtual[1];

  String payload;
 
  if (atualizacao) {
    serializeJson(doc, payload);
    Serial.println(payload);
  }

  if (BT.connected()) {
    BT.println(payload);
  } else {
    reconectarBT();
  }

  if (atualizacao) {
    for (int i = 0; i < num_botoes; i++) {
      if (mudancaBotoes[i]) {
        lcd.setCursor(0, 0);
        lcd.printf("Botao %d esta %s", i, estadoBotoes[i] ? "Precionado" : "Solto");
      }
    }
  }
}

void reconectarBT() {
  if (BT.connected()) return;

  Serial.println("Tentando reconectar...");
  BT.end();
  delay(1000);
  IniciarBT();
}

void IniciarBT() {
  Serial.println("Esp32 Iniciado");

  bool iniciouSucesso = BT.begin("SLAVE-GUI", false);  // Inicia como slave

  if (iniciouSucesso) {
    Serial.print("O Bluetooth iniciou como slave com sucesso");
  } else {
    Serial.println("Erro ao iniciar o Bluetooth como slave");
    ESP.restart();
  }

  Serial.println("Tentando conectar ao MASTER");

  if (BT.connect(enderecoMaster)) {
    Serial.println("Conectado ao MASTER com sucesso");
  }
}