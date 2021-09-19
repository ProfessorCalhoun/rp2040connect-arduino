// constants won't change. They're used here to set pin numbers:
const int vibSense = 2;     // the number of the pushbutton pin
const int orangeLED =  13;      // the number of the buzzer pin
 
// variables will change:
int vibState = 0;         // variable for reading the pushbutton status
 
void setup() {
  // initialize the LED pin as an output:
  pinMode(orangeLED, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(vibSense, INPUT);
}
 
void loop() {
  // read the state of the pushbutton value:
  vibState = digitalRead(vibSense);
 
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (vibState == HIGH) {
    // turn LED on:
    digitalWrite(orangeLED, LOW);
  } else {
    // turn LED off:
    digitalWrite(orangeLED, HIGH);
  }
}
