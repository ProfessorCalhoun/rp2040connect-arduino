//Arduino Nano only. Outputs PWM at baseband rate with Fc component

const byte ANTENNA = 11;
int state = 0;

void setup() 
{
  // set up Timer 1
  TCCR1A = _BV (COM1A0);  // toggle OC1A on Compare Match
  TCCR1B = _BV(WGM12) | _BV(CS10);   // CTC, no prescaler
  OCR1A =  9;       // compare A register value to 10 (zero relative)
}  // end of setup

//Communicate "SOS" in Morse Code
void loop() 
{
  if (state < 3){
    pinMode (ANTENNA, OUTPUT);
    delay (50);
  }else if (state >= 4 && state < 7){
    pinMode (ANTENNA, OUTPUT);
    delay (250);
  }else if (state < 10) {
    pinMode (ANTENNA, OUTPUT);
    delay (50);
  }else{
    delay (300);
  }
  if (state == 11){
    state = 0;
  }
  state++;
  pinMode (ANTENNA, INPUT);
  delay (300);
}  // end of loop
