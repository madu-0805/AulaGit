/*#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;

void setup()
{
  mcp.begin_I2C();
  mcp.pinMode(10, OUTPUT); // 10 ao 15
}

void loop()
{
  mcp.digitalWrite(10, HIGH);
  delay(500);
  mcp.digitalWrite(10, LOW);
  delay(500);
}
*/

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_ADS1X15.h>
#include <PubSubClient.h>
//---------- OBJETO ----------
Adafruit_MCP23X17 mcp;
Adafruit_ADS1X15 ads;
PubSubClient client();

// Controle de tempo com millis()
unsigned long previousMillis = 0;
const unsigned long interval = 500; // intervalo de piscar (ms)
bool ledState = false;

//* ===== CONFIG MQTT =====
const int mqtt_port = 8883;
const char *mqtt_id = "espsantosmesa01";
const char *mqtt_sub = "teste/carinho";
const char *mqtt_pub = "teste/carinho";
const char *mqttTopic = "teste/carrinho";

void setup()
{
  Serial.begin(9600);

  // Inicializa o MCP23X17 via I2C
  if (!mcp.begin_I2C())
  {
    Serial.println("Erro ao inicializar MCP23X17!");
    while (1)
      ;
  }

  // Configura cada pino individualmente
  mcp.pinMode(10, OUTPUT);
  mcp.pinMode(11, OUTPUT);
  mcp.pinMode(12, OUTPUT);
  mcp.pinMode(13, OUTPUT);
  mcp.pinMode(14, OUTPUT);
  mcp.pinMode(15, OUTPUT);

  // Garante que todos comecem desligados
  mcp.digitalWrite(10, LOW);
  mcp.digitalWrite(11, LOW);
  mcp.digitalWrite(12, LOW);
  mcp.digitalWrite(13, LOW);
  mcp.digitalWrite(14, LOW);
  mcp.digitalWrite(15, LOW);

  Serial.println("MCP23X17 configurado — piscando pinos 10 a 15 com millis()");
}

void loop()
{
  unsigned long currentMillis = millis();

  // Verifica se passou o intervalo
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    ledState = !ledState;

    // Atualiza todos os pinos individualmente
    mcp.digitalWrite(10, ledState ? HIGH : LOW);
    mcp.digitalWrite(11, ledState ? HIGH : LOW);
    mcp.digitalWrite(12, ledState ? HIGH : LOW);
    mcp.digitalWrite(13, ledState ? HIGH : LOW);
    mcp.digitalWrite(14, ledState ? HIGH : LOW);
    mcp.digitalWrite(15, ledState ? HIGH : LOW);

    Serial.print("Pinos 10 a 15: ");
    Serial.println(ledState ? "LIGADOS" : "DESLIGADOS");
  }

  // temperatura motores
  // int leitura = ads.readADC_SingleEnded(0); // de 0 a 3
  // float tempC = leitura * 0.01875;          // converter em teperatura do LM35

  // Serial.printf("Temperatura: %.2f C \n", tempC); //%.2f eh um float c 2 casas decimais
  // delay(1000);
}
