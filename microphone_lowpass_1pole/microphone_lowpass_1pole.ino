#include <WiFiNINA.h>
#include <PDM.h>

// default number of output channels
static const char channels = 1;

// default PCM output frequency
static const int frequency = 16000;

// Buffer to read samples into, each sample is 16-bits
short sampleBuffer[512];

// Number of audio samples read
volatile int samplesRead;

//we need at least 3 samples in time to exist to compute filtered data
float xn1 = 0;
float yn1 = 0;
int k = 0;

void setup() {
  Serial.begin(9600);
  
  while (!Serial);
  // Configure the data receive callback
  PDM.onReceive(onPDMdata);

  // Optionally set the gain
  // Defaults to 20 on the BLE Sense and -10 on the Portenta Vision Shields
  // PDM.setGain(30);

  // Initialize PDM with:
  // - one channel (mono mode)
  // - a 16 kHz sample rate for the Arduino Nano 33 BLE Sense
  // - a 32 kHz or 64 kHz sample rate for the Arduino Portenta Vision Shields
  if (!PDM.begin(channels, frequency)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }
}

void loop() {
  // Wait for samples to be read
  if (samplesRead) {
    for (int i = 0; i < samplesRead; i++) {
      float xn = sampleBuffer[i];
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
      //10Hz filter, based on 20kHz sampling freq
      /*float b[] = {0.00156833, 0.00156833};
      float a[] = {0.99686333};*/
      //5Hz filter, based on 20kHz sampling freq
      float b[] = {0.00078478, 0.00078478};
      float a[] = {0.99843044};
  
      float yn = a[0]*yn1 + b[0]*xn + b[1]*xn1;

      if(k % 10 == 0) //send fewer samples as to not mess with sampling frequency
      {
        //Print out samples
        Serial.print(2*xn);
        Serial.print(" ");
        Serial.println(2*yn);
      }
      k = k+1;
      
      // Make sample rate of main loop something usable for filtering
      delayMicroseconds(50);
    
      xn1 = xn;
      yn1 = yn;
    }  
  }
  
  // Clear the read count
  samplesRead = 0;
}

/**
   Callback function to process the data from the PDM microphone.
   NOTE: This callback is executed as part of an ISR.
   Therefore using `Serial` to print messages inside this function isn't supported.
 * */
void onPDMdata() {
  // Query the number of available bytes
  int bytesAvailable = PDM.available();

  // Read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}
