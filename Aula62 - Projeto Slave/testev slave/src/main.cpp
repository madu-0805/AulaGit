#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>
/*Madu Silva 
teste do projeto em grupo slave

*/
BluetoothSerial BT;
JsonDocument doc;
#define LED_PIN 2

void setup() {
  Serial.begin(9600);
  BT.begin("slaveGusta"); // Nome do dispositivo Bluetooth
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Esperando dados via Bluetooth...");
}

void loop() {
  if (BT.available()) {
    String mensagem = BT.readStringUntil('\n');
    Serial.print("Recebido: ");
    Serial.println(mensagem);

    
    if (erro) {
      Serial.print("Erro ao ler JSON: ");
      Serial.println(erro.c_str());
      return;
    }

    // Acende o LED se "Botao0" for true
    if (doc.containsKey("Botao0") && doc["Botao0"] == true) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED LIGADO (Botao0)");
    }

    // Apaga o LED se "Botao1" for true
    if (doc.containsKey("Botao1") && doc["Botao1"] == true) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED DESLIGADO (Botao1)");
    }
  }
}

