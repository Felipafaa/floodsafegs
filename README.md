# 🌊 FloodSafe – Monitoramento Inteligente de Nível de Água com IoT

![Wokwi Logo](https://img.shields.io/badge/Simulado%20no-Wokwi-green)
![MQTT](https://img.shields.io/badge/Protocolo-MQTT-blue)
![ESP32](https://img.shields.io/badge/Placa-ESP32-orange)
![Node-RED](https://img.shields.io/badge/Dashboard-Node--RED-red)

## 📌 Descrição do Projeto

Vinicius de Souza SantAnna rm556841
Felipe Rosa Peres rm557636
Pedro Henrique de Souza rm555533

**FloodSafe** é uma solução de monitoramento de enchentes e níveis de água baseada em IoT, desenvolvida para detectar variações de nível e alertar em tempo real por meio de atuadores físicos e um painel online.

Nossa aplicação simula cenários de emergência urbana e desastres naturais, com o objetivo de auxiliar a população ou órgãos responsáveis a tomarem decisões rápidas e preventivas.

---

## 🧠 Tecnologias e Conceitos Envolvidos

- **ESP32** como unidade de controle
- **Sensor Ultrassônico HC-SR04** para medir o nível da água
- **LEDs** para indicação visual de níveis (baixo, médio, alto)
- **Módulo Relé** para acionar um motor/bomba
- **Display LCD I2C** para exibir mensagens locais
- **Protocolo MQTT (broker.hivemq.com)** para transmissão de dados
- **Node-RED** com **Dashboard Web** para visualização em tempo real
- **JSON** como formato de payload

---

## 📡 Esquema de Comunicação IoT

[ESP32 + HC-SR04]
|
MQTT (JSON)
↓
[Broker MQTT Público: broker.hivemq.com]
↓
[Node-RED + Dashboard Web]


---


### 🔌 Simulação no Wokwi

## 🛠️ Componentes Utilizados

| Componente                | Quantidade |
|--------------------------|------------|
| ESP32 DevKit V1          | 1          |
| Sensor Ultrassônico HC-SR04 | 1      |
| LED (Vermelho, Verde, Amarelo) | 3    |
| Módulo Relé (simulando bomba) | 1      |
| Display LCD I2C 16x2     | 1          |
| Resistores               | 4          |
| Broker MQTT Público      | 1 (HiveMQ) |
| Node-RED + Dashboard     | 1          |

---

## 📈 Lógica de Funcionamento

- A cada segundo, o sensor ultrassônico mede a distância da água.
- O nível é interpretado da seguinte forma:
  - 🔴 **Baixo** (< 150 cm): LED 1 aceso
  - 🟡 **Médio** (150–250 cm): LED 2 aceso
  - 🔵 **Alto** (> 250 cm): LED 3 aceso + relé ativado
- O dado é publicado no tópico MQTT: `floodsafe/nivel`
- No **Node-RED**, o valor é exibido como:
  - **Gauge (medidor)** em cm
  - **Classificação textual** (Baixo / Médio / Alto)

---

## 🖥️ Dashboard Node-RED

- Acesse pelo navegador: `http://localhost:1880/ui` ou URL do seu servidor
- Medidor e texto se atualizam em tempo real com base no MQTT

---

## 📁 COMO EXECUTAR o Projeto

### 🧪 Simular no Wokwi

1. Acesse: [Projeto no Wokwi](https://wokwi.com/projects/376408708887997441) OU utilize os arquivos inseridos no github, clonando-os.
2. Clique em **"Start Simulation"**
3. Veja a atualização dos LEDs, LCD e Serial Monitor. Ao mexer nos centimetros do sensor de distância, leds irão se acender e de acordo com a distância, o visor demonstrará o nível da agua (Baixo, Médio e Alto).

### 🌐 Rodar Node-RED

1. Instale o Node-RED ([guia aqui](https://nodered.org/docs/getting-started/)) e rode na sua máquina.
2. Instale o **Node-Red Dashboard**. O pacote node-red-dashboard pode ser instalado via Menu > Manage palette > Install > node-red-dashboard.
3. Importe o [fluxo Node-RED] presente nesse repositório.
4. Clique em **Deploy**
5. Acesse: `http://localhost:1880/ui`


### O link deve abrir um pequeno dashboard com um medidor que mostra o nivel.

## 📦 Dependências do Projeto
### 🔧 Arduino / ESP32 (Wokwi)

-As seguintes bibliotecas são utilizadas no código:


WiFi.h-Conexão do ESP32 à rede Wi-Fi


PubSubClient.h-Comunicação MQTT com o broker público


LiquidCrystal_I2C.h-Controle do display LCD I2C para exibição local dos dados



Essas bibliotecas são carregadas automaticamente no Wokwi com base nos #include e também podem ser instaladas via Library Manager no Arduino IDE, se usado fora do simulador.

## 🌐 Node-RED
O dashboard é construído com os seguintes componentes:


node-red-dashboard-Criação de interface web com gauge, texto, etc.


mqtt in (nativo)-Receber mensagens do broker MQTT


json (nativo)-Converter a string recebida em objeto JSON


function (nativo)-Processar e classificar os valores do sensor



---

## 🌍 MQTT Broker

- Utilizado: `broker.hivemq.com` (público)
- Tópico: `floodsafe/nivel`
- Exemplo de mensagem enviada:

```json
{
  "nivel": 237
}
