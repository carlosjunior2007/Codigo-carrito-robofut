#ifndef PWM_MOTORS_H
#define PWM_MOTORS_H

void setupPWMmotors();

const int pwmPin1 = 32;  // Pin para la primera señal PWM
const int pwmPin2 = 26;  // Pin para la segunda señal PWM

const int pwmChannel1 = 0;
const int pwmChannel2 = 1; // Segundo canal PWM

const int pwmFrequency = 5000;  // Frecuencia PWM en Hz
const int pwmResolution = 10;   // Resolución PWM (0-1023)

#endif // PS4_CONTROL_H