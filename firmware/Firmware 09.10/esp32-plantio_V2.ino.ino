/***************Inclusão da Biblioteca criada****************/
#include "leituraSensores.h"

#define POLL_DELAY 200

void setup() {
  setupSensors();
}

void loop() {
  String serialCommand;

  while (Serial.available() > 0) {
    char serialChar = Serial.read();
    serialCommand += serialChar;

    if (serialChar == '\n') {
      processCommand(serialCommand);
      serialCommand = "";
    }
  }

  delay(POLL_DELAY);
}
