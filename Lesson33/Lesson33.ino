#include <Servo.h>
int servoPin = 9;
int photoResistorPin = A0;
int br = 9600;

Servo blueServo;
void setup() {
  Serial.begin(br);
  pinMode(photoResistorPin, INPUT);
  blueServo.attach(servoPin);
  blueServo.write(0);
}

void loop() {
  // delay(100);
  float output = analogRead(photoResistorPin);
  float angle = (180.0/1023.0)*output;
  Serial.print(output);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.println(1023);
  blueServo.write(angle);pio run -t upload -e esp32cam_ai_thinker
}
