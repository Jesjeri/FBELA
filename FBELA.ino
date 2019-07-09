#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

String  Request;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "YOUR FEED"
#define AIO_KEY  "YOURKEY"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe homefeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/akzfeed");
boolean MQTT_connect();

boolean MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    Serial.println("CONNECTED TO MQTT");
    return true;
  }  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    mqtt.disconnect();
    delay(2000);
    retries--;
    if (retries == 0) {
      return false;
    }
  } return true;
}

void setup()
{
  Serial.begin(9600);
  Request = "";

  WiFi.disconnect();
  delay(3000);
  Serial.println("Start IoT");
  WiFi.begin("SSID", "PSWD");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print(".");

  }
  Serial.println("Wifi Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));

  mqtt.subscribe(&homefeed);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);
  pinMode(D6, OUTPUT);
  digitalWrite(D6, LOW);
  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW);
  pinMode(D8, OUTPUT);
  digitalWrite(D8, LOW);
}


void loop()
{
Serial.println("111222333");
  if (MQTT_connect()) {
    Adafruit_MQTT_Subscribe *subscription_name;
    while ((subscription_name = mqtt.readSubscription(5000))) {
      if (subscription_name == &homefeed) {
        Request = ((char *)homefeed.lastread);
        Serial.println(Request);
        if(Request=="d0on  ") {
          digitalWrite(D0, HIGH);
          Serial.println("0LED ON");
        }
        else if (Request == "d0off  ") {
          digitalWrite(D0, LOW);
          Serial.println("0LED OFF");
        }
        else if (Request == "d1on  ") {
          digitalWrite(D1, HIGH);
          Serial.println("1LED ON");
        }
        else if (Request == "d1off  ") {
          digitalWrite(D1, LOW);
          Serial.println("1LED OFF");
        }
        else if (Request == "d2on  ") {
          digitalWrite(D2, HIGH);
          Serial.println("2LED ON");
        }
        else if (Request == "d2off  ") {
          digitalWrite(D2, LOW);
          Serial.println("2LED OFF");
        }
        else if (Request == "d5on  ") {
          digitalWrite(D5, HIGH);
          Serial.println("5LED ON");
        }
        else if (Request == "d5off  ") {
          digitalWrite(D5, LOW);
          Serial.println("5LED OFF");
        }
        else if (Request == "d6on  ") {
          digitalWrite(D6, HIGH);
          Serial.println("6LED ON");
        }
        else if (Request == "d6off  ") {
          digitalWrite(D6, LOW);
          Serial.println("6LED OFF");
        }
        else if (Request == "d7on  ") {
          digitalWrite(D7, HIGH);
          Serial.println("7LED ON");
        }
        else if (Request == "d7off  ") {
          digitalWrite(D7, LOW);
          Serial.println("7LED OFF");
        }
        else if (Request == "d8on  ") {
          digitalWrite(D8, HIGH);
          Serial.println("8LED ON");
        }
        else if (Request == "d8off  ") {
          digitalWrite(D8, LOW);
          Serial.println("8LED OFF");
        }
      }
    }
  }
}
