#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "masukkan host database"
#define FIREBASE_AUTH "masukkan secret code"
#define WIFI_SSID "masukkan nama access point"
#define WIFI_PASSWORD "masukkan password access point"
int relay = 16;
void setup() {
  Serial.begin(9600);
// connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
pinMode(relay, OUTPUT);
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("LED_Status", 0);
}
int n = 0;
void loop() {
  // set value
  n = Firebase.getInt("LED_Status");
  // handle error
  if (n == 1) {
      Serial.print("Relay ON");
      digitalWrite(relay, HIGH);  
      return;
      delay(1000);
  }
  else{
      Serial.print("\n Relay OFF");
      digitalWrite(relay, LOW);  
    }
}
