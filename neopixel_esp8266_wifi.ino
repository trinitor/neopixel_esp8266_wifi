#include "config.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>

#include <Adafruit_NeoPixel.h>

int changed = 0;
int effectnumber = 0;

// json variables
String effect  = "";
int red     = 0;
int green   = 0;
int blue    = 0;
int stripe  = 0;
int dim     = 0;
int refresh = 0;
int option1 = 0;
int option2 = 0;

WiFiUDP Udp;
// normal GBR stripe
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, LEDPIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, LEDPIN2, NEO_GRB + NEO_KHZ800);
// uncommon BRG stripe
//Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, LEDPIN1, NEO_BRG + NEO_KHZ800);
//Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, LEDPIN2, NEO_BRG + NEO_KHZ800);

void setup()
{
  unsigned int counter = 0;

  // Neopixel
  pixels1.begin();
  pixels1.show();
  pixels2.begin();
  pixels2.show();
  if(lamp == 1)
  {
    Serial.printf("default = lamp on");
    showDefaultColor();
  }

  // Serial
  Serial.begin(baudRate);
  Serial.println();
  Serial.printf("LEDs: %i \n", NUMPIXELS);
  Serial.printf("LEDPIN1: %i \n", LEDPIN1);
  Serial.printf("LEDPIN2: %i \n", LEDPIN2);
  Serial.printf("lamp: %i \n", lamp);
  Serial.printf("OTAHostname: %i \n", OTAHostname);
  Serial.printf("debugMode: %i \n", debugMode);

  // network
  Serial.println();
  Serial.printf("connecting to: %s", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED && counter <= wlanTimeout*2)
  {
    delay(500);
    Serial.print(".");
    counter++;
  }

  if(WiFi.status() == WL_CONNECTED)
  {
    Udp.begin(localUdpPort);

    Serial.println(" connected.");
    Serial.printf("now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  }
  else {
    if(debugMode == 1)
    {
      Serial.println(" connection failed!");
      Serial.println("UDP communication won't work!");
    }
  }

  // Over The Air Update
  if(OTAUpdate == 1)
  {
    ArduinoOTA.setPort(OTAPort);
    ArduinoOTA.setHostname(OTAHostname);
    ArduinoOTA.setPassword(OTAPassword);
    ArduinoOTA.onStart([]() {
      Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
  }
}

void loop()
{
  changed = 0;
  if(OTAUpdate == 1)
  {
     ArduinoOTA.handle();
  }

  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    if(debugMode == 1)
    {
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    }
    int len = Udp.read(incomingPacket, 255);

    if(len > 0)
    {
      incomingPacket[len] = 0;
      if(debugMode == 1)
      {
        Serial.printf("UDP packet contents: %s", incomingPacket);
      }
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(incomingPacket);

      if(!json.success())
      {
        Serial.println("parseObject() failed");
      }
      else
      {
        if(debugMode == 1)
        {
          for (JsonObject::iterator it=json.begin(); it!=json.end(); ++it)
          {
            Serial.println(it->key);
            Serial.println(it->value.asString());
          }
        }

        red     = json["red"];
        green   = json["green"];
        blue    = json["blue"];
        stripe  = json["stripe"];
        dim     = json["dim"];
        refresh = json["refresh"];
        effect  = json["effect"].as<const char*>();
        option1 = json["option"];
        option2 = json["option2"];

        changed = 1;
      }
    }

    if(refresh > 0)
    {
      Serial.println("new refresh rate received...");
      displayRefresh = refresh;
    }

    if(effect=="")
    {
      changed = 0;
    }
  }

  if(changed == 1) {
    getEffectNumber(effect);
    if(debugMode == 1) {
      Serial.printf("Execute Effect: %s \n", effect.c_str());
      Serial.printf("Effectnumber: %i \n", effectnumber);
    }

  }
  runEffectNumber(effectnumber);

  delay(displayRefresh);
}
