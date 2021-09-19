#include <WiFiNINA.h>
//Could use audacity to generate an audio signal
//Could use sig-gen
int sensorPin = A0;

//we need at least 3 samples in time to exist to compute filtered data
float x[] = {0,0,0};
float y[] = {0,0,0};
int k = 0;

void setup() {
  Serial.begin(9600);
  //wait for serial port to open before code works
  while (!Serial);
  
}

void loop() {
  // Wait for samples to be read
  x[0] = analogRead(sensorPin);
  //Filtering - second order Butterworth
  //5kHz filter, based on 20kHz sampling freq
  /*float b[] = {0.2261537, 0.4523075, 0.2261537};
  float a[] = {0.28094575, -0.18556054};*/
  //1kHz filter, based on 20kHz sampling freq
  /*float b[] = {0.01978958, 0.03957917, 0.01978958};
  float a[] = {1.56450399, -0.64366232};*/
  //500Hz filter, based on 20kHz sampling freq
  /*float b[] = {0.00552119, 0.01104239, 0.00552119};
  float a[] = {1.77908235, -0.80116713};*/
  //250Hz filter, based on 20kHz sampling freq
  float b[] = {0.00145886, 0.00291771, 0.00145886};
  float a[] = {1.88908996, -0.89492539};
  y[0] = a[0]*y[1] + a[1]*y[2] +
               b[0]*x[0] + b[1]*x[1] + b[2]*x[2];

  if(k % 10 == 0) //send fewer samples as to not mess with sampling frequency
  {
    //Print out samples
    Serial.print(2*x[0]);
    Serial.print(" ");
    Serial.println(2*y[0]);
  }
  k = k+1;
      
  // Make sample rate of main loop something usable for hifi filtering - 20kHz
  delayMicroseconds(50);

  for(int i = 1; i >= 0; i--){
    x[i+1] = x[i]; // store xi
    y[i+1] = y[i]; // store yi
  }
}
