void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Tested by Prof. C with Arduino IDE and VS Code. Repeating this message 1x per second.");
  delay(1000);
}
