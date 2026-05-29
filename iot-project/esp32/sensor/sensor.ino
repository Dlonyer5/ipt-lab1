#include <WiFi.h>
#include <WebSocketsClient.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11

const char* ssid = "POCO F7";
const char* password = "IShowSpeed";

const char* websocket_host = "10.215.51.105";
const int websocket_port = 5000;

DHT dht(DHTPIN, DHTTYPE);
WebSocketsClient webSocket;

bool wsConnected = false;
unsigned long lastSendTime = 0;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("WebSocket connected!");
      wsConnected = true;
      break;

    case WStype_DISCONNECTED:
      Serial.println("WebSocket disconnected!");
      wsConnected = false;
      break;

    case WStype_ERROR:
      Serial.println("WebSocket error!");
      wsConnected = false;
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  dht.begin();

  Serial.println("Starting ESP32...");
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin(websocket_host, websocket_port, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();

  if (millis() - lastSendTime >= 2000) {
    lastSendTime = millis();

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT11!");
      return;
    }

    String json = "{\"temp\":" + String(t, 2) + ",\"humidity\":" + String(h, 2) + "}";

    if (wsConnected) {
      webSocket.sendTXT(json);
      Serial.print("Sent: ");
      Serial.println(json);
    } else {
      Serial.print("WebSocket not connected. Data not sent: ");
      Serial.println(json);
    }
  }
}