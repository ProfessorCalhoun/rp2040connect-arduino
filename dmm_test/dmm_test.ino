const int adc1_reg = A1;
float calibrated_resistance = 986.9;
float avolt_ref = 3.259;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor blocking
  while(!Serial);
}

void loop() {
  
  long adc_reading = 0;
  float voltage_average_value = 0;
  float resistance = 0;
  
  for(int ss = 0; ss < 32; ss++){
    adc_reading += analogRead(adc1_reg);
  }
  adc_reading >>= 5; //divide by 32
  voltage_average_value = adc_reading*0.00322;
  
  //calculate resistance
  resistance = calibrated_resistance*((avolt_ref/voltage_average_value)-1);
  Serial.print(resistance);
  Serial.println(" Ohm");
  Serial.print(voltage_average_value);
  Serial.println(" Volts");
  Serial.print(adc_reading);
  Serial.println(" last raw adc reading");
  delay(100);
}
