import serial
import time
import requests
import json

arduino = serial.Serial('COM7', 9600, timeout=1)
arduino.reset_input_buffer()
url = "http://localhost:5000/Datos"

def saveData(args):
    response = requests.post(url, json=args)
    print(response.url)
    if response.status_code == 200:
        print(response.content)


def write_read():
    time.sleep(2)
    data = arduino.readline().decode("utf-8")
    try:
        dict_json = json.loads(data)
        print(dict_json)
        saveData(dict_json)
    except json.JSONDecodeError as e:
        print("json: ", e)
    return dict_json

while True:
    value = write_read()
    # print(value)