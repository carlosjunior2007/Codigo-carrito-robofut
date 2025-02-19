#include "Control.h"
#include "ps4_conection.h"
#include "pwm_motors.h"

void setupControl(){
  setupPS4Control();             // Configura el control PS4
  setupPWMmotors();              // Configura los motores

  // Configurar pines para dirección de motores como salida
  pinMode(phPin, OUTPUT);
  pinMode(nSleep, OUTPUT);
  pinMode(phPin2, OUTPUT);
  pinMode(nSleep2, OUTPUT);

  // Habilitamos ambos motores
  digitalWrite(nSleep, LOW);
  digitalWrite(nSleep2, LOW);
}

void loopControl() {
  updatePS4Control();  // Actualizamos el estado del control PS4

  if (myController && myController->isConnected()) {
    digitalWrite(nSleep, HIGH);
    digitalWrite(nSleep2, HIGH);

    bool l = myController->l1(); // Boton superior izquierdo
    bool r = myController->r1(); // Boton superior derecho

    if (l && !r) { // Si el boton superior izquierdo esta presionado y el derecho no esta presionado
      digitalWrite(phPin, HIGH); // Girar a la izquierda
      digitalWrite(phPin2, LOW);

      ledcWrite(pwmChannel1, 1023);
      ledcWrite(pwmChannel2, 1023);
    } else if (r && !l) { // Si el boton superior derecho esta presionado y el izquierdo no esta presionado
      digitalWrite(phPin, LOW); // Girar a la derecha
      digitalWrite(phPin2, HIGH);

      ledcWrite(pwmChannel1, 1023);
      ledcWrite(pwmChannel2, 1023);
    } else { // Si ninguno de los dos botones superiores esta presionado, utiliza los controles convencionales

      // Leer valores de los gatillos y joystick izquierdo
      int leftX = myController->axisX();  // Joystick para dirección
      int throttleValue = map(myController->throttle(), 0, 1020, 0, 1023);  // Gatillo derecho
      int brakeValue = map(myController->brake(), 0, 1020, 0, 1023);        // Gatillo izquierdo
      
      // Aplicar deadzone al joystick y gatillos
      if (abs(leftX) < DEADZONE) leftX = 0;  // Deadzone para joystick
      if (throttleValue < DEADZONE) throttleValue = 0; // Deadzone para throttle
      if (brakeValue < DEADZONE) brakeValue = 0;       // Deadzone para brake
  
      // Ajustar velocidad base en función del acelerador y freno
      int velocidadBase = throttleValue - brakeValue;
  
      // **Detener motores si no hay aceleración ni freno**
      if (velocidadBase == 0 || (throttleValue == 0 && brakeValue == 0 )) {
        ledcWrite(pwmChannel1, 0);  // Detener motor A
        ledcWrite(pwmChannel2, 0);  // Detener motor B
        Serial.println("Motores detenidos (velocidadBase = 0)");
        return;
      }
  
      // Cambiar dirección según velocidad base (adelante o atrás)
      if (velocidadBase > 0) {
        digitalWrite(phPin, HIGH);   // Motor A avanza
        digitalWrite(phPin2, HIGH); // Motor B avanza
      } else if (velocidadBase < 0) {
        digitalWrite(phPin, LOW);   // Motor A retrocede
        digitalWrite(phPin2, LOW); // Motor B retrocede
        velocidadBase = abs(velocidadBase); // Convertir a positivo para PWM
      }
  
      // Mapear joystick para controlar giros progresivos
      int ajusteDireccion = map(leftX, -508, 512, -512, 512);  // Valores negativos: giro izquierda, positivos: giro derecha
  
      // Calcular velocidades finales para cada motor
      int velocidadMotorA = constrain(velocidadBase + ajusteDireccion, 0, 1023);
      int velocidadMotorB = constrain(velocidadBase - ajusteDireccion, 0, 1023);
  
      // Enviar señal PWM a los motores
      ledcWrite(pwmChannel1, velocidadMotorA);
      ledcWrite(pwmChannel2, velocidadMotorB);
    }

    // Mostrar valores en el monitor serie
    Serial.print("Throttle: ");
    Serial.print(throttleValue);
    Serial.print(" Brake: ");
    Serial.print(brakeValue);
    Serial.print(" Joystick Left X: ");
    Serial.print(leftX);
    Serial.print(" Motor A PWM: ");
    Serial.print(velocidadMotorA);
    Serial.print(" Motor B PWM: ");
    Serial.print(velocidadMotorB);
    Serial.println();
    
  } else {
    // Si no hay un control conectado, detener los motores
    ledcWrite(pwmChannel1, 0);
    ledcWrite(pwmChannel2, 0);
    digitalWrite(nSleep, LOW);  // Deshabilitar motor A
    digitalWrite(nSleep2, LOW); // Deshabilitar motor B
    Serial.println("Control desconectado. Motores detenidos.");
  }

  delay(1);
}

