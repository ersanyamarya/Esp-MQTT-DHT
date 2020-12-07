#ifndef _INCL_GUARD
#define _INCL_GUARD
#include <Arduino.h>
#include "env.h"
#include "DHT.h"
#include <Wire.h>
#include <WiFi.h>
#include <SPI.h>
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <AsyncMqttClient.h>
#include <ArduinoJson.h>

extern AsyncMqttClient mqttClient;
extern TimerHandle_t mqttReconnectTimer;
extern TimerHandle_t wifiReconnectTimer;
extern Adafruit_BMP280 bmp;

void connectToWifi();
void onMqttConnect(bool sessionPresent);
void connectToMqtt();
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
void WiFiEvent(WiFiEvent_t event);
void onMqttPublish(uint16_t packetId);
/*void onMqttSubscribe(uint16_t packetId, uint8_t qos);
void onMqttUnsubscribe(uint16_t packetId);*/
#endif