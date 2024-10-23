#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define LED_PIN 28
// WiFi
const char* SSID = "SSID-HERE";
const char* WiFipassword = "PASSWORD-HERE";
// MQTT
const char* rpiIP = "RASPBERRY-PI-IP-HERE";
const char* mqttUserName = "MQTT-USERNAME-HERE";
const char* mqttPassword = "MQTT-PASSWORD-HERE";
const char* subTopic = "dashboard/led"; //The topic to subscribe to

//TODO: make a subtopic with the device ID / IP to request from specific device ex: dashboard/device/id/<device-ip>

WiFiClient rpicow;
PubSubClient client(rpicow);

void callback(char* topic, uint8_t* payLoad, unsigned int size);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  connectToWiFi();
  client.setServer(rpiIP, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void setLed(String& status) {
  if(status == "ON") {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
}

void connectToWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(SSID);
  WiFi.begin(SSID, WiFipassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP adress: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("reconnecting");
    if (client.connect(WiFi.localIP().toString().c_str(), mqttUserName, mqttPassword)) {
      Serial.println("Connected to MQTT Broker");
      client.subscribe(subTopic);
    } else {
      Serial.println("Failed to connect");
      Serial.println("will retry in 5 sec");
    }
    delay(5000);
  }
}

void callback(char* topic, uint8_t* payLoad, unsigned int size) {
  Serial.print("recieved message from: ");
  Serial.println(topic);
  String message = "";
  for (int i = 0; i < size; i++) {
    message += (char)payLoad[i];
  }
  setLed(message);
}