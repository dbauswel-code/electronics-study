#include <Servo.h>
 
int potentiometerPin = A0;
int servoPin = 9;
int servoAngle = 0;
int br = 9600;
int potPoll = 1;
int delayTime = 50;
float maxPowerOutput = 695.0;
float servoMaxAngle = 180.0;

Servo blueServo;

void setup() {
  pinMode(potentiometerPin, INPUT);
  Serial.begin(br);
  blueServo.attach(servoPin);
  blueServo.write(0);
}

void waitForInput(){
  while(Serial.available() == 0){

  }
}
void setServoAngle(Servo s, int angle){
  s.write(angle);
}

void inClass(){
  Serial.println("What angle would you like to set the servo?");
  waitForInput();
  int servoAngle = Serial.parseInt();
  setServoAngle(blueServo, servoAngle);
  delay(delayTime);
}

float calculateServoAngle(float pR, float mP, float sA){
  return (sA/mP)*pR;
}
void Lesson22HomeWork(){
  float potReading = analogRead(potentiometerPin);
  float servoAngle = calculateServoAngle(potReading, maxPowerOutput, servoMaxAngle);
  setServoAngle(blueServo, servoAngle);
}

void loop() {
  inClass();
}

//servo + potentionmeter
//potentiometer determines position of servo