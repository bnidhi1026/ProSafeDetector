# 🔧 Embedded Systems Project – Smart Device Control via Serial & Web Interface

## 📦 Overview
This project integrates embedded firmware, Python middleware, and a web-based frontend to manage and monitor environmental conditions (e.g., smoke, alcohol levels) using Arduino and a Linux-based microcontroller (e.g., MT7688AN or Raspberry Pi). It supports:

Sensor input & data smoothing (e.g., alcohol, smoke)

LED control & audio alerts via Serial

Web UI + REST API for remote control

Real-time serial communication bridge

## 🧱 Project Architecture

[Web UI (main.ts)]

       │
       ▼
       
[FastAPI Backend (main.py)]

       │
       ▼
       
[Serial Bridge (main.py)]

       │
       ▼
       
[Arduino (arduino.ino)]

       │
       
Sensors (Alcohol, Smoke)
Outputs (LEDs, Buzzer)

## Links
- Python Examples: https://github.com/eclipse/mraa
- Board Setup: https://wiki.seeedstudio.com/LinkIt_Smart_7688/#demo-a-hello-world-example

## Setup
Connect server and board to same wifi (Default right now is "Fabis Phone" with password "hochsicher31")

### Server (Laptop/Pi)
- in directory _server/frontend_ run `npm install .`
- in directory _server/backend_ run `pip install -r requirements.txt`

### Smart 7688 Board
- Connect LED to port S1 (gpio496)
- To programm arduino, make sure the micro-usb is plugged in the "PWR/MCU" port of the board
- For Arduino IDE setup, import file://path/to/package_mtk_linkit_smart_7688_index.json
  - in this file change to file so it references file://path/to/LinkIt.zip
  - then under Board-Manager, install and finally select Smart 7688 Board to programm the atmega32u4 

## Running

### Server
- in directory _server/backend_ `folder run: npm run watch --prefix ../frontend & uvicorn main:app --reload --host 0.0.0.0 && fg`
- Website will be accessible under _localhost:8000_
### Smart 7688 Board
- Python script listening for changes in LED state should auto-start
  - otherwise run `python main.py`

## Caveats/Todo
- on board, hostname of sereer is hardcoded
