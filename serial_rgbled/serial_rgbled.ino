/*
 * This is a block comment!
 * Every code/document/file should have a description that includes its author and purpose...
 * Author: Professor DM Calhoun
 * Purpose: This code combines serial output functionality with a sequence of RGB LED blinking
 */

// This is a line comment!

// Compiler directives go at the top of your file. These are references to other files and libraries that the code uses to achieve its functionality.
#include <WiFiNINA.h>
// Variables may also go at the top of your file. 
byte state = 0x01;

/*
 * When it comes to this type of programming, operations implemented in your code (function calls, arithmetic, pin toggling, etc.) execute serially. 
 * This "setup" function is the first portion of your code to execute. It is meant to do as described: set up any necessary items to make the main body of our code execute successfully.
 */
void setup() {
  //Sets pin mode to outputs for the three WiFiNiNA pins that control the RGB LED
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  //Initializes the serial interface with a baud rate. 
  Serial.begin(9600);
}

// put your main code here, to run repeatedly:
void loop() {

  Serial.println("Hello my name is Prof. C and I have tested this board!");
  
  //use bitwise AND here to mask the "state" variable
  if(state & 0x01){
    digitalWrite(LEDR,HIGH);
  }else{
    digitalWrite(LEDR,LOW);
  }
  if(state & 0x02){
    digitalWrite(LEDG,HIGH);
  }else{
    digitalWrite(LEDG,LOW);
  }
  if(state & 0x04){
    digitalWrite(LEDB,HIGH);
  }else{
    digitalWrite(LEDB,LOW);
  }
  
  Serial.print("State: ");
  Serial.println(state);
  state = state+0x01;
  
  if (state == 0x08){
    state = 0x01;
  }
  delay(500);
  
}
