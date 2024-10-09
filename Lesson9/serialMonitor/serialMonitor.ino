
int pinNumber = 12;

void setup() {
  Serial.begin(9600);
  pinMode(pinNumber, OUTPUT);
}

void loop() {
  digitalWrite(pinNumber, HIGH);
  Serial.print("pin ");
  Serial.print(pinNumber);
  Serial.println(" is on");
  delay(1000);
  digitalWrite(pinNumber, LOW);
  Serial.print("pin ");
  Serial.print(pinNumber);
  Serial.println(" is off");
  delay(1000);
}
