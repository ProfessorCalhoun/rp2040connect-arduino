/* Author: Prof. D.M. Calhoun
 * Description: 4-bit driving logic for a SN74LS46N 7-segment BCD driver IC. 
 * Tested with this 7-seg (common anode): https://www.mouser.com/datasheet/2/143/everlight_evers01077-1-1734957.pdf
 * Tested with this BCD driver: https://www.ti.com/lit/gpn/SN5447A
 * Revision: 11/1/2021
 */

const byte BCD_A = 9;
const byte BCD_B = 10;
const byte BCD_C = 11;
const byte BCD_D = 12;

int counter = 0;

void setup() {
  //Set up output pins from RP2040 Connect to SN74LS47N
  pinMode(BCD_A,OUTPUT);
  pinMode(BCD_B,OUTPUT);
  pinMode(BCD_C,OUTPUT);
  pinMode(BCD_D,OUTPUT);
}

void loop() {
  //Mask bit of interest. If the counter reflects a 1 in that position the statement will evaluation to TRUE
  digitalWrite(BCD_A,(counter & 0x01));
  digitalWrite(BCD_B,(counter & 0x02));
  digitalWrite(BCD_C,(counter & 0x04));
  digitalWrite(BCD_D,(counter & 0x08));
  delay(1000);
  //reset the count when necessary rather than roll over
  if (counter == 9){
    counter = 0;
  }else{
    counter++;
  }

}
