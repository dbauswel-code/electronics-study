int potentiometerPin = A0; //A0 is a INT as it is hexadecimal NICE!
int potVal;
float power = 0.0;
int waitTime = 100;
int br = 9600;
float volts;
float upperLimitVoltage = 5.0;
float upperLimitArdType = 1023.0;
void setup() {
  Serial.begin(br);
  pinMode(potentiometerPin, INPUT); 
  //INPUT = Reading from PIN
  //OUTPUT = Writing to PIN 
}


void loop() {
  potVal = analogRead(potentiometerPin);
  volts = (upperLimitVoltage/upperLimitArdType)*potVal;
  Serial.print("Potentiometer Value: ");
  Serial.print(potVal);
  Serial.print(" Voltage: ");
  Serial.println(volts);
  delay(waitTime);
}
