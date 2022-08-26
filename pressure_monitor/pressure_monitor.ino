/* 
 *  Basic water pressure sensor for Home Assistant via MQTT
 *  
 *  Uses home-assistant-integration, available in the library manager
 *  
 *  Not for commercial use!
 */

#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoHA.h>
#include "config.h"
#include "timer.h"
#include "function.h"

#define softwareVersion "1"

WiFiClient wifi;

//HA Sensor Setup
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(wifi,device);
HASensor pres("Pressure");

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(myName);

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  });

  ArduinoOTA.begin();

//HA Stuff
  device.setName(myName);
  device.setSoftwareVersion(softwareVersion);

  pres.setUnitOfMeasurement("psi");
  pres.setDeviceClass("pressure");
  pres.setIcon("hass:water");
  pres.setName("Water Pressure");

  mqtt.begin(brokerAddress, brokerUser, brokerPass);
}

void loop() {
  ArduinoOTA.handle();
  mqtt.loop();

  if (timer(refreshTime,0)) { //Timer for adding values to the array
    addPressure();
  }

  if (timer(3000,1)) {
    Serial.print("Converted: ");  Serial.print(getPressure());
    Serial.print(" | Raw : ");    Serial.println(averagePressure());

    pres.setValue(getPressure());
  }
  
}
