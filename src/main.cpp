#include <Arduino.h>
#include <WiFi.h>
#include <stdio.h>
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT_Client.h"
#include "./utilities.h"

#define WLAN_SSID "#"
#define WLAN_PASS "#"
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
//ADAFRUIT KEYS
#define AIO_USERNAME "#"
#define AIO_KEY "#"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe DoorOpener = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/DoorOpener");

#define PINOUT_1 2
#define PINOUT_2 3

#define HIGH_STATE_IN_MILISEC 1500
int pinOuts[] = {PINOUT_1, PINOUT_2};

void MQTT_connect();

void setup()
{
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  mqtt.subscribe(&DoorOpener);

  pinMode(PINOUT_1, OUTPUT);
}

uint32_t x = 0;
void loop()
{
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &DoorOpener)
    {
      Serial.print(F("Got: "));
      Serial.println((char *)DoorOpener.lastread);
      if (!strcmp((char *)DoorOpener.lastread, "open_door_1"))
      {
        stateChange(HIGH_STATE_IN_MILISEC, pinOuts[0]);
        Serial.println("DOOR 1 OPENED");
      }
      if (!strcmp((char *)DoorOpener.lastread, "open_door_2"))
      {
        stateChange(HIGH_STATE_IN_MILISEC, pinOuts[1]);
        Serial.println("DOOR 2 OPENED!");
      }
    }
  }
}

void MQTT_connect()
{
  int8_t ret;
  if (mqtt.connected())
  {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  int retrieves = 3;
  while ((ret = mqtt.connect()) != 0)
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retrieves--;
    if (retrieves == 0)
    {
      Serial.println("MQTT connection failed...:( Please reconfigure");
      while (1)
        ;
    }
  }
  Serial.println("MQTT Connected!");
}
