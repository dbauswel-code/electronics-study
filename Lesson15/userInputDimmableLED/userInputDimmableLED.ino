// Just teaching if/else not

int potentiometerPin = A0; //A0 is a INT as it is hexadecimal NICE!
int ledOutputPin = 11;
int br = 9600;
float volts;
float upperLimitLED = 255.0;
float ledPower;

void waitForInput(){
  while(Serial.available() == 0){

  }
}
void setup() {
  Serial.begin(br);
  pinMode(ledOutputPin, OUTPUT);
}


void loop() {
  Serial.println("What brightness would you like to set the LED (range: 1-10)");
  waitForInput();
  int brightnessValue = Serial.parseInt();
  if(brightnessValue > 10 || brightnessValue < 0){
    Serial.println("Value is outside expected range.");
    return;
  }
  Serial.print("Setting LED brightness to ");
  Serial.println(brightnessValue);
  // ledPower = 2.55 * brightnessValue;
  int expo = brightnessValue/1.25;
  ledPower = pow(2, expo) - 1;
  Serial.println(ledPower);
  analogWrite(ledOutputPin, ledPower);
  Serial.println("DONE."); 
}
