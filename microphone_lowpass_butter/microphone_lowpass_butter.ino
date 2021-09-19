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
float x[] = {0,0,0};
float y[] = {0,0,0};
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
      x[0] = sampleBuffer[i];
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
      
      // Make sample rate of main loop something usable for filtering
      delayMicroseconds(50);
    
      for(int i = 1; i >= 0; i--){
        x[i+1] = x[i]; // store xi
        y[i+1] = y[i]; // store yi
      }
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
