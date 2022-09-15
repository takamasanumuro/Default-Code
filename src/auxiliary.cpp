#include "auxiliary.h"

hw_timer_t *timer=NULL;
const char* ssid = "espnet";
const char* password = "12345678";



void wifiConfig(){
  pinMode(LED_BUILTIN,OUTPUT);
  int counter=0;
  unsigned long previousTime=0;

  WiFi.mode(WIFI_STA);
  Serial.println("Booting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {

    if(millis()-previousTime>500){
      previousTime=millis();
      Serial.printf("Connection attempt: %d\n",counter);
      counter++;
      if(counter>10){
      Serial.println("Connection failed");
      ESP.restart();
    }
    }
    
  }
}

void hwTimerSetup(){
  pinMode(LED_BUILTIN,OUTPUT);
  timer=timerBegin(0,80,true);
  timerAttachInterrupt(timer,&hwTimerBack,true);
  timerAlarmWrite(timer,1e6,true);
  timerAlarmEnable(timer);
  
}


IRAM_ATTR void hwTimerBack(){
  
  if(WiFi.status()!=WL_CONNECTED){
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  }
  else{
    digitalWrite(LED_BUILTIN,HIGH);
  } 
  
}


void serialCommands(){
  if(Serial.available()){
    char command=Serial.read();
    switch(command){
      case '0':
        Serial.printf("Off\n");
        WiFi.disconnect();
        break;
      case '1':
        Serial.printf("On\n");
        WiFi.begin(ssid,password);
        while(WiFi.status()!=WL_CONNECTED){
          delay(100); Serial.printf("|");
        }
        Serial.println("Ready");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        break;
      case '2':
        digitalWrite(LED_BUILTIN,HIGH);
        break;
      case '3':
        digitalWrite(LED_BUILTIN,LOW);
        break;
      case '4':
        digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
        break;
    }
    
  }
}


void OTASetup(){
    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}