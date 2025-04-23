""" this file covers test cases regarding user info """
# module import

import sample_pb2
import sys

import threading
import signal

import paho.mqtt.client as mqtt
import paho.mqtt.subscribe as subscribe

iterations = 1111
brokerIP = "13.94.243.51"

uuid = ""
ip = ""
res =  [False for i in range(iterations)]

def keyboardInterruptHandler(signal, frame):
    print("KeyboardInterrupt (ID: {}) has been caught. Cleaning up...".format(signal))
    exit(0)

signal.signal(signal.SIGINT, keyboardInterruptHandler)


def parseProtobuf(payload):
    sampleInference = sample_pb2.sampleInference()
    sampleInference.ParseFromString(payload)
    print("Sample timestamp:", sampleInference.timestamp)
    print("Sample object:", sampleInference.object)
    print("Sample x_cordinate_start:", sampleInference.x_cordinate_start)
    print("Sample x_cordinate_end:", sampleInference.x_cordinate_end)
    print("Sample y_cordinate_start:", sampleInference.y_cordinate_start)
    print("Sample y_cordinate_end:", sampleInference.y_cordinate_end)
    print("Sample size_h:", sampleInference.size_h)
    print("Sample size_w:", sampleInference.size_w)
    
# The callback function of connection
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    #sub = "/aievent/" + uuid
    #client.subscribe(sub)
    #print(f"Subscribed to {sub}")

# The callback function for received message
def on_message(client, userdata, msg):
    print("on_message:")
    print(msg.topic+" "+str(msg.payload))


def connect2mqtt1():
    sub = "/aievent/" + uuid
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.username_pw_set(username="admin",password="admin")
    client.connect(brokerIP, 1883, 60)
    client.subscribe(sub)
    client.loop_forever()
  
def connect2mqtt2():
    sub = "/aievent/" + uuid + "/*"
    print(f"Subscribed to {sub}")
    for i in range(iterations):
        msg = subscribe.simple(sub, qos=1, msg_count=1, retained=False, hostname=brokerIP, port=1883, auth = {'username':"admin", 'password':"admin"})
        print(f"{msg.topic} {msg.payload}")
        parseProtobuf(msg.payload)

def connect2mqtt4():
    sub = "/aievent/alltopics"
    print(f"Subscribed to {sub}")
    for i in range(iterations):
        msg = subscribe.simple(sub, qos=1, msg_count=1, retained=False, hostname=brokerIP, port=1883, auth = {'username':"admin", 'password':"admin"})
        print(f"{msg.topic} {msg.payload}")

def checkResults():
    print("Packets lost are:")
    for i in range(iterations):
        if(res[i] == False):
            print("SeqNo: ", i, " is lost")
    print("End of Result")



def ReceiveAndParseProtobuf():
    th1 = threading.Thread(target=connect2mqtt2)
    th1.start()
    th2 = threading.Thread(target=connect2mqtt4)
    th2.start()
    print("Waiting for connect2mqtt to exit.")
    print("Press Ctrl+C if the program doesnt exit to get result")
    th1.join()
    th2.join()
    print("Check Result:")
    #checkResults()

if __name__=="__main__":
    uuid = str(sys.argv[1])
    ReceiveAndParseProtobuf()
    

