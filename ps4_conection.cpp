#include "ps4_conection.h"
#include <Arduino.h>

// Dirección MAC del control objetivo
const uint8_t targetMacAddress[6] = {0x00, 0x22, 0x68, 0xDF, 0xB1, 0xD5};
ControllerPtr myController = nullptr;

bool compareMacAddress(const uint8_t* mac1, const uint8_t* mac2) {
  for (int i = 0; i < 6; i++) {
    if (mac1[i] != mac2[i]) {
      return false;
    }
  }
  return true;
}

void onGamepadConnected(ControllerPtr ctl) {
  ControllerProperties properties = ctl->getProperties();
  const uint8_t* macAddress = properties.btaddr;

  Serial.printf("Control conectado - Dirección MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                macAddress[0], macAddress[1], macAddress[2],
                macAddress[3], macAddress[4], macAddress[5]);

  if (compareMacAddress(macAddress, targetMacAddress)) {
    Serial.println("Control objetivo conectado");
    myController = ctl;
  } else {
    Serial.println("Control desconocido conectado, desconectando...");
    ctl->disconnect();
  }
}

void onGamepadDisconnected(ControllerPtr ctl) {
  if (myController == ctl) {
    Serial.println("Control objetivo desconectado");
    myController = nullptr;
  }
}

void setupPS4Control() {
    BP32.setup(&onGamepadConnected, &onGamepadDisconnected);
    BP32.enableVirtualDevice(false);
}

void updatePS4Control() {
    BP32.update();
}
