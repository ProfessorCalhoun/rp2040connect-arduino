/*
 * Author: Professor DM Calhoun
 * Description: Employs the LiquidCrystal library and a GPIO push button to demonstrate processing delay 
 * associated with multiple peripherals.
 */
 //Include WiFiNINA for appropriate GPIO access
#include <WiFiNINA.h>

// LCD initialization
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int LED_PIN = 8;

//button initialization
const int BUTTON_PIN = 7;
int button_state = LOW;
int button_prev = LOW;
int button_count = 0;

unsigned long last_debounce = 0;
unsigned long debounce_delay = 100;
unsigned long emulated_process_delay = 250;

int reading = LOW;

void setup() {
  // initialize button
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Seconds: ");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(9, 0);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

  lcd.setCursor(0, 1);
  lcd.print("Presses: ");
  lcd.setCursor(9, 1);
  
  lcd.print(button_count);

  reading = (digitalRead(BUTTON_PIN));
  digitalWrite(LED_PIN, reading);
  
  // check if last button press occurred sufficiently long ago
  if (button_state != button_prev){
    last_debounce = millis();
  }

  if ((millis() - last_debounce) > debounce_delay){
    
    //check if button was pressed and log a press if last event was not a button press
    if (reading != button_state){
      button_state = reading;
      if (button_state == HIGH){
        button_count++;        
      }
    }
  }
  button_prev = button_state;

  //Delay implemented here to emulate some process that takes a specified amount of time and blocks other functions.
  delay(emulated_process_delay);
}
