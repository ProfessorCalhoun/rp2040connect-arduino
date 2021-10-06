/*
 * Author: Professor DM Calhoun
 * Purpose: This code maps a PWM signal to a PWM-capable output pin using a user
 * input over a serial connection.
 */
#include <WiFiNINA.h>
int pwm_out = A2;
int pwm_value = 0;
String str = "";

void setup() {
  pinMode(pwm_out, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  if(Serial.available() > 0){
      //Read input string
      Serial.print("Input new PWM value (0-255): ");
      str = Serial.readStringUntil('\n');
      Serial.println(str);
      delay(100);
      pwm_value = str.toInt();
      Serial.println("New PWM value: " + String(pwm_value));
  }
  analogWrite(pwm_out,pwm_value); 

}
