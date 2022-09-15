
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#endif
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

//random test gibberish here

void OTASetup();
void wifiConfig();
void hwTimerSetup();
void serialCommands();
extern void hwTimerBack();

class IO{

private:
    
    
    
    bool _state;
    uint8_t _mode;
    uint8_t _pin;
public:
    IO(uint8_t pin,uint8_t mode);
    void on();
    void off();
    void toggle();
    void blink(uint16_t interval);
    bool state();
    void safety(uint32_t safetyInterval);
    uint16_t read();
    void setMode(uint8_t mode);
    uint8_t pin();
    float value;
    unsigned long _timer;
    unsigned long timer();
    
};
