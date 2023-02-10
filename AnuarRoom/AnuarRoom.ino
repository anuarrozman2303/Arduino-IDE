#define BLYNK_TEMPLATE_ID "TMPLOk7oU-WQ"
#define BLYNK_DEVICE_NAME "Anuar Room"
#define BLYNK_AUTH_TOKEN "jh_5TpKnoewXZ21Tv43AtswoiJGkqpTC"

#include <WiFi101.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <BlynkSimpleMKR1000.h>

char SSID[] = "semanz";
char PASSWORD[] = "33632407";
char AUTH[] = BLYNK_AUTH_TOKEN;
RTCZero rtc;
const int GMT = +8;
unsigned long Started = 0;
const long interval = 1000;

void setupIoT() {
  WiFi.begin(SSID, PASSWORD);
  Blynk.begin(AUTH, SSID, PASSWORD); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void setupNTP() {  //NTP Setup
  rtc.begin();
  unsigned long epoch;                  // Variable to represent epoch
  int numberOfTries = 0, maxTries = 6;  // Variable for number of tries to NTP service
  // Get epoch
  do {
    epoch = WiFi.getTime();
    numberOfTries++;
  }
  while ((epoch == 0) && (numberOfTries < maxTries));
  if (numberOfTries == maxTries) {
    Serial.print("NTP unreachable!!");
    while (1)
      ;
  }
  else {
    Serial.print("Epoch received: ");
    Serial.println(epoch);
    rtc.setEpoch(epoch);
    Serial.println();
  }
}

void setup() {
  // put your setup code here, to run once:
  setupIoT();
  setupNTP();
}

void printTime()
{
  print2digits(rtc.getHours() + GMT);
  Serial.print(":");
  
  print2digits(rtc.getMinutes());
  Serial.print(":");
  
  print2digits(rtc.getSeconds());
  Serial.println();
}

void printDate()
{
  Serial.print(rtc.getDay());
  Serial.print("/");
  
  Serial.print(rtc.getMonth());
  Serial.print("/");
  
  Serial.print(rtc.getYear());
  Serial.print(" ");
}

String print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}

// Set Time to Run Every 1 Sec
void TIME() {
  unsigned long currentMillis = millis();
  if (currentMillis - Started >= interval) {
    Started = currentMillis;
    printDate();
    printTime();
  }
  else{}
}

void loop() {
  // put your main code here, to run repeatedly:
  TIME();
}
