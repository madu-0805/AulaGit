#include <Arduino.h>
#include <WIFI.h>
#include <ezTime.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>
/**madu silva
 * parte 2
 */
#define botao 0
// Defina as credenciais da rede Wi-Fi
void conectaWifi();
void checkWifi();

const char *SSID = "SALA 9";
const char *SENHA = "info@134";
// Defina os tempos de espera para conexão e reconexão
const unsigned long tempoEsperaConexao = 20000;
const unsigned long tempoEsperaReconexao = 5000;

Timezone tempo;
LiquidCrystal_I2C lcd(0x27, 20, 4);
Bounce bounce = Bounce();

void setup()
{
  bounce.attach(botao, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  waitForSync(); // busca na rede
  Serial.begin(9600);
  conectaWifi(); // Tenta conectar ao Wi-Fi
  tempo.setLocation("America/Sao_Paulo");
}

void loop()
{
  static bool estadoAnterior = 1;
  static bool escolha = 1;
  bool estadoAtual = digitalRead(botao);

  bounce.update();

  checkWifi();

  // Serial.println(tempo.dateTime()); // a data e hora atual

  switch (tempo.weekday())
  //  o dia da semana
  {
    lcd.setCursor(0, 0);
  case 1:
    lcd.setCursor(0, 0);
    lcd.print("Domingo");
    break;

  case 2:
    lcd.setCursor(0, 0);
    lcd.print("Segunda");
    break;

  case 3:
    lcd.setCursor(0, 0);
    lcd.print("Terca");
    break;

  case 4:
    lcd.setCursor(0, 0);
    lcd.print("Quarta");
    break;
  case 5:

    lcd.setCursor(0, 0);
    lcd.print("Quinta");
    break;

  case 6:
    lcd.setCursor(0, 0);
    lcd.print("Sexta");
    break;

  case 7:
    lcd.setCursor(0, 0);
    lcd.print("Sabado");
    break;
  }

  //! dia

  lcd.setCursor(0, 1);

  if (tempo.day() > 10) // o dia do mês atual
  {
    lcd.printf("0%d", tempo.day());
  }
  else
  {
    lcd.print(tempo.day());
  }

  switch (tempo.month()) //  E O MES ATUAL (1 A)
  {

  case 1:
    lcd.setCursor(3, 1);
    lcd.print("Janeiro");
    break;

  case 2:
    lcd.setCursor(3, 1);
    lcd.print("Fevererio");
    break;

  case 3:
    lcd.setCursor(3, 1);
    lcd.print("Marco");
    break;

  case 4:
    lcd.setCursor(3, 1);
    lcd.print("Abril");
    break;

  case 5:
    lcd.setCursor(3, 1);
    lcd.print("Maio");
    break;

  case 6:
    lcd.setCursor(3, 1);
    lcd.print("Junho");
    break;

  case 7:
    lcd.setCursor(3, 1);
    lcd.print("Julho");
    break;

  case 8:
    lcd.setCursor(3, 1);
    lcd.print("Agosto");
    break;

  case 9:
    lcd.setCursor(3, 1);
    lcd.print("Setembro");
    break;

  case 10:
    lcd.setCursor(3, 1);
    lcd.print("Outubro");
    break;

  case 11:
    lcd.setCursor(3, 1);
    lcd.print("Novembro");
    break;

  case 12:
    lcd.setCursor(3, 1);
    lcd.print("Dezembro");
    break;
  }

  lcd.setCursor(12, 1);    //! fazer nada
  lcd.print(tempo.year()); // o ano atual
                           //! horas
  lcd.setCursor(0, 2);
  // lcd.print(tempo.hour()); // a hora atual no formato 24 horas

  if (bounce.fell())
  {
    if (tempo.hour() < 10)
    {
      lcd.printf("0%d", tempo.hour());
    }
    else
    {
      lcd.print(tempo.hour());
    }
  }

  if (tempo.hour() < 10)
  {
    lcd.printf("0%d", tempo.hour());
  }
  else
  {
    lcd.print(tempo.hour());
  }

  //! minutos
  lcd.setCursor(3, 2);
  lcd.print(tempo.minute()); // os minutos atuais

  if (tempo.minute() > 10)
  {
    lcd.printf("0%d", tempo.minute());
  }
  else
  {
    lcd.print(tempo.minute());
  }

  //! segundos
  lcd.setCursor(6, 2);
  lcd.print(tempo.second()); // os segundos atuais
  if (tempo.second() > 10)
  {
    lcd.printf("0%d", tempo.second());
  }
  else
  {
    lcd.print(tempo.second());
  }

  // Serial.println(tempo.hourFormat12()); //  a hora no formato 12 horas
  // Serial.println(tempo.now());          // o timestamp atual segundo desde 01/01/1970
  //  Serial.println(tempo.dayOfYear()); // o número do dia no ano
  //  Serial.println(tempo.isAM());      // se for antes do meio-dia
  //  Serial.println(tempo.isPM());      // se for depois do meio-dia

  delay(1000);
}

void conectaWifi()
{

  Serial.printf("Conectando ao Wifi: %s", SSID);

  WiFi.begin(SSID, SENHA); // Inicia a conexão com o Wi-Fi
  unsigned long tempoInicialWiFi = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - tempoInicialWiFi < tempoEsperaConexao)
  {
    Serial.print(" . "); // Indica que está tentando conectar
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\n Wifi conectado com sucesso !");
    Serial.print("Enderco IP:");
    Serial.println(WiFi.localIP()); // Exibe o endereço IP local
  }
  else
  {
    Serial.println("\nFalta ao conectar no Wifi. Verfique o nome da rede e a senha");
  }
}

void checkWifi() // Função para verificar o status da conexão Wi-Fi

{
  unsigned long tempoAtual = millis();
  static unsigned long tempoUltimaConexao = 0;
  // Verifica se é hora de checar a conexão Wi-Fi
  if (tempoAtual - tempoUltimaConexao > tempoEsperaReconexao)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("\n Conexao perdida! tentando reconectar");
      conectaWifi(); // Tenta reconectar ao Wi-Fi
    }

    tempoUltimaConexao = tempoAtual;
  }
}
