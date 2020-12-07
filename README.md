# MQTT DHT Sensor

Publishes data over MQTT in JSON format

## Config values

copy `example.env.h` to `env.h` in `src` directory

```c
#define WIFI_SSID <WIFI_SSID>
#define WIFI_PASSWORD <WIFI_PASSWORD>

#define MQTT_HOST <MQTT_HOST>
#define MQTT_PORT <MQTT_PORT>

#define MQTT_PUB_TOPIC <MQTT_PUB_TOPIC>

#define DHTPIN <DHTPIN>
#define DHTTYPE <DHT11 || DHT22>

#define SEALEVELPRESSURE_HPA (1013.25)
```

Make the required changes
