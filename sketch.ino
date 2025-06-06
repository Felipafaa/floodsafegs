#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>

// Definições de pinos
#define PIN_TRIG 26
#define PIN_ECHO 25
#define LOWLED   18
#define MIDLED   19
#define HIGHLED  21
#define MOTOR    27

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variáveis
unsigned int level = 0;
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Pinos
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(LOWLED, OUTPUT);
  pinMode(MIDLED, OUTPUT);
  pinMode(HIGHLED, OUTPUT);
  pinMode(MOTOR, OUTPUT);

  digitalWrite(LOWLED, HIGH);
  digitalWrite(MIDLED, HIGH);
  digitalWrite(HIGHLED, HIGH);
  digitalWrite(MOTOR, HIGH);

  // LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // Wi-Fi e MQTT
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  // Conexão MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Inicia nova medição
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Lê a duração do pulso
  int duration = pulseIn(PIN_ECHO, HIGH);

  // Converte duração para centímetros
  level = duration / 58;

  // Exibe no Serial Monitor
  Serial.print("Distancia em cm: ");
  Serial.println(level);
  Serial.print("Distancia em polegadas: ");
  Serial.println(duration / 148);

  // Publica no MQTT
  char msg[50];
  snprintf(msg, 50, "{\"nivel\": %u}", level);
  client.publish("floodsafe/nivel", msg);

  // Atualiza o LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nivel da agua");

  if (level < 150) {
    lcd.setCursor(0, 1);
    lcd.print("muito baixo");
    digitalWrite(LOWLED, LOW);
    digitalWrite(MIDLED, HIGH);
    digitalWrite(HIGHLED, HIGH);
  }
  else if (level > 150 && level < 250) {
    lcd.setCursor(0, 1);
    lcd.print("Medio");
    digitalWrite(LOWLED, HIGH);
    digitalWrite(MIDLED, LOW);
    digitalWrite(HIGHLED, HIGH);
  }
  else if (level >= 250) {
    lcd.setCursor(0, 1);
    lcd.print("muito alto");
    digitalWrite(LOWLED, HIGH);
    digitalWrite(MIDLED, HIGH);
    digitalWrite(HIGHLED, LOW);
  }

  delay(1000);
}
