// test code for Grove - Sound Sensor
// Prof. DMC 9/13/21
 
const int pinAdc = A0;
 
void setup()
{
    Serial.begin(9600);
    Serial.println("Grove - Light Sensor Test v1.2...");
}
 
void loop()
{
    //Create variable to store value, larger than int
    long sum = 0;
    //Add 32 samples of this reading together
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pinAdc);
    }
    //divide by 32 (2^5=32)
    sum >>= 5;
 
    Serial.println(sum);
    delay(10);
}
