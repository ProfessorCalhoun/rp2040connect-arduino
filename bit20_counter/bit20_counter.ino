/*
 * Author: Professor Calhoun
 * Description: 5-bit counter with increments of 5-bit value inside of a single main 
 * program loop iteration. Utilizes bitRead tyo parse our 5 bits of Arduino int structure 
 * (might be 16-bit int)
 */

int BITA = 6;//D2
int BITB = 5;//D3
int BITC = 4;//D4
int BITD = 3;//D5
int BIT0 = 11;//D6
int BIT1 = 10;//D6
int BIT2 = 9;//D6
int BIT3 = 8;//D6
int BIT4 = 7;//D6

int counter = 0;
int ii = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(BITA,OUTPUT);
  pinMode(BITB,OUTPUT);
  pinMode(BITC,OUTPUT);
  pinMode(BITD,OUTPUT);
  pinMode(BIT0,OUTPUT);
  pinMode(BIT1,OUTPUT);
  pinMode(BIT2,OUTPUT);
  pinMode(BIT3,OUTPUT);
  pinMode(BIT4,OUTPUT);

  Serial.begin(9600);
}



void loop() {
  
  
  if (counter < 5){
    Serial.print("Group1");
    digitalWrite(BITA, HIGH);
    digitalWrite(BITB, LOW);
    digitalWrite(BITC, LOW);
    digitalWrite(BITD, LOW); 
  }else if (counter < 10){
    Serial.print("Group2");
    digitalWrite(BITA, LOW);
    digitalWrite(BITB, HIGH);
    digitalWrite(BITC, LOW);
    digitalWrite(BITD, LOW);
  }else if (counter < 15){
    Serial.print("Group3");
    digitalWrite(BITA, LOW);
    digitalWrite(BITB, LOW);
    digitalWrite(BITC, HIGH);
    digitalWrite(BITD, LOW);
  }else if (counter < 20){
    Serial.print("Group4");
    digitalWrite(BITA, LOW);
    digitalWrite(BITB, LOW);
    digitalWrite(BITC, LOW);
    digitalWrite(BITD, HIGH);
  }
  digitalWrite(BIT0, not(bitRead(ii,0)));
  digitalWrite(BIT1, not(bitRead(ii,1)));
  digitalWrite(BIT2, not(bitRead(ii,2)));
  digitalWrite(BIT3, not(bitRead(ii,3)));
  digitalWrite(BIT4, not(bitRead(ii,4)));
  Serial.print(not(bitRead(ii,0)));
  Serial.print(not(bitRead(ii,1)));
  Serial.print(not(bitRead(ii,2)));
  Serial.print(not(bitRead(ii,3)));
  Serial.println(not(bitRead(ii,4)));
  if (ii > 8){
    ii = 1;
  }else{
    ii = ii<<1;  
  }
  
  if (counter == 19){
    counter = 0;
  }else{
    counter++;    
  }
  
  
  delay(250); 
  
    
  
}
