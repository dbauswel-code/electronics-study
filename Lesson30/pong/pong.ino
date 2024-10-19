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


int upPin = 12;
int downPin = 11;
int ROWS = 8;
int COLS = 12;
int dt = 200;
int bounceDelay = 100;
int br = 9600;
int dir;
bool gameOver = false;
String lowScoreMessage = "YOU'RE TRASH KID";
String gameOverMessage = "GAME OVER LOSER. Score: ";
enum PongType {
  PLAYER,
  BALL
};
struct PongObject {
  PongType p;
  int prevX;
  int prevY;
  int x;
  int y;
  int dX = 0;
  int dY = 0;
  int score = 0;
};

PongObject ball;
PongObject player;

class Button {
  private:
    int inputPin;
    int defaultState;
    bool on;
    bool pressed;
    bool released;
  public:
    Button(int i) {
      this->defaultState = 1;
      this->inputPin = i;
      pinMode(this->inputPin, INPUT_PULLUP);
      this->on = false;
      this->pressed = false;
      this->released = true;
    }

    int getStatus(){
      return digitalRead(this->inputPin);
    }

    bool stateChanged(){
      int currentState = this->getStatus();
      if(currentState == 0){
        this->pressed = true;
        this->released = false;
      }
      if(currentState == 1 && this->pressed == true){
        this->pressed = false;
        this->released = true;
        return true;
      }
      return false;
    }
};

int randomRange(int min, int max) {
  return random(min, max);
}

Button* upButton;
Button* downButton;

void setLocation(PongObject& obj) {
  //set previous location to empty
  if(obj.p == PLAYER){
    frame[obj.prevX][0] = 0;
    if(obj.prevX > 0){
      frame[(obj.prevX)-1][0] = 0; //Makes ball go vertical or some reason
    }
    frame[(obj.prevX)+1][0] = 0;
    frame[(obj.x)+1][0] = 1;
    frame[(obj.x)-1][0] = 1;
  }
  frame[obj.x][obj.y] = 0;
  //set new location
  obj.x = obj.x + obj.dX;
  obj.y = obj.y + obj.dY;
  frame[obj.x][obj.y] = 1;
  //render
  matrix.renderBitmap(frame, ROWS, COLS);
}

void pongSetup() {
  ball.p = BALL;
  ball.x = randomRange(0, ROWS);
  ball.y = randomRange(0, COLS);
  setLocation(ball);
  ball.dX = 1;
  ball.dY = 1;
  player.p = PLAYER;
  player.x = ROWS / 2;
  player.y = 0;
  setLocation(player);
  upButton = new Button(upPin);
  downButton = new Button(downPin);
}


void sendMessage(String msg){
  matrix.beginDraw();
  matrix.textScrollSpeed(100);
  matrix.textFont(Font_5x7);
  matrix.beginText(0,0,255,0,0);
  matrix.println(msg);
  matrix.endText(1);
  matrix.endDraw();
}

bool touchingPlayer(PongObject& obj, PongObject& player){
  if(player.y == obj.y){
    if(player.x == obj.x || player.x+1 == obj.x || player.x-1 == obj.x){
      player.score += 1;
      return true;
    }
  }
  return false;
}

bool checkLocation(PongObject& obj, PongObject& player) {
  if (obj.y == 0 && !touchingPlayer(obj, player)) {
    return false;
  }
  if (obj.x == 0 || obj.x == (ROWS - 1)) {
    obj.dX = -obj.dX;
  }
  if (obj.y == 0 || obj.y == (COLS - 1)) {
    obj.dY = -obj.dY;
  }
  return true;
}
void pong() {
  if(upButton->stateChanged()){
    if((player.x - 1) >= 1){
      player.prevX = player.x;
      player.x -= 1;
    }
  }
  setLocation(player);
  if(downButton->stateChanged()){
    if((player.x + 1) < ROWS-1){
      player.prevX = player.x;
      player.x += 1;
    }
  }
  setLocation(player);
  if (!checkLocation(ball, player)) {
    gameOver = true;
    matrix.end();
    return;
  }
  setLocation(ball);
  delay(bounceDelay);
}

void setup() {
  Serial.begin(br);
  matrix.begin();
  pongSetup();
}

void loop() {
  while (!gameOver) {
    pong();
  }
  delay(100);
  matrix.begin();
  if(player.score <= 2){
    sendMessage(lowScoreMessage);
    delay(500);
  }
  String msg = gameOverMessage + player.score;
  sendMessage(msg);
}