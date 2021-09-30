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
  //Filtering - first order highpass
  //5kHz filter, based on 20kHz sampling freq
  /*float b[] = ;
  float a[] = ;*/
  //1kHz filter, based on 20kHz sampling freq
  /*float b[] = ;
  float a[] = ;*/
  //500Hz filter, based on 20kHz sampling freq
  /*float b[] = ;
  float a[] = ;*/
  //250Hz filter, based on 20kHz sampling freq
  /*float b[] = ;
  float a[] = ;*/
  //10Hz filter, based on 20kHz sampling freq
  /*float b[] = ;
  float a[] = ;*/
  //5Hz filter, based on 20kHz sampling freq
  float b[] = {0.99921522, -0.99921522};
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
