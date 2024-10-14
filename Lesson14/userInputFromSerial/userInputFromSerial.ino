int baud = 9600;
void setup(){
  Serial.begin(baud);
}

void waitForInput(){
  while(Serial.available() == 0){ //Serial.available| 0 => no input 1=>input waiting
  }
}
void loop(){
  Serial.println("What is your number");
  waitForInput();
  int userInput = Serial.parseInt();
  Serial.print("Your number x2 is ");
  int res = userInput * 2;
  Serial.println(res);

  Serial.println("What is your name");
  waitForInput();
  String yourName = Serial.readString();
  Serial.print("Your name is ");
  Serial.println(yourName);
}