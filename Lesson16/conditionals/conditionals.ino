int br = 9600;
int redPin = 9;
int yellowPin = 10;
int greenPin = 11;

int ledList[] = {redPin,yellowPin,greenPin};
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(br);
}

void waitForInput(){
  while(Serial.available() == 0){

  }
}

void turnOffAll(){
  for(int pn: ledList){
    analogWrite(pn, 0);
  }
}
void lightled(int pinNbr, int brightness = 10){
  turnOffAll();
  analogWrite(pinNbr, calculateBrightness(brightness));
}

int calculateBrightness(int brightness){
  int expo = brightness/1.25;
  return pow(2, expo) - 1;
}
void lightAll(int brightness = 10){
  for(int pinNbr: ledList){
    analogWrite(pinNbr, calculateBrightness(brightness));
  }
}

void loop() {
  Serial.println("Which LED would you like to light up? (RED, YELLOW, GREEN, OR ALL)");
  waitForInput();
  String colorInput = Serial.readString();
  Serial.print("What brightness would you like to set the ");
  Serial.print(colorInput);
  Serial.println(" LED (range: 1-10)");
  waitForInput();
  int brightness = Serial.parseInt();
  if(brightness < 0 || brightness > 10){
    Serial.println("Invalid value entered please try again.");
    return;
  }
  String userInput = Serial.readString();
  colorInput.toLowerCase();
  if(colorInput == "red"){
    lightled(redPin, brightness);
  } else if(colorInput == "yellow"){
    lightled(yellowPin, brightness);
  } else if(colorInput == "green"){
    lightled(greenPin, brightness);
  } else if (colorInput == "all"){
    lightAll(brightness);
  }
  else {
    Serial.print(colorInput);
    Serial.println(" is not a valid entry");
  }
}
