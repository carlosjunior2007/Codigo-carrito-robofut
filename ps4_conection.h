#ifndef PS4_CONECTION_H
#define PS4_CONECTION_H

#include <Bluepad32.h>

// Variables y funciones relacionadas con el control PS4
extern const uint8_t targetMacAddress[6];
extern ControllerPtr myController;

void setupPS4Control();
void updatePS4Control();
void onGamepadConnected(ControllerPtr ctl);
void onGamepadDisconnected(ControllerPtr ctl);

#endif // PS4_CONTROL_H
