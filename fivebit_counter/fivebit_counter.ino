/*
 * Author: Professor Calhoun
 * Description: 5-bit counter with increments of 5-bit value inside of a single main 
 * program loop iteration. Utilizes bitRead tyo parse our 5 bits of Arduino int structure 
 * (might be 16-bit int)
 */

int BIT0 = 2;//D2
int BIT1 = 3;//D3
int BIT2 = 4;//D4
int BIT3 = 5;//D5
int BIT4 = 6;//D6

void setup() {
  // put your setup code here, to run once:
  pinMode(BIT0,OUTPUT);
  pinMode(BIT1,OUTPUT);
  pinMode(BIT2,OUTPUT);
  pinMode(BIT3,OUTPUT);
  pinMode(BIT4,OUTPUT);
}

void loop() {
  
  int num = 0;

  while(num < 32){
    digitalWrite(BIT0, bitRead(num,0));
    digitalWrite(BIT1, bitRead(num,1));
    digitalWrite(BIT2, bitRead(num,2));
    digitalWrite(BIT3, bitRead(num,3));
    digitalWrite(BIT4, bitRead(num,4));
    num++; 
    delay(500); // wait 1 ms
  }
}
