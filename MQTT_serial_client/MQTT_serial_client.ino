/*
 * Author: Professor DM Calhoun
 * Purpose: This code utilizes an Arduino MQTT library and serial string parsing functionality
 * to demonstrate messaging across multiple devices subscribed to one topic.
 */

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
char user_name[] = USER_NAME;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "ece101_section2_messaging";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;

String str;
boolean fade = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600);

  //set initial state of LEDs
  digitalWrite(LEDR,LOW);
  digitalWrite(LEDG,LOW);
  digitalWrite(LEDB,LOW);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);
}

void loop() {
  // avoids being disconnected by the broker
  mqttClient.poll();
        
  // Serial input parser. First check if the UART is available
  if(Serial.available() > 0){
      //Read input string
      str = Serial.readStringUntil('\n');
      delay(100);
      //Put string into message on broker
      unsigned long currentMillis = millis();
    
      if (currentMillis - previousMillis >= interval) {
        // save the last time a message was sent
        previousMillis = currentMillis;
    
        // send message, the Print interface can be used to set the message contents
        mqttClient.beginMessage(topic);
        String transmit_message = (String(user_name) + String(": ") + str);
        mqttClient.print(transmit_message);
        mqttClient.endMessage();
      }
  }

  if (fade){
    updateRGB();
  }
}

//MQTT message received callback function
void onMqttMessage(int messageSize) {
  String received_message = "";
  // we received a message, print out the topic and contents
  Serial.println("Message received from '");
  Serial.print(mqttClient.messageTopic());
  Serial.print(", length ");
  Serial.print(messageSize);
  Serial.println(" bytes");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    received_message+=(char)mqttClient.read();
  }
  parseMessage(received_message);

}

//Function for breaking a string into section based on a parsing character
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
      if (data.charAt(i) == separator || i == maxIndex) {
          found++;
          strIndex[0] = strIndex[1] + 1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void parseMessage(String message){
  String sender = getValue(message,':',0);
  String cmd_message = getValue(message,':',1);
  String act_message = getValue(message,':',2);
  String do_message = getValue(message,':',3);
  
  if(cmd_message == " CMD"){
    //Serial.println("Got into CMD");
    if (act_message == "LEDR"){
      Serial.println("Changing LEDR status!");
      if (do_message == "ON"){
        analogWrite(LEDR,0);
        if (fade) {
          analogWrite(LEDG,255);
          analogWrite(LEDB,255); 
          fade = false;
        }
      }else{
        analogWrite(LEDR,255);
      }
      
    }else if (act_message == "LEDG"){
      Serial.println("Changing LEDG status!");
      if (do_message == "ON"){
        analogWrite(LEDG,0);
        if (fade) {
          analogWrite(LEDR,255);
          analogWrite(LEDB,255); 
          fade = false;
        }
      }else{
        analogWrite(LEDG,255);
      }
      
    }else if (act_message == "LEDB"){
      Serial.println("Changing LEDB status!");
      if (do_message == "ON"){
        analogWrite(LEDB,0);
        if (fade) {
          analogWrite(LEDR,255);
          analogWrite(LEDG,255); 
          fade = false;
        }
      }else{
        analogWrite(LEDB,255);
      }
      
    }else if (act_message == "LED3"){
      Serial.println("Setting RGB LED!");
      if (do_message == "FADE"){
        fade = true;
      }else{
        fade = false;
      }
    }
  }else{
    Serial.println(message);
  }  
}

//Function for updating an RGD LED in a fade configuration
void updateRGB(){
  static int rgbValues[] = {255, 0, 0}; // 0=Red, 1=Green and 2=Blue
  static int upIndex=0, downIndex=1;

  rgbValues[upIndex] += 1;
  rgbValues[downIndex] -= 1;

  if(rgbValues[upIndex] > 255){
    rgbValues[upIndex] = 255;
    upIndex = upIndex + 1;

    if(upIndex > 2){
      upIndex = 0;
    }
  }

  if(rgbValues[downIndex] < 0){
    rgbValues[downIndex] = 0;
    downIndex = downIndex + 1;

    if(downIndex > 2){
      downIndex = 0;
    }
  }

  analogWrite(LEDR, 255 - rgbValues[0]);
  analogWrite(LEDG, 255 - rgbValues[1]);
  analogWrite(LEDB, 255 - rgbValues[2]);  
  
  delay(5);
}
