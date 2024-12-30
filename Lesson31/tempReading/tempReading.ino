#include <DHT.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

#define DHTPIN 11
#define DHTTYPE DHT22


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

int displayBtnPin = 10;
int setupDelay = 1000;
int delayTime = 1000;
int br=9600;
String message = "No Successful Calculation yet";
DHT tempSensor(DHTPIN, DHTTYPE);

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

Button displayButton(displayBtnPin);

void displayReading(){
  Serial.println(message);
  matrix.beginDraw();
  matrix.textScrollSpeed(100);
  matrix.textFont(Font_5x7);
  matrix.beginText(0,0,255,0,0);
  matrix.println(message);
  matrix.endText(1);
  matrix.endDraw();
}

void setup(){
  Serial.begin(br);
  matrix.begin();
  tempSensor.begin();
  // Button displayButton
  delay(setupDelay);
}

void loop(){
  if(displayButton.stateChanged()){
    displayReading();
  }
  float tempC = tempSensor.readTemperature(false);
  float tempF = tempSensor.readTemperature(true);
  float hum = tempSensor.readHumidity();
  if(isnan(tempC) || isnan(tempF) || isnan(hum)){
    tempC = 1.0;
    tempF = 1.0;
    hum = 10.0;
    // return;
  }
  float heatIdxC = tempSensor.computeHeatIndex(tempC, hum, false);
  float heatIdxF = tempSensor.computeHeatIndex(tempF, hum, true);
  message = "Temp: " + String(tempC) + "C " + String(tempF) + "F Humidity: " + String(hum) + "% Heat Index: " + String(heatIdxC) + "C " + String(heatIdxF) + "F.";
  delay(delayTime);
}