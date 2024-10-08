
int redLED = 10; //10 slow
int greenLED = 11; //5 fast
void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void blink(int pinVar, int count, int dl){
  for(int i = 0; i < count; i++){
    digitalWrite(pinVar, HIGH);
    delay(dl);
    digitalWrite(pinVar, LOW);
    delay(dl);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  blink(redLED, 10, 500);
  delay(1000);
  blink(greenLED, 5, 100);
  delay(1000);
}
