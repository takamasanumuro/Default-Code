#include <auxiliary.h>

void setup() {
  Serial.begin(115200);
  wifiConfig();
  OTASetup();
  hwTimerSetup();
}

void loop() {

  serialCommands();
  ArduinoOTA.handle();
}



/*
DEBUG.PRINTLN
DEBUG.PRINTF
FINISH WIFIHANDLER
FINISH ESPDASH
RECEIVE LORA INFO FROM GATEWAY


*/