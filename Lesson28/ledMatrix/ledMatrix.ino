#include "ArduinoGraphics.h";
#include "Arduino_LED_Matrix.h";

ArduinoLEDMatrix matrix;

byte frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int ROWS = 8;
int COLS = 12;
int dt = 200;
int bounceDelay = 20;
int br = 9600;
int dir;

int prevX = 0;
int prevY = 0;
int dX;
int dY;

String msg = "Blackhawk LED Matrix";

void setFrame(byte fram[][12], int r, int c) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (i == r || j == c) {
        fram[i][j] = !fram[i][j];
      }
    }
  }
}

void draw(int i, int j){
  setFrame(frame, i, j);
  matrix.renderBitmap(frame, ROWS, COLS);
  delay(dt);
}
void inClassLoop1(){
  for(int i = 0; i < ROWS; i++ ){
    for(int j = 0; j < COLS; j++){
      draw(i,j);
      draw(i,j);
    }
  }
}
void message(){
  matrix.beginDraw();
  matrix.textScrollSpeed(100);
  matrix.textFont(Font_5x7);
  matrix.beginText(0,0,255,0,0);
  matrix.println(msg);
  matrix.endText(1);
  matrix.endDraw();
}

int randomRange(int min, int max){
    return random(min, max);
}

void setLocation(int x, int y){
  //turn previous location off
  frame[prevX][prevY] = 0;
  //turn on new location
  frame[x][y] = 1;
  //update prev location to new values
  prevX = x;
  prevY = y;
  //render
  matrix.renderBitmap(frame, ROWS, COLS);
  delay(bounceDelay);
}
void bouncingPixelSetup(){
  int posX = randomRange(0, ROWS);
  int posY = randomRange(0, COLS);
  setLocation(posX, posY);
  dX = 1; //1 or -1
  dY = 1; //1 or -1
}

//13   purple liquid
//4 feather

void calculateNewDirection(){
  if(prevX == 0 || prevX == (ROWS-1)){
    dX = -dX;
  }
  if(prevY == 0 || prevY == (COLS-1)){
    dY = -dY;
  }
}
void translate(){
  calculateNewDirection();
  setLocation(prevX+dX, prevY+dY);
}
void bouncingPixel(){
  while(true){
    translate();
  }
}

void setup() {
  Serial.begin(br);
  matrix.begin();
  bouncingPixelSetup();
}
//1player pong 

void loop() {
  bouncingPixel();
}