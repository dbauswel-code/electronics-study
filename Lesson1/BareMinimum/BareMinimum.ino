int pins[] = { 10, 11, 12, 13 };

void on(int pinNbr) {
  digitalWrite(pinNbr, 1);
}
void off(int pinNbr) {
  digitalWrite(pinNbr, 0);
}

void setup() {
  // put your setup code here, to run once:
  for (int pinNbr : pins) {
    pinMode(pinNbr, OUTPUT);
  }
}

void loop() {
  for (int pinNbr : pins) {
    on(pinNbr);
  }
  delay(1000);
  for (int pinNbr : pins) {
    off(pinNbr);
  }
  delay(1000);
}
