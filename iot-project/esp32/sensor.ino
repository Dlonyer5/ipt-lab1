#include <WiFi.h>
#include <WebSocketsClient.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11

const char* ssid = "PLDT_HOME_123";
const char* password = "yourpassword";

const char* websocket_host = "YOUR_PC_IPV4";
const int websocket_port = 5000;

DHT dht(DHTPIN, DHTTYPE);
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_CONNECTED) {
    Serial.println("WebSocket connected!");
  } else if (type == WStype_DISCONNECTED) {
    Serial.println("WebSocket disconnected!");
  }
}

void setup() {
  Serial.begin(9600);
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

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT11!");
    delay(2000);
    return;
  }

  String json = "{\"temp\":" + String(t) + ",\"humidity\":" + String(h) + "}";

  webSocket.sendTXT(json);

  Serial.print("Sent: ");
  Serial.println(json);

  delay(2000);
}