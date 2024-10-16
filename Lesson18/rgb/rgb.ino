int br = 460800;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int ledList[] = { redPin, greenPin, bluePin };
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(br);
}

void waitForInput() {
  while (Serial.available() == 0) {
  }
}


void turnOffAll() {
  for (int pn : ledList) {
    analogWrite(pn, 0);
  }
}

void lightrgbled(int r, int g, int b, int brightness = 10) {
  int cB = calculateBrightness(brightness);
  analogWrite(redPin, calcBrightness(r, cB));
  analogWrite(greenPin, calcBrightness(g, cB));
  analogWrite(bluePin, calcBrightness(b, cB));
}

int calcBrightness(int val, int brightness){
  return ((val * brightness))/100;
}
int calculateBrightness(int brightness) {
  int expo = brightness / 1.25;
  return pow(2, expo) - 1;
}

void loop() {
  Serial.println("Which LED would you like to light up? (RED, GREEN, BLUE, CYAN, MAGENTA, ORANGE OR WHITE)");
  waitForInput();
  String colorInput = Serial.readString();
  Serial.print("What brightness would you like to set the ");
  Serial.print(colorInput);
  Serial.println(" LED (range: 1-10)");
  waitForInput();
  int brightness = Serial.parseInt();
  if (brightness < 0 || brightness > 10) {
    Serial.println("Invalid value entered please try again.");
    return;
  }
  String userInput = Serial.readString();
  colorInput.toLowerCase();
  if (colorInput == "off"){
    turnOffAll();
  }
  else if (colorInput == "red") {
    lightrgbled(255, 0, 0, brightness);
  } else if (colorInput == "green") {
    lightrgbled(0, 255, 0, brightness);
  } else if (colorInput == "blue") {
    lightrgbled(0, 0, 255, brightness);
  } else if (colorInput == "cyan") {
    lightrgbled(0, 255, 255, brightness);
  } else if (colorInput == "magenta") {
    lightrgbled(255, 0, 255, brightness);
  } else if (colorInput == "orange") {
    lightrgbled(255, 165, 0, brightness);
  } else if (colorInput == "white") {
    lightrgbled(255, 255, 255, brightness);
  } else {
    Serial.print(colorInput);
    Serial.println(" is not a valid entry");
  }
}
