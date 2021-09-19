/*
 * Author: Professor DM Calhoun
 * Purpose: This code is an example of a simple control system using an
 * ultrasonic distance sensor and some DC motors controlled with a L293D
 * H-bridge motor driver
 */

#include "Ultrasonic.h"
#include "WiFiNINA.h"

Ultrasonic ultrasonic(6); //D6 on RP2040 Connect/Nano
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int potPin = 0;

void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop()
{
  //Create variable to handle distance and direction
  long range_cm;
  boolean reverse;
  
  //Read a voltage from a potentiometer to dictate speed
  int speed = analogRead(potPin) / 4;
  
  //Determine direction based on UD densor
  range_cm = ultrasonic.MeasureInCentimeters();
  //Correct for ultra-small distance error
  if (range_cm > 500){
    range_cm = 0;
  }
  Serial.print("The distance to obstacles in front is (cm): ");
  Serial.println(range_cm);
  //simple state machine to change direction based on distance
  if (range_cm > 7){
    //move forward
    reverse = false;
    //set comms status via LED and UART
    Serial.println("Moving forward!");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,LOW);
  }else if ((range_cm <= 7) && (range_cm > 3)){
    //stay in place
    speed = 0;
    reverse = false;
    //set comms status via LED and UART
    Serial.println("Stopped.");
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDB,LOW);
  }else if(range_cm <= 3){
    //move backward
    reverse = true;
    //set comms status via LED and UART
    Serial.println("Moving backward!");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDB,HIGH);
  }
  
  //Set motor config based on other readings
  setMotor(speed, reverse);
  delay(250);
}

void setMotor(int speed, boolean reverse)
{
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, ! reverse);
  digitalWrite(in2Pin, reverse);
}
