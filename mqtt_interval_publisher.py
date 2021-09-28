import paho.mqtt.client as mqtt
import time
import datetime

#callback function, prints received message when something comes in on the subscribed MQTT topic
def on_message(client, userdata, message):
    #print(userdata)
    print("Received message: " , str(message.payload.decode("utf-8")))

publish_interval = 30
    
mqttBroker ="test.mosquitto.org"

client = mqtt.Client("ECE101_Section2_Interval_Publisher")
client.connect(mqttBroker) 

client.loop_start()

client.subscribe("ece101_section2_messaging")
client.on_message=on_message 

while True:
    current_time = datetime.datetime.now()
    text = "Hi I'm the ECE 101 Section 2 interval publisher and I publish something every " + str(publish_interval) + " seconds. The time at which this message was generated is: " + str(current_time) 
    client.publish("ece101_section2_messaging", text)
    print("Published a message to topic 'ece101_section2_messaging'")
    time.sleep(publish_interval)

client.loop_stop()