import requests
import serial
import time
import json

s = serial.Serial("/dev/ttyS0", 9600, timeout=1)

input_devices = ['alcohol', 'smoke']
output_devices = ['ledRed', 'ledGreen', 'ledYellow', 'ledOne', 'ledTwo', 'ledThree']

SERVER_HOST = "http://172.20.10.5:8000"
#server

def getServerState() -> dict:
    r = requests.get(SERVER_HOST + "/system_state")
    if r.status_code != requests.codes.ok:
        return {}

    return r.json()


def updateDeviceOnServer(input_device: str, value: int):
    data = json.dumps({"value": value})
    r = requests.post(SERVER_HOST + "/devices/" + input_device, data=data)
    if r.status_code != requests.codes.ok:
        return {}


def readSensorVal(input_device: str):
    command_str = "read " + input_device + "\n"
    print(command_str)
    s.write(command_str.encode('raw_unicode_escape'))
    time.sleep(0.1)
    line = s.readline().decode()
    if line == "":
        return
    print("OUT: " + line)
    return int(line)


def sendOutputVal(output, val):
    command_str = "write " + output + " " + str(val) + "\n"
    print(command_str)
    s.write(command_str.encode("raw_unicode_escape"))


def mainLoop():
    # get state from server
    server_stats = getServerState()

    # update all output devices
    for device in server_stats:
        if device["type"] == "input" or device["value"] == None:
            continue
        print(device["name"] + " " + str(device["value"]))
        sendOutputVal(device["name"], device["value"])
        time.sleep(0.1)

    for device in input_devices:
        value = readSensorVal(device)
        if value is None:
            continue
        updateDeviceOnServer(device, value)


while True:
    mainLoop()
    time.sleep(1)