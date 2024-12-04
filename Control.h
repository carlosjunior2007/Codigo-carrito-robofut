#ifndef CONTROL_H
#define CONTROL_H

// Pines para dirección y control de los motores
const int phPin = 33;     // Dirección motor A
const int nSleep = 25;    // Habilitar motor A
const int phPin2 = 27;    // Dirección motor B
const int nSleep2 = 14;   // Habilitar motor B
const int DEADZONE = 50;  // Rango muerto para el joystick

void setupControl();
void loopControl();

#endif