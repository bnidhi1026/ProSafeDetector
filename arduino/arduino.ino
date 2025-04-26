#include <movingAvg.h>

/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


int pins[]       = {13,12,11,10,9,8,7,6};
String devices[]    = {"ledRed","ledGreen","ledYellow","alcohol", "ledOne", "ledTwo", "ledThree","smoke"};
int directions[] = {OUTPUT,OUTPUT,OUTPUT,INPUT,OUTPUT,OUTPUT,OUTPUT,INPUT};

int buzzPin = 5;
int oldRedLedVal = -1;
int oldGreenLedVal = -1;

movingAvg* inputMovingAverages[] = {new movingAvg(2), new movingAvg(2)};

void setup() {
  Serial.begin(115200); // open serial connection to USB Serial port
  Serial1.begin(9600); // open internal serial connection to MT7688AN}
  
  for (int i = 0; i < sizeof(inputMovingAverages) / sizeof(inputMovingAverages[0]); i++) {
    inputMovingAverages[i]->begin();
  }

  pinMode(buzzPin, OUTPUT);
  
  
  for (int i=0; i<sizeof(pins) / sizeof(pins[0]);i++) {
    pinMode(pins[i], directions[i]);
    digitalWrite(pins[i], HIGH);
    delay(1000);
    digitalWrite(pins[i], LOW);
  }
  
  
}

int getDevicePin(String device) {
   for (int i = 0; i < sizeof(devices) / sizeof(devices[0]); i++) {
    if (devices[i] == device) {
      return pins[i];
    }
  }
  return -1;
}

movingAvg* getMovingAverageForInputDevice(String device) {
  int deviceCount = 0;
  for (int i = 0; i < sizeof(devices) / sizeof(devices[0]); i++) {
    int deviceType = directions[i]; 
    if (devices[i] == device) {
      return inputMovingAverages[deviceCount];
    }
    if (deviceType == INPUT) {
      deviceCount++;
    }
  }
  return NULL;
}

void playMusic() {
  tone(buzzPin, NOTE_G7, 200); 
  delay(350);
  
  tone(buzzPin, NOTE_G7, 200);
  delay(350);
  
  tone(buzzPin, NOTE_A7, 450);
  delay(650);
  
  tone(buzzPin, NOTE_G7, 450);
  delay(650);
  
  tone(buzzPin, NOTE_C8, 650);
  delay(850);
  
  tone(buzzPin, NOTE_B7, 850);
  delay(350);
}


void playBadMusic() {
  tone(buzzPin, NOTE_G5, 300); 
  delay(400);
  
  tone(buzzPin, NOTE_G5, 300); 
  delay(400);
  
  tone(buzzPin, NOTE_G5, 300); 
  delay(400);
  
  tone(buzzPin, NOTE_DS5);
  delay(2100);
  noTone(buzzPin);

  delay(100);

  tone(buzzPin, NOTE_F5, 300); 
  delay(400);
  
  tone(buzzPin, NOTE_F5, 300); 
  delay(400);
  
  tone(buzzPin, NOTE_F5, 300); 
  delay(400);
  
  tone(buzzPin, NOTE_D5);
  delay(3000);
  noTone(buzzPin);
}


void loop() {
  if (Serial1.available()) {
    String line = Serial1.readStringUntil('\n');
      Serial.println(line);
    int firstSpace  = line.indexOf(" ");
    int secondSpace = line.indexOf(" ", firstSpace+1);
    
    String command = line.substring(0, firstSpace);
    String device; 
    int value;

    if (secondSpace == -1) {
      device = line.substring(firstSpace+1);
    }
    else {
      device = line.substring(firstSpace+1, secondSpace);   
    }

        

    Serial.println(command);
    Serial.println(device);

    if (command != "read" && command != "write") {
      Serial.println("err cmd");
      return;
    }
    if (getDevicePin(device) == -1) {
       Serial.println("err dev");
       return;
    }
    
    int pin = getDevicePin(device);
    if (pin == -1) {
      return;
    }
    //Serial.println(pin);

    if (command == "write") {
      value = line.substring(secondSpace).toInt();
      Serial.println(value);
      if (value != 1 && value != 0) {
        Serial.println("err val");
        return;
      }

      digitalWrite(pin, value); 

      if (device == "ledRed") {
         if (value == 1 && oldRedLedVal != 1) {
          playBadMusic();
         }

        oldRedLedVal = value;
      }
       if (device == "ledGreen") {
         if (value == 1 && oldGreenLedVal != 1) {
          playMusic();
         }

        oldGreenLedVal = value;
      }

      
    }
    else if (command == "read") {
      value = analogRead(pin);
      movingAvg* avg = getMovingAverageForInputDevice(device);
      //Serial1.println(avg->reading(value));
      Serial1.println(value);
    }
  }
  delay(100);
}
