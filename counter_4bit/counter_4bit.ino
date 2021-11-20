/*
 * Author: Prof. DM Calhoun
 * Purpose: 4-bit counter
 */

#include <WiFiNINA.h>

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

int count = 0;

// the loop function runs over and over again forever
void loop() {
  if (count<15){
    
    count++;
  }else{
    count=0;
  }
  Serial.println(count);
  digitalWrite(12,(count & 0x01));
  digitalWrite(11,(count & 0x02));
  digitalWrite(10,(count & 0x04));
  digitalWrite(9,(count & 0x08));  
  delay(50);
}
