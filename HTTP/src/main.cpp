#include <Arduino.h>
#include <ezTime.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>  // Para HTTPS
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "internet.h" // Sua função conectaWifi() e checkWifi()

LiquidCrystal_I2C lcd(0x27, 20, 4);
Timezone tempo;
WiFiUDP ntpUDP;
Bounce botaoBoot = Bounce();
HTTPClient http;

// Variáveis de tempo
int dia = 0, mes = 0, ano = 0;
int hora = 0;
int minuto[2] = {0, 0};
int segundo[2] = {0, 0};
int diaSemana = 0;
int diaAno = 0;
bool formato24h = true;
bool manha = false;

// Variáveis de clima
String descricaoTempo = "N/A"; // Descrição do tempo (ex: Ensolarado)
float temperaturaAtual = 0.0; // Temperatura atual

const char *diaSemanaTexto[] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};
const char *mesTexto[] = {"jan", "fev", "mar", "abr", "mai", "jun", "jul", "ago", "set", "out", "nov", "dez"};

void obterClima() {
  String url = "https://www.msn.com/pt-br/clima/mapas/severeweather/in-S%C3%A3o-Caetano-do-Sul,S%C3%A3o-Paulo?loc=eyJsIjoiU8OjbyBDYWV0YW5vIGRvIFN1bCIsInIiOiJTw6NvIFBhdWxvIiwiYyI6IkJyYXNpbCIsImkiOiJCUiIsImciOiJwdC1iciIsIngiOiItNDYuNTY1Mzg3NzI1ODMwMDgiLCJ5IjoiLTIzLjYxNzk1OTk3NjE5NjI5In0%3D&weadegreetype=C&ocid=winp2fptaskbar&cvid=f74887edc7fd4ecdeb92c6422dc0ffb6&content=SevereWeather_wxswotl&alertid=14741750617252&ei=8";

  WiFiClientSecure client;
  client.setInsecure();  // Ignora SSL (usar apenas para testes)

  http.begin(client, url);  // HTTPS com WiFiClientSecure
  int httpCode = http.GET();  // Executa a requisição GET

  if (httpCode == 200) {  // Se a requisição foi bem-sucedida
    String payload = http.getString();   // Lê o corpo da resposta
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload); // Lê o JSON

    if (!error) {
      temperaturaAtual = doc["current"]["temperature_2m"] | 0.0;
      int codigoTempo = doc["current"]["weather_code"] | -1;
 // Interpreta o código do tempo e transforma em texto
      switch (codigoTempo) {
        case 0: descricaoTempo = "Ceu limpo"; break;
        case 1: case 2: case 3: descricaoTempo = "Ensolarado"; break;
        case 4: case 5: case 6: descricaoTempo = "Nublado"; break;
        case 45: case 48: descricaoTempo = "Nevoeiro"; break;
        case 51: case 53: case 55: descricaoTempo = "Garoa"; break;
        case 61: case 63: case 65: descricaoTempo = "Chuva"; break;
        case 80: case 81: case 82: descricaoTempo = "Chuva intensa"; break;
        case 95: descricaoTempo = "Trovoadas"; break;
        default: descricaoTempo = "Desconhecido"; break;
      }
    } else {
      descricaoTempo = "Erro JSON"; // Se der erro ao interpretar
      Serial.println("Erro ao ler JSON");
    }

    Serial.println("Clima atualizado!");
  } else {
    descricaoTempo = "Erro clima";    // Se falhar a requisição
    Serial.print("Erro clima: ");
    Serial.println(httpCode);
  }

  http.end(); // Finaliza a conexão HTTP
}

void display() {
  lcd.clear(); // Limpa o display
  lcd.setCursor(0, 0);
  lcd.printf("%02d/%s/%04d", dia, mesTexto[mes - 1], ano);  // Linha 0: data
  lcd.setCursor(0, 1);
  lcd.print(diaSemanaTexto[diaSemana - 1]);     // Linha 1: dia da semana
  lcd.setCursor(0, 2);
  lcd.printf("%02d:%02d:%02d", hora, minuto[1], segundo[1]);  // Linha 2: hora
  lcd.setCursor(0, 3);
  lcd.printf("%.1fC %s", temperaturaAtual, descricaoTempo.c_str());  // Linha 3: clima
}

void setup() {
  Serial.begin(9600);
  botaoBoot.attach(0, INPUT_PULLUP);
  botaoBoot.interval(25);

  conectaWifi(); // Sua função para conectar ao Wi-Fi
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP());  // Mostra o IP local

  tempo.setLocation("America/Sao_Paulo");
  waitForSync();  // Espera sincronizar com servidor NTP


 // Armazena os valores de data e hora atual nas variáveis globais
  dia = tempo.day();
  dia = tempo.day();
  mes = tempo.month();
  ano = tempo.year();
  hora = tempo.hour();
  minuto[1] = tempo.minute();
  segundo[1] = tempo.second();
  diaSemana = tempo.weekday();
  diaAno = tempo.dayOfYear();
  manha = tempo.isAM();

  lcd.init();
  lcd.backlight();

  obterClima(); // Busca clima ao iniciar
  display(); // Exibe as informações
}

void loop() {
  botaoBoot.update(); // Atualiza o estado do botão
  // Se o botão for pressionado, troca entre 24h e 12h
  if (botaoBoot.fell()) {
    formato24h = !formato24h;
    lcd.setCursor(0, 2);
    lcd.printf("%02d", formato24h ? tempo.hour() : tempo.hourFormat12());
  }

  checkWifi();
  segundo[1] = tempo.second();   // Atualiza hora atual
  minuto[1] = tempo.minute(); 
  hora = tempo.hour();
  dia = tempo.day();
  mes = tempo.month();
  ano = tempo.year();
  diaSemana = tempo.weekday();
 
    // Atualiza apenas o segundo no LCD se mudou

  if (segundo[1] != segundo[0]) {
    lcd.setCursor(6, 2);
    lcd.printf("%02d", segundo[1]);
    segundo[0] = segundo[1];
  }
 // Se o minuto mudou, atualiza clima e tela inteira
  if (minuto[1] != minuto[0]) {
    lcd.setCursor(3, 2);
    lcd.printf("%02d", minuto[1]);
    minuto[0] = minuto[1];

    obterClima(); // Atualiza clima a cada minuto
    display();
  }
}