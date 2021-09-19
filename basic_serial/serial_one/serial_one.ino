/*
 * Author: Professor DM Calhoun
 * Purpose: This code uses the Serial communication functionality of any Arduino-compatible board to send a single message every 1 second.
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello my name is Prof. C and I am communicating over a serial connection!");
  delay(1000);
}
