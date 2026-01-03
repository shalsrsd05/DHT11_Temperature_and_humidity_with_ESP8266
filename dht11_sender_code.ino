#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// ------------------ DHT CONFIG ------------------
#define DHTPIN D4          // GPIO2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ------------------ WIFI CONFIG ------------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ------------------ MQTT CONFIG ------------------
const char* mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp8266/dht11";
const char* mqtt_client_id = "ESP8266_DHT11_Client";

// ------------------ OBJECTS ------------------
WiFiClient espClient;
PubSubClient client(espClient);

// ------------------ WIFI CONNECT ------------------
void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

// ------------------ MQTT RECONNECT ------------------
void reconnectMQTT() {
  while (!client.connected()) {
    if (client.connect(mqtt_client_id)) {
      break;
    }
    delay(3000);
  }
}

// ------------------ SETUP ------------------
void setup() {
  Serial.begin(115200);
  dht.begin();

  setupWiFi();
  client.setServer(mqtt_broker, mqtt_port);
}

// ------------------ LOOP ------------------
void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    return;
  }

  // JSON Payload
  String payload = "{";
  payload += "\"temperature\": " + String(temperature) + ",";
  payload += "\"humidity\": " + String(humidity);
  payload += "}";

  client.publish(mqtt_topic, payload.c_str());

  delay(5000);  // Send every 5 seconds
}
