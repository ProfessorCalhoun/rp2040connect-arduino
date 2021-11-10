/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  
  myservo.write(0+1); // write an initial position prior to creating servo object. Servo will move there once object is created
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
  delay(1000);
  Serial.println("Starting up...");
}

void loop() {
  
  myservo.write(45);              // tell servo to go to position in variable 'pos'
  Serial.println("Moved to 45");
  delay(1000);
  
  myservo.write(90);              // tell servo to go to position in variable 'pos'
  Serial.println("Moved to 90");
  delay(1000);
  
  myservo.write(135);              // tell servo to go to position in variable 'pos'
  Serial.println("Moved to 135");
  delay(1000);

  myservo.write(180-1);              // tell servo to go to position in variable 'pos'
  Serial.println("Moved to 180");
  delay(1000);

  myservo.write(135);              // tell servo to go to position in variable 'pos'
  Serial.println("Moved to 135");
  delay(1000);

  myservo.write(90);              // tell servo to go to position in variable 'pos'
  Serial.println("Moved to 190");
  delay(1000);

  myservo.write(45);              // tell servo to go to position in variable 'pos'
  Serial.println("Moved to 45");
  delay(1000);

  myservo.write(0+1);              // tell servo to go to position in variable 'pos'
  Serial.println("Reset to 0");
  delay(1000);
}
