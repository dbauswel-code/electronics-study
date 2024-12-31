//area
//perimeter
//diagonal (a^2 + b^2 = c^2)

struct Shape{
  int num;
  String shape;
};

int shapeCt = 4;
Shape shs[4];
int br = 9600;

int outpin = 11;
int potPin = A0;

// Potentionmeter to adjust brightness of LED

void HWSetup(){
    pinMode(outpin, OUTPUT);
    pinMode(potPin, INPUT);
}
void setup() {
  Serial.begin(br);
  // inClassSetup();
  HWSetup();
}

float readPot(){
  float value = analogRead(potPin);
  return value;
}

float calculateBrightness(float potVal){
  float upperLimitVoltage = 5.0;
  float upperLimitArdType = 1023.0;
  float volts = (upperLimitVoltage/upperLimitArdType)*potVal;
  return volts*51.0;
}

void setLight(float val){
  analogWrite(outpin, val);
}

void HWLoop(){
  float potVal = readPot();
  float ledVal = calculateBrightness(potVal);
  Serial.println(ledVal);
  setLight(ledVal);
}
void loop() {
  HWLoop();
  // inClassLoop();
}

void inClassSetup(){
  shs[0] = {1, "Rectangle"};
  shs[1] = {2, "Square"};
  shs[2] = {3, "Triangle"};
  shs[3] = {4, "Circle"};
}
void inClassLoop(){
  Serial.println("What shape would you like to calculate?");
  for(int i = 0; i < shapeCt; i++){
    Serial.println(String(shs[i].num) + ": " + shs[i].shape);
  }
  // for
  while(Serial.available() == 0){

  }
  int selection = Serial.parseInt();
  if(selection > shapeCt || selection < 1){
    Serial.println("INVALID SELECTION");
    return;
  }
  polygon(shs[selection-1]);
}
void polygon(Shape shp){
  Serial.println(shp.shape +" Selected");
  switch(shp.num){
    case 1:
      rectangle();
      break;
    case 2:
      square();
      break;
    case 3:
      triangle();
      break;
    case 4:
      circle();
      break;
  }
}

float findArea(float l, float w){
  return l*w;
}

void findPerimeter(float l, float w, float &p){
  p = 2*l+2*w;
}
void rectangle(){
  Serial.println("What is the length?");
  while(Serial.available() == 0){}
  float l = Serial.parseFloat();

  Serial.println("What is the width?");
  while(Serial.available() == 0){}
  float w = Serial.parseFloat();

  float area = findArea(l, w);
  float perimeter = 0;
  findPerimeter(l, w, perimeter);

  float res = pow(l,2) + pow(w,2);
  float diagonal = sqrt(res);
  Serial.println("Your shape's area is: " + String(area));
  Serial.println("Your shape's perimeter is: " + String(perimeter));
  Serial.println("Your shape's diagonal is: " + String(diagonal));
}
void square(){
  Serial.println("What is the side length?");
  while(Serial.available() == 0){}
  float s = Serial.parseFloat();

  float area = findArea(s, s);
  float perimeter = 0;
  findPerimeter(s, s, perimeter);
  float res = pow(s,2) + pow(s,2);
  float diagonal = sqrt(res);
  Serial.println("Your shape's area is: " + String(area));
  Serial.println("Your shape's perimeter is: " + String(perimeter));
  Serial.println("Your shape's diagonal is: " + String(diagonal));
}
void triangle(){
  Serial.println("NOT IMPLEMENTED");
}
void circle(){
  Serial.println("NOT IMPLEMENTED");
}
 