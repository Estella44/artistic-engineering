#include <Servo.h>

//pins
int hallPin = 2;
int servoPin = 9;
int ledPin = 6;

//servo

int hallActiveState = HIGH;
//wing behavior
int wingMinAngle = 40;
int wingMaxAngle = 140;
int stepDelay = 20;
int restAngle = 90;
//-----

Servo myServo;

bool magnetActive = false;
float phase = 0.0;

void setup() {
  pinMode(hallPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  myServo.attach(servoPin);
  myServo.write(restAngle);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() {

    //led behavior
  int hallValue = digitalRead(hallPin);
  magnetActive = (hallValue == hallActiveState);
  if(magnetActive) {
    digitalWrite(ledPin, HIGH);
    //add wing function
    wingFunction();

  } else {
    digitalWrite(ledPin, LOW);
    
  }
}

void wingFunction() {
    float flapSpeed = 0.07;
    phase += flapSpeed;
    //use sine wave for motion
    if (phase > 2 * PI) {
      phase -= 2 * PI;
    }

    float sineValue = sin(phase);
    int angle = restAngle + sineValue * (wingMaxAngle - wingMinAngle) / 2.0;
    myServo.write(angle);
    delay(stepDelay);
}



