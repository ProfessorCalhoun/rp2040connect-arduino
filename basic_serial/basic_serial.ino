/*
 * Author: Prof. DM Calhoun
 * Purpose: A basic serial/UART printing example.
 */

//Initial routine that runs once, used for initial setup
void setup() {
  Serial.begin(9600); //Initialize serial/UART interface
}

//Loops continuously and is the main "body" of your code
void loop() {
  Serial.println("Insert custom message here!"); //Print with CR/LF
  delay(1000); //Delay in milliseconds
}
