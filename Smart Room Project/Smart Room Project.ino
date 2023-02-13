#define BLYNK_TEMPLATE_ID "TMPLDS1dKiP3"
#define BLYNK_DEVICE_NAME "Fan Control"
#define BLYNK_AUTH_TOKEN "vkWqDtBdOuC21CQdNcn6UZje-SWBixrW"
#define APP_KEY           "47f05c0b-8f2c-4b74-a5d2-c00aec445c57"      
#define APP_SECRET        "4b9fa934-ee9b-4fd0-8a7c-c4a3b9807804-e696b366-91f3-47a6-b2f9-c8f3489cf562"   

#include <BlynkSimpleEsp32.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <IRremote.h>
#define ir 14
#define Fan             "63dc918822e49e3cb5f77ff1"  

int ON_OFF;
int Speed;
int Timer1, Timer2;

char SSID[] = "semanz"; 
char PASSWORD[] = "33632407";
char AUTH[] = BLYNK_AUTH_TOKEN;

void setupWIFI() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected!");
  Blynk.begin(AUTH, SSID, PASSWORD);
}

void setupSinricPro() {   // Setting up Sinric Pro Devices
  SinricProSwitch& mySwitch1 = SinricPro[Fan];
  mySwitch1.onPowerState(onPowerState1);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  Serial.begin(9600);
  setupWIFI();
  IrSender.begin(ir);
  setupSinricPro();
}

void loop() {
  Blynk.run();
  SinricPro.handle();
}

bool onPowerState1(const String &deviceId, bool &state) {   // Sinric Pro Device 1
  if(state){
    uint32_t tRawData[] = { 0x84D02002, 0x553130 };
    IrSender.sendPulseDistanceWidthFromArray(38, 3450, 1750, 400, 1300, 400, 450, &tRawData[0], 56, PROTOCOL_IS_LSB_FIRST,100,15);
  }    
  else if (!state){
    uint32_t tRawData[] = { 0x84D02002, 0x553130 };
    IrSender.sendPulseDistanceWidthFromArray(38, 3450, 1750, 400, 1300, 400, 450, &tRawData[0], 56, PROTOCOL_IS_LSB_FIRST,100,15);
  }
  return true;
}

BLYNK_WRITE(V0) { //On & Off
  ON_OFF = param.asInt();
  if (ON_OFF == 1){
    uint32_t tRawData[] = { 0x84D02002, 0x553130 };
    IrSender.sendPulseDistanceWidthFromArray(38, 3450, 1750, 400, 1300, 400, 450, &tRawData[0], 56, PROTOCOL_IS_LSB_FIRST,100,15);
    Serial.println("ON OFF");
  }
  else{}
}

BLYNK_WRITE(V1) { //Timer 1 Hour
  Timer1 = param.asInt();
  if (Timer1 == 1){
    uint32_t tRawData[] = { 0x84D02002, 0x254130 };
    IrSender.sendPulseDistanceWidthFromArray(38, 3450, 1750, 400, 1300, 400, 450, &tRawData[0], 56, PROTOCOL_IS_LSB_FIRST,100,15);
  }
  else{}
}

BLYNK_WRITE(V2) { //Timer 3 Hours
  Timer2 = param.asInt();
  if (Timer2 == 1){
    uint32_t tRawData[] = { 0x84D02002, 0x274330 };
    IrSender.sendPulseDistanceWidthFromArray(38, 3450, 1750, 400, 1300, 400, 450, &tRawData[0], 56, PROTOCOL_IS_LSB_FIRST,100,15); 
  }
  else{}
}

BLYNK_WRITE(V3) { //Speed 1 to 3
  Speed = param.asInt(); 
  if (Speed == 1){
    uint32_t tRawData[] = { 0x84D02002, 0x452130 };
    IrSender.sendPulseDistanceWidthFromArray(38, 3400, 1800, 400, 1350, 400, 450, &tRawData[0], 56, PROTOCOL_IS_LSB_FIRST,100,15);
  }
  else if (Speed == 2){
    uint32_t tRawData[] = { 0x84D02002, 0x462230 };
    IrSender.sendPulseDistanceWidthFromArray(38, 3400, 1800, 400, 1350, 400, 450, &tRawData[0], 56, PROTOCOL_IS_LSB_FIRST,100,15);
  }
  else if (Speed == 3){
    uint32_t tRawData[] = { 0x84D02002, 0x472330 };
    IrSender.sendPulseDistanceWidthFromArray(38, 3400, 1800, 400, 1350, 400, 450, &tRawData[0], 56, PROTOCOL_IS_LSB_FIRST,100,15);    
  }
}

