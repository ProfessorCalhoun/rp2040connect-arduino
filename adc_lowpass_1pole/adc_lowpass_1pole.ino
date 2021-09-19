#include <WiFiNINA.h>
//Could use audacity to generate an audio signal
//Could use sig-gen
int sensorPin = A0;

//we need at least 3 samples in time to exist to compute filtered data
float xn1 = 0;
float yn1 = 0;
int k = 0;

void setup() {
  Serial.begin(9600);
  //wait for serial port to open before code works
  while (!Serial);
  
}

void loop() {
  // Wait for samples to be read
  float xn = analogRead(sensorPin);
  //Filtering - second order Butterworth
  //5kHz filter, based on 20kHz sampling freq
  /*float b[] = {0.43990085, 0.43990085};
  float a[] = {0.12019831};*/
  //1kHz filter, based on 20kHz sampling freq
  /*float b[] = {0.13575525, 0.13575525};
  float a[] = {0.7284895};*/
  //500Hz filter, based on 20kHz sampling freq
  /*float b[] = {0.07282051, 0.07282051};
  float a[] = {0.85435899};*/
  //250Hz filter, based on 20kHz sampling freq
  float b[] = {0.03778605, 0.03778605};
  float a[] = {0.92442789};
  float yn = a[1]*yn1 + b[1]*xn + b[2]*xn1;


  if(k % 10 == 0) //send fewer samples as to not mess with sampling frequency
  {
    //Print out samples
    Serial.print(2*xn);
    Serial.print(" ");
    Serial.println(2*yn);
  }
  k = k+1;
      
  // Make sample rate of main loop something usable for hifi filtering - 20kHz
  delayMicroseconds(50);

  xn1 = xn;
  yn1 = yn;
}
