int pinNumber = 11;
float power = 0.0;
int timeOut = 1;
void setup() {
  Serial.begin(9600);
  pinMode(pinNumber, OUTPUT);
  // put your setup code here, to run once:

}

void increaseBrightness(){
  while(power <= 255){
    float level = (power/255.0)*100.0;
    analogWrite(pinNumber, power);
    Serial.print("Brightness Level: ");
    Serial.print(level);
    Serial.println("%");
    power+=1.0;
    delay(timeOut);
  }
}

void decreaseBrightness(){
  while(power >= 0){
    float level = (power/255.0)*100.0;
    analogWrite(pinNumber, power);
    Serial.print("Brightness Level: ");
    Serial.print(level);
    Serial.println("%");
    power-=1.0;
    delay(timeOut);
  }
}

void loop() {
  increaseBrightness();
  delay(500);
  decreaseBrightness();
  delay(500);
  //power can be between 0-255 (8bit binary number)
}
