/**
*  HomeNotifier - It is a library to monitor and notify through Blynk iot platform
*
*  Supporting:
*   - Magnetic Reed Swictch RF433mhz sensor.
*
* Created by Mario Ponciano, September 20, 2020.
*/
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <RCSwitch.h>
#include <Credentials.h>
#include <RCSwitchNotify.h>

const int PIN_LED1 = D5;
const int RCDEVICE_0 = 167149813;

BlynkTimer timer;

// BlynkToken
char auth[] = BLYNK_TOKEN;

// Your WiFi credentials.
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;

boolean flag = false;

RCSwitchNotify rcSwitchNotify = RCSwitchNotify(PIN_LED1, RCDEVICE_0);

void sendNotification()
{
  rcSwitchNotify.sendBlynkNotification();
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  delay(10);
  pinMode(PIN_LED1, OUTPUT);

  rcSwitchNotify.enabledReceive(0); // Connected to GPIO0 (D3) of Nodemcu 1.0 module

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendNotification);
}

void loop()
{
  Blynk.run();
  timer.run();
}
