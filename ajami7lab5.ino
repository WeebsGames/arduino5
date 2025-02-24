/*

Areeb Jamili, 669950568, ajami7
Lab 5 - Multiple Inputs and Outputs
This code turns a button on for one second every x seconds. X is determined by a potentiometer. At the same time it detects the light in the room and turns on and off leds basesd on the light level.
I assumed the buzzer would work like the buzzers on the schematics.
I used tutorials for how to use the potentiometer and buzzer for this lab.
https://www.ardumotive.com/how-to-use-a-buzzer-en.html
https://docs.arduino.cc/learn/electronics/potentiometer-basics/


*/


unsigned long time;
unsigned long curr;
unsigned long curr2;
unsigned long curr3;
int buzzDelay;
int photoPin = A0;
int potPin = A1;
int buzzer = 9;
int pinLED1 = 13;
int pinLED2 = 12;
int pinLED3 = 11;
int pinLED4 = 10;
//this is used to test the buzzer without needing to listen to it
int pinLEDtest = 8;
int status1 = LOW;
int status2 = LOW;
int status3 = LOW;
int status4 = LOW;

bool buzz = false;

void setup() {
  // put your setup code here, to run once:
  //enable serial output for debugging
  Serial.begin(9600);
  //enable all output devices
  pinMode(buzzer, OUTPUT);
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);
  pinMode(pinLED4, OUTPUT);
  pinMode(pinLEDtest, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //assign variables to photoresistor and potentiometer values
  int light = analogRead(photoPin);
  int potVal = analogRead(potPin);
  Serial.println(light);
  Serial.println(potVal);
  time = millis();

  //assign the buzzerDelays
  if(potVal == 0){
    buzzDelay = 9999999;
  } else if (potVal < 170){
    buzzDelay = 9000;
  } else if (potVal < 340){
    buzzDelay = 5000;
  } else if (potVal < 510){
    buzzDelay = 2000;
  } else if (potVal < 680){
    buzzDelay = 1000;
  } else if (potVal < 850){
    buzzDelay = 500;
  } else {
    buzzDelay = 0;
  }

  //update the lights every half second
  if(time - curr >=500){
    curr = time;
    status1 = HIGH;
    status2 = HIGH;
    status3 = HIGH;
    status4 = HIGH;
    if(light > 900){
      status1 = LOW;
    }
    if(light > 600){
      status2 = LOW;
    }
    if(light > 400){
      status3 = LOW;
    }
    if(light > 250){
      status4 = LOW;
    }
    digitalWrite(pinLED1, status1);
    digitalWrite(pinLED2, status2);
    digitalWrite(pinLED3, status3);
    digitalWrite(pinLED4, status4);
  }

  //turn on the buzzer after buzzDelay amount and if the buzzer isnt already buzzing
  if(time - curr2 >= buzzDelay && !buzz){
    tone(buzzer,1000);
    digitalWrite(pinLEDtest, HIGH);
    buzz = true;
    curr2 = time;
  }
  //turn off the buzzer after a second if the buzzer is buzzing
  if(time - curr2 >= 1000 && buzz){
    digitalWrite(pinLEDtest, LOW);
    noTone(buzzer);
    curr2 = time;
    buzz = false;
  }
  //turn off the buzzer if the potentiometer is at 0
  if(potVal <= 10){
    digitalWrite(pinLEDtest, LOW);
    noTone(buzzer);
  }
}
