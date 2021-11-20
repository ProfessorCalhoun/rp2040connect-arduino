#include <WiFiNINA.h>

const int SEGA = 12;
const int SEGB = 11;
const int SEGC = 10;
const int SEGD = 9;
const int SEGE = 8;
const int SEGF = 7;
const int SEGG = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(SEGA,OUTPUT);
  pinMode(SEGB,OUTPUT);
  pinMode(SEGC,OUTPUT);
  pinMode(SEGD,OUTPUT);
  pinMode(SEGE,OUTPUT);
  pinMode(SEGF,OUTPUT);
  pinMode(SEGG,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int count = 0;
  for(count = 0; count<16; count++){
    switch(count){
      case 0:
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,LOW);
          break;
      case 1:
          digitalWrite(SEGA,LOW);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,LOW);
          digitalWrite(SEGE,LOW);
          digitalWrite(SEGF,LOW);
          digitalWrite(SEGG,LOW);
          break;
      case 2:
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,LOW);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,LOW);
          digitalWrite(SEGG,HIGH);
          break;
      case 3:
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,LOW);
          digitalWrite(SEGF,LOW);
          digitalWrite(SEGG,HIGH);
          break;
      case 4:
          digitalWrite(SEGA,LOW);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,LOW);
          digitalWrite(SEGE,LOW);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
      case 5:
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,LOW);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,LOW);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
      case 6:
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,LOW);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
      case 7:
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,LOW);
          digitalWrite(SEGE,LOW);
          digitalWrite(SEGF,LOW);
          digitalWrite(SEGG,LOW);
          break;
      case 8:
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
      case 9:
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,LOW);
          digitalWrite(SEGE,LOW);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
      case 10: //A
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,LOW);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
      case 11: //B
          digitalWrite(SEGA,LOW);
          digitalWrite(SEGB,LOW);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
      case 12: //C
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,LOW);
          digitalWrite(SEGC,LOW);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,LOW);
          break;
      case 13: //D
          digitalWrite(SEGA,LOW);
          digitalWrite(SEGB,HIGH);
          digitalWrite(SEGC,HIGH);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,LOW);
          digitalWrite(SEGG,HIGH);
          break;
      case 14: //E
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,LOW);
          digitalWrite(SEGC,LOW);
          digitalWrite(SEGD,HIGH);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
      case 15: //F
          digitalWrite(SEGA,HIGH);
          digitalWrite(SEGB,LOW);
          digitalWrite(SEGC,LOW);
          digitalWrite(SEGD,LOW);
          digitalWrite(SEGE,HIGH);
          digitalWrite(SEGF,HIGH);
          digitalWrite(SEGG,HIGH);
          break;
    }
    delay(1000);
  }
  
}
