#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "fir-led-53612.firebaseio.com"
#define FIREBASE_AUTH "f7YGreZgwZ0D1BKK07WLqmhnU3KPkTIk4yjiIsC6"
#define WIFI_SSID "승목"
#define WIFI_PASSWORD "99990000"

String fireStatus ="";
int led = D4;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  pinMode(led, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.setString("LED STATUS", "OFF");
}

void loop()
{
  fireStatus = Firebase.getString("LED_STATUS");
  if (fireStatus == "ON") {
    Serial.println("Led Turned ON");
    digitalWrite(led, HIGH);
  }
  else if (fireStatus == "OFF"){
    Serial.println("Led Turned OFF");
    digitalWrite(led, LOW);
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }
  delay(1000);
}
