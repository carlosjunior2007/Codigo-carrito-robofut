#include <Arduino.h>
#include "ps4_conection.h"
#include "Control.h"

void setup() {
  Serial.begin(115200);
  setupControl();
}

void loop() {
  loopControl();
}

