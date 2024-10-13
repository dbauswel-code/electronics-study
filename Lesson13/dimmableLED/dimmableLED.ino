int potentiometerPin = A0; //A0 is a INT as it is hexadecimal NICE!
int ledOutputPin = 11;
int potVal;
float power = 0.0;
int waitTime = 100;
int br = 9600;
float volts;
float upperLimitVoltage = 5.0;
float upperLimitArdType = 1023.0;
float upperLimitLED = 255.0;
float ledPower;
void setup() {
  Serial.begin(br);
  pinMode(potentiometerPin, INPUT); 
  pinMode(ledOutputPin, OUTPUT);
  //INPUT = Reading from PIN
  //OUTPUT = Writing to PIN 
}


void loop() {
  potVal = analogRead(potentiometerPin);
  volts = (upperLimitVoltage/upperLimitArdType)*potVal;
  ledPower = volts*51.0;
  analogWrite(ledOutputPin, ledPower);
  Serial.print("Potentiometer Value: ");
  Serial.print(potVal);
  Serial.print(" Voltage: ");
  Serial.print(volts);
  Serial.print(" LED Power: ");
  Serial.println((ledPower/upperLimitLED)*100.0);
  delay(waitTime);
}
