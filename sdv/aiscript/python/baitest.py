""" this file covers test cases regarding user info """
# module import
import sys
import threading
import signal

import requests
import json
import paho.mqtt.client as mqtt
import paho.mqtt.subscribe as subscribe

import base64

iterations = 11
brokerIP = "52.178.44.77"
# create header
jsonheaders = {"Content-type": "application/json"}
imgheaders = {"Content-type": "application/octet-stream"}
uuid = ""
ip = ""
res =  [False for i in range(iterations)]

def keyboardInterruptHandler(signal, frame):
    print("KeyboardInterrupt (ID: {}) has been caught. Cleaning up...".format(signal))
    checkResults()
    exit(0)

signal.signal(signal.SIGINT, keyboardInterruptHandler)


def test_send_ai_event(payload, dest):
    try:
        for i in range(iterations):
            payload['seqno'] = i
            response = requests.post(url=dest, headers=jsonheaders, data=json.dumps(payload))
            print("Iter:", i+1, "Res:", response)
            assert response.status_code == 200, "post failed"
    except Exception as err:
         print("Failed to post ", i+1)

def test_send_ai_image(payload, dest):
    print(dest, imgheaders);
    try:
        for i in range(iterations):
            response = requests.post(url=dest, headers=imgheaders, data=payload)
            print("Iter:", i+1, "Res:", response)
            # let's check if what we sent is what we intended to send...
            #assert base64.b64decode(response.json()['data'][len('data:application/octet-stream;base64,'):]) == data
    except Exception as err:
         print("Failed to post ", i+1, Exception, err)



def updateInfo(payload):
    msg = payload.decode("utf-8") 
    data = json.loads(msg)
    seqno = data['seqno']
    res[seqno] = True

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
    sub = "/aievent/" + uuid
    print(f"Subscribed to {sub}")
    for i in range(iterations):
        msg = subscribe.simple(sub, qos=1, msg_count=1, retained=False, hostname=brokerIP, port=1883, auth = {'username':"admin", 'password':"admin"})
        print(f"{msg.topic} {msg.payload}")
        #updateInfo(msg.payload)


def sendImage():
    dest = "http://" + ip + ":80/ai-event"
    with open('./obj-detect.jpg', 'rb') as f:
        data = f.read()
    test_send_ai_image(data, dest)
    
    
def sendData():
    dest = "http://" + ip + ":80/ai-event"
    # Opening JSON file
    f = open('data.json', "r")
    # returns JSON object as 
    # a dictionary
    data = json.load(f)
    data['senderIP'] = ip
    test_send_ai_event(data, dest)

def checkResults():
    print("Packets lost are:")
    for i in range(iterations):
        if(res[i] == False):
            print("SeqNo: ", i, " is lost")
    print("End of Result")

def testJsonEvent():
    th1 = threading.Thread(target=sendData)
    th2 = threading.Thread(target=connect2mqtt2)
    th1.start()
    th2.start()
    print("Waiting for sendData to exit")
    th1.join()
    print("Waiting for connect2mqtt to exit.")
    print("Press Ctrl+C if the program doesnt exit to get result")
    th2.join()
    print("Check Result:")
    checkResults()

def testAiImage():
    th1 = threading.Thread(target=sendImage)
    th2 = threading.Thread(target=connect2mqtt2)
    th1.start()
    th2.start()
    print("Waiting for sendImage to exit")
    th1.join()
    print("Waiting for connect2mqtt to exit.")
    print("Press Ctrl+C if the program doesnt exit to get result")
    th2.join()
    print("Check Result:")
    checkResults()

if __name__=="__main__":
    ip = str(sys.argv[1])
    uuid = str(sys.argv[2])
    testJsonEvent()
    #testAiImage()
    

