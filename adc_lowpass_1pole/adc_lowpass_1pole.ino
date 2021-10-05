#include <WiFiNINA.h>
//Could use audacity to generate an audio signal
//Could use sig-gen
int sensorPin = A0;

//we need at least 3 samples in time to exist to compute filtered data
float xn1 = 0;
float yn1 = 0;
int k = 0;

void setup() {
  Serial.begin(115200);
   
}

void loop() {
  // Wait for samples to be read
  int reading = analogRead(sensorPin);
  float xn = (float)reading*5/1024; // convert to a voltage
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
  /*float b[] = {0.03778605, 0.03778605};
  float a[] = {0.92442789};*/
  //100Hz filter, based on 20kHz sampling freq
  /*float b[] = {0.01546504, 0.01546504};
  float a[] = {0.96906992};*/
  //10Hz filter, based on 20kHz sampling freq
  /*float b[] = {0.00156833, 0.00156833};
  float a[] = {0.99686333};*/
  //5Hz filter, based on 20kHz sampling freq
  float b[] = {0.00078478, 0.00078478};
  float a[] = {0.99843044};
  
  float yn = a[0]*yn1 + b[0]*xn + b[1]*xn1;

  //This delay is the main contributor to sampling frequency
  delayMicroseconds(50);
  
  xn1 = xn;
  yn1 = yn;
  
  if(k % 60 == 0) //send fewer samples as to not mess with sampling frequency
  {
    //Print out samples
    Serial.print(2*xn);
    Serial.print(" ");
    Serial.println(2*yn);
  }
  k = k+1;
      
}
