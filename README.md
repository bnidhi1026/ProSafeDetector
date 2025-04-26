# EmbeddedProjectGroup3

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
