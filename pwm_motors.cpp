#include "pwm_motors.h"
#include <Arduino.h>

void setupPWMmotors() {
  ledcSetup(pwmChannel1, pwmFrequency, pwmResolution);
  ledcAttachPin(pwmPin1, pwmChannel1);

  ledcSetup(pwmChannel2, pwmFrequency, pwmResolution);
  ledcAttachPin(pwmPin2, pwmChannel2);
}