int br = 460800;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int timeout = 250;

int ledList[] = { redPin, greenPin, bluePin };
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(br);
}

void turnOffAll() {
  for (int pn : ledList) {
    analogWrite(pn, 0);
  }
  while(true){

  }
}

void setColor(String colorInput){
  if (colorInput == "red") {
    lightrgbled(255, 0, 0);
  } else if (colorInput == "green") {
    lightrgbled(0, 255, 0);
  } else if (colorInput == "blue") {
    lightrgbled(0, 0, 255);
  } else {
    return;
  }
}
void lightrgbled(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void waitForInput(){
  while(Serial.available() == 0){

  }
}

void colorLoop(){
  setColor("red");
  delay(timeout);
  setColor("green");
  delay(timeout);
  setColor("blue");
  delay(timeout);
}
//Lesson19 HW
void forLoopVersion(int ct){
  for(int i = 0; i < ct; i++){
    colorLoop();
  }
  turnOffAll();
}

//Lesson20 HW
void whileLoopVersion(int ct){
  int i = 0;
  while(i < ct){
    colorLoop();
    i++;
  }
  turnOffAll();
}

void loop() {
  Serial.println("How many iterations?");
  waitForInput();
  int ct = Serial.parseInt();
  // forLoopVersion(ct);
  whileLoopVersion(ct);
}
