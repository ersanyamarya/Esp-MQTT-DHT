#include "header.h"

unsigned long previousMillis = 0; // Stores last time message was published
const long interval = 5000;       // Interval at which to publish

float temp;
float hum;

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  dht.begin();
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  //mqttClient.onSubscribe(onMqttSubscribe);
  //mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  //mqttClient.setCredentials("USER_NAME", "PASSWORD");
  connectToWifi();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    StaticJsonDocument<200> doc;

    // Save the last time a new reading was published
    previousMillis = currentMillis;
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    doc["location"] = "5";
    doc["MAC"] = WiFi.macAddress();
    doc["temp"] = temp;
    doc["hum"] = hum;

    // Checking if values a valid
    if (isnan(hum) || isnan(temp))
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    String dataToSend;
    serializeJson(doc, dataToSend);
    uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_TOPIC, 1, true, dataToSend.c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i", MQTT_PUB_TOPIC, packetIdPub1);
    /* Serial.printf(dataToSend.c_str()); */
  }
}