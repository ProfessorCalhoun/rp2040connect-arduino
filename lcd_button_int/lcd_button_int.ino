/*
 * Author: Professor DM Calhoun
 * Description: Employs the LiquidCrystal library and a GPIO push button - with an interrupt - to 
 * demonstrate less processing delay compared to without an interrupt
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
#define BUTTON_INT_TRIGGERED true
volatile int button_state = LOW;
volatile int button_prev = LOW;
volatile int button_count = 0;

volatile bool button_isr_flag = !BUTTON_INT_TRIGGERED;

volatile unsigned long last_debounce = 0;
unsigned long debounce_delay = 100;
unsigned long emulated_process_delay = 250;

volatile int reading = LOW;

void button_isr(){
  //if we have generated an ISR, proceed to processing further pushes as valid events
  if (button_isr_flag == !BUTTON_INT_TRIGGERED){
    button_isr_flag = BUTTON_INT_TRIGGERED;
  //all events processed below when valid
  }else{
    reading = (digitalRead(BUTTON_PIN));
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
          //clear ISR flag when event is successfully processed (flag consumed)
          button_isr_flag = !BUTTON_INT_TRIGGERED;
        }
      }
    }
    button_prev = button_state;  
  }
}

void setup() {
  // initialize button
  pinMode(BUTTON_PIN, INPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_isr, CHANGE);
  
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

  digitalWrite(LED_PIN, digitalRead(BUTTON_PIN));

  //code to handle button debounce and logic moved to an ISR!

  //Delay implemented here to emulate some process that takes a specified amount of time and blocks other functions.
  delay(emulated_process_delay);
}
