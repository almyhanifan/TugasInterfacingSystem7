#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#define BLYNK_PRINT Serial
#define DHTPIN 12        //DHT pin GPIO12 = D6
#define DHTTYPE DHT11   //DHT Type

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer1;
BlynkTimer timer2;
WidgetRTC rtc;

//Blynk Connetion Config
char auth[] = "02af7fa649e74a3a93ec296c836673f0"; //auth token blynk
char ssid[] = "birdy"; //SSID Wifi
char pass[] = "Birdie123"; //Password wifi

bool isFirstConnect = true;

BLYNK_CONNECTED() {
  if (isFirstConnect) {
    // Request Blynk server to re-send latest values for all pins
    Blynk.syncAll();

    // You can also update individual virtual pins like this:
    //Blynk.syncVirtual(V1, V2);

    isFirstConnect = false;
  }
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(V3, t);
}

void clockDisplay()
{
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();

  // Send time to the App
  Blynk.virtualWrite(V1, currentTime);
  // Send date to the App
  Blynk.virtualWrite(V2, currentDate);
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  rtc.begin();

  timer1.setInterval(1000L, sendSensor); //Read Temperature and Humidity every 1s
  timer2.setInterval(1000L, clockDisplay); //Read RTC from server every 1s
}

void loop() 
{
  Blynk.run();
  timer1.run();
  timer2.run();
}
