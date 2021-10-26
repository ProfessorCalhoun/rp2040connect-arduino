"""
 * Author: Professor DM Calhoun
 * Purpose: This code utilizes an an MQTT library to collect topics and subtopics and parse them to a viewable chart.
"""

import paho.mqtt.client as mqtt
import time
import datetime
import os

all_data = "|Author     |            Time            |     Sensor     |     Information\n"

#callback function, prints received message when something comes in on the subscribed MQTT topic
def on_message_gen(client, userdata, message):
    current_time = str(datetime.datetime.now())
    received_topic = str(message.topic)
    topics = received_topic.split('/')
    author = '{:11.11}'.format(topics[1])
    sensor = '{:3.3}'.format(topics[2])
    global all_data
    add_data = "|" + author + "| " + current_time + " |      " + sensor + "       |     " + str(message.payload.decode("utf-8")) + "\n"
    all_data = all_data + add_data
    os.system('cls||clear') #clear the terminal window
    print(all_data)

publish_interval = 30
    
mqttBroker ="test.mosquitto.org"

client = mqtt.Client("ECE101_Section2_Other_Data_Aggregator")
client.connect(mqttBroker) 

client.loop_start()

client.subscribe("ece101_section2_sensors/+/+")
client.message_callback_add("ece101_section2_sensors/+/+",on_message_gen) #for generic messages
"""client.message_callback_add("ece101_section2_sensors/+/uds",on_message_uds) #for ultrasonic distance sensor (ranger)
client.message_callback_add("ece101_section2_sensors/+/irx",on_message_irx) #for infrared receiver
client.message_callback_add("ece101_section2_sensors/+/lis",on_message_lis) #for light sensor
client.message_callback_add("ece101_section2_sensors/+/acc",on_message_acc) #for digital accelerometer
client.message_callback_add("ece101_section2_sensors/+/pir",on_message_pir) #for mini PIR
client.message_callback_add("ece101_section2_sensors/+/rps",on_message_rps) #for rotary position sensor
client.message_callback_add("ece101_section2_sensors/+/sou",on_message_sou) #for sound sensor
client.message_callback_add("ece101_section2_sensors/+/dht",on_message_dht) #for temperature and humidity sensor
client.message_callback_add("ece101_section2_sensors/+/tem",on_message_tem) #for temperature sensor
client.message_callback_add("ece101_section2_sensors/+/vib",on_message_vib) #for vibration sensor
"""

input()

client.loop_stop()