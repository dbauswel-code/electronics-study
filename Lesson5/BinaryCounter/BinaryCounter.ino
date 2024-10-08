#include <vector>
using namespace std;

int pins[] = { 13, 12, 11, 10 };
int start = 15;

vector<int> decToBin(int dec) {
  vector<int> store;
  int idx = 0;
  int n = dec;
  while (n != 0) {
    store.push_back(n % 2);
    idx++;
    n = n / 2;
  }
  return store;
}

void setLights(vector<int> arr) {
  for (int pinNbr : pins) {
    digitalWrite(pinNbr, 0);
  }

  int sz =  arr.size();
  for (int i = sz - 1; i >= 0; i--) {
    digitalWrite(pins[i], arr[i]);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int pinNbr : pins) {
    pinMode(pinNbr, OUTPUT);
  }
}

void loop() {
  for (int i = start; i >= 0; i--) {
    vector<int> binRep = decToBin(i);
    setLights(binRep);
    delay(1000);
  }
  delay(100000);
}
