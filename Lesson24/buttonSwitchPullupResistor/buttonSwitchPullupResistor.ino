#include <vector>
using namespace std;


int readPin = 13;
int ledPin = 10;
int br = 9600;

int redInputPin = 2;
int greenInputPin = 3;
int blueInputPin = 4;

int redLedPin = 9;
int greenLedPin = 10;
int blueLedPin = 11;

int redState = 2;
int greenState = 2;
int blueState = 2;

int internalPullupPin = 6;
int dt = 0;
enum Color {RED, GREEN, BLUE};

class ColorController {
  private:
    Color color;
    int inputPin;
    int outputPin;
    int defaultState;
    bool on;
    bool pressed;
    bool released;
  public:
    ColorController(Color c, int i, int o){
      this->defaultState = 1;
      this->color = c;
      this->inputPin = i;
      this->outputPin = o;
      pinMode(this->inputPin, INPUT);
      pinMode(this->outputPin, OUTPUT);
      this->on = false;
      this->pressed = false;
      this->released = true;
    }

    String getColorString(){
      switch (this->color) {
        case RED:   return "RED";
        case GREEN: return "GREEN";
        case BLUE:  return "BLUE";
        default:    return "UNKNOWN";
      }
    }

    Color getColor(){
      return this->color;
    }

    int getStatus(){
      return digitalRead(this->inputPin);
    }

    void toggle(){
      this->on = !this->on;
      if(this->on){
        digitalWrite(this->outputPin, 1);
      } else {
        digitalWrite(this->outputPin, 0);
      }
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
        this->toggle();
      }
    }
};

vector<ColorController*> colorControllers;

void setup() {
  Serial.begin(br);
  pinMode(internalPullupPin, INPUT_PULLUP);
  ColorController* redC = new ColorController(RED, redInputPin, redLedPin);
  ColorController* greenC = new ColorController(GREEN, greenInputPin, greenLedPin);
  ColorController* blueC = new ColorController(BLUE, blueInputPin, blueLedPin);
  colorControllers.push_back(redC);
  colorControllers.push_back(greenC);
  colorControllers.push_back(blueC);
}

void updateLED(ColorController* c){
  c->stateChanged();
}

void loop() {
  for(ColorController *c: colorControllers){
    updateLED(c);
  }
  int val = digitalRead(internalPullupPin);
  // Serial.println(val);
  delay(dt);
}
