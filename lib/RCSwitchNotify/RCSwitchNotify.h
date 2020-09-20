/*
  RCNotify_h - Library for notify.
  This Library is integrating the Blynk's notification along with RCSwitch.

  Created by Mario Ponciano, September 20, 2020.
*/
#ifndef RCSwitchNotify_h
#define RCSwitchNotify_h

#include <RCSwitch.h>
#include <BlynkSimpleEsp8266.h>

class RCSwitchNotify
{

private:
    byte pinLed;
    int rcDevice;
    boolean flag = false;
    RCSwitch mySwitch;

public:
    RCSwitchNotify(byte pinLed, int rcDevice)
    {
        this->mySwitch = RCSwitch();
        this->pinLed = pinLed;
        this->rcDevice = rcDevice;
    }

    /**
    * Enable receiving data
    * 
    * @param interrupt 
    */
    void enabledReceive(int interrupt)
    {
        this->mySwitch.enableReceive(interrupt);
    }

    /**
     * Check if the RCSwitch is available and receiving data:
     * First, it's checking if the device serial number is configured an then turn the led ON and send a notification through Blynk server.
     * However if the device is not configured it will print a message and notification won't be send.
     */
    void sendBlynkNotification()
    {

        int value = mySwitch.getReceivedValue();
        if (mySwitch.available())
        {
            if (value == rcDevice && !flag)
            {
                Serial.print("led On");
                digitalWrite(pinLed, HIGH);
                delay(5000);
                digitalWrite(pinLed, LOW);

                Blynk.notify("Alert: Door is open."); // Blynk notification

                flag = true;
            }
            else
            {
                Serial.print("Bad code. You code is ");
                Serial.println(mySwitch.getReceivedValue());
                flag = false;
            };

            // Printing the RF433 device information.
            Serial.print("Received ");
            Serial.print(mySwitch.getReceivedValue());
            Serial.print(" / ");
            Serial.print(mySwitch.getReceivedBitlength());
            Serial.print("bit ");
            Serial.print("Protocol: ");
            Serial.println(mySwitch.getReceivedProtocol());
            mySwitch.resetAvailable();
            flag = false;
        }
    }
};

#endif