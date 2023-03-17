#include <WiFi.h>
#include "WiFiClientSecure.h"
#include <AdafruitIO_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <LiquidCrystal.h>
WiFiClient client;
#define v 34
#define a 35
#define wifi_SSID       ""//wifi-name
#define wifi_PASS       ""//wifi password
#define AIO_SERVER      "io.adafruit.com"//server domain name
#define AIO_SERVERPORT  1883//port num
#define AIO_USERNAME    "OliverJesmon"//adafruit account user name
#define AIO_KEY         "aio_mZMo570VK6f7YnbYqB09XvamFhnz"//adafruit account personal token

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish voltage = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Voltage");
Adafruit_MQTT_Publish Current = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Current");
LiquidCrystal lcd(1,2,3,4,5,6);
float adc_voltage = 0.0;
float in_voltage = 0.0;
float volt=0.0;
//AC current constants
int mVperAmp = 185;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
// Floats for resistor values in divider (in ohms)
//const float R1 = 30000.0;
//const float R2 = 7500.0; 
 
// Float for Reference Voltage
float ref_voltage;
 
// Integer for ADC value
int adc_value = 0;


void setup() {
  lcd.begin(16,2);
  Serial.begin(115200);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(wifi_SSID);
  WiFi.begin(wifi_SSID, wifi_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
  connect();// connect to adafruit io
   lcd.print("voltage:");
   lcd.print("current:");
   
}
void connect() {
  Serial.print(F("Connecting to Adafruit IO... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(10000);
  }
  Serial.println(F("Adafruit IO Connected!"));
}
float volta()
{
  
}
float getVPP()
{
  float result;
  int readValue;                // value read from the sensor
  int maxValue = 0;             // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(a);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }

void loop() {
  
   // Calculate voltage at divider input
   in_voltage = 0.0;
   Voltage = getVPP();
  VRMS = (Voltage/2.0) *0.707;   //root 2 is 0.707
  AmpsRMS = (VRMS * 1000)/mVperAmp;
  //lcd.setCursor(0,14);
  //lcd.print(in_voltage);
   lcd.print("Voltage:");
   lcd.println(in_voltage);
   lcd.println("Current:");  
   Serial.print(AmpsRMS);
   lcd.clear();
   delay(1000);
   if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }
  
   
   if (! voltage.publish(in_voltage)) {
      Serial.println(F("Failed"));
    } 
       if (! Current.publish(AmpsRMS)) {            
      Serial.println(F("Failed"));
    }
    else {
      Serial.println(F("Sent!"));

}
}
#include <WiFi.h>
#include "WiFiClientSecure.h"
#include <AdafruitIO_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <LiquidCrystal.h>
WiFiClient client;
#define v 34
#define a 35
#define wifi_SSID       ""//wifi-name
#define wifi_PASS       ""//wifi password
#define AIO_SERVER      "io.adafruit.com"//server domain name
#define AIO_SERVERPORT  1883//port num
#define AIO_USERNAME    "OliverJesmon"//adafruit account user name
#define AIO_KEY         "aio_mZMo570VK6f7YnbYqB09XvamFhnz"//adafruit account personal token

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish voltage = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Voltage");
Adafruit_MQTT_Publish Current = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Current");
LiquidCrystal lcd(1,2,3,4,5,6);
float adc_voltage = 0.0;
float in_voltage = 0.0;
float volt=0.0;
//AC current constants
int mVperAmp = 185;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
// Floats for resistor values in divider (in ohms)
//const float R1 = 30000.0;
//const float R2 = 7500.0; 
 
// Float for Reference Voltage
float ref_voltage;
 
// Integer for ADC value
int adc_value = 0;


void setup() {
  lcd.begin(16,2);
  Serial.begin(115200);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(wifi_SSID);
  WiFi.begin(wifi_SSID, wifi_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
  connect();// connect to adafruit io
   lcd.print("voltage:");
   lcd.print("current:");
   
}
void connect() {
  Serial.print(F("Connecting to Adafruit IO... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(10000);
  }
  Serial.println(F("Adafruit IO Connected!"));
}
float volta()
{
  
}
float getVPP()
{
  float result;
  int readValue;                // value read from the sensor
  int maxValue = 0;             // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(a);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }

void loop() {
  
   // Calculate voltage at divider input
   in_voltage = 0.0;
   Voltage = getVPP();
  VRMS = (Voltage/2.0) *0.707;   //root 2 is 0.707
  AmpsRMS = (VRMS * 1000)/mVperAmp;
  //lcd.setCursor(0,14);
  //lcd.print(in_voltage);
   lcd.print("Voltage:");
   lcd.println(in_voltage);
   lcd.println("Current:");  
   Serial.print(AmpsRMS);
   lcd.clear();
   delay(1000);
   if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }
  
   
   if (! voltage.publish(in_voltage)) {
      Serial.println(F("Failed"));
    } 
       if (! Current.publish(AmpsRMS)) {            
      Serial.println(F("Failed"));
    }
    else {
      Serial.println(F("Sent!"));

}
}
