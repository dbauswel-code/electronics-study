float grades[25];
int numGrades;
int i;
String myPrompt;
 
float tmp;
int j;
int flag = 1;
 
float bucket;
float avg;
float highGrade = 0;
float lowGrade = 100;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void requestGrades(){
  Serial.println("How Many Grades? ");
  while (Serial.available() == 0) {
  
  }
  numGrades = Serial.parseInt();
  
  for (i = 0; i < numGrades; i = i + 1) {
    myPrompt = "Please Input Grade: " + String(i + 1);
    Serial.println(myPrompt);
    while (Serial.available() == 0) {
    }
    grades[i] = Serial.parseFloat();
  }
}

void averageGrades(){
  bucket = 0;
  for (i = 0; i < numGrades; i = i + 1) {
    bucket = bucket + grades[i];
  }
  avg = bucket / numGrades;
}

void findHighLow(){
  highGrade = 0;
  lowGrade = 100;
  for (i = 0; i < numGrades; i = i + 1) {
    if (grades[i] > highGrade) {
      highGrade = grades[i];
    }
    if (grades[i] < lowGrade) {
      lowGrade = grades[i];
    }
  }
}
void outputResult(){
  Serial.println();
  Serial.println("Your Grades Are: ");
  for (i = 0; i < numGrades; i = i + 1) {
    Serial.println(grades[i]);
  }
  Serial.println("Your Average is: " + String(avg));
  Serial.println("Your High Grade is: " + String(highGrade));
  Serial.println("Your Low Grade is: " + String(lowGrade));
  Serial.println();
}

void sortGrades(){
  flag=1;
  while (flag == 1) {
    flag = 0;
    for (i = 0; i < numGrades - 1; i++) {
      if (grades[i] < grades[i + 1]) {
        tmp = grades[i];
        grades[i] = grades[i + 1];
        grades[i + 1] = tmp;
        flag = 1;
      }
    }
  }
}
void loop() {
  requestGrades();
  sortGrades();
  averageGrades();
  findHighLow();
  outputResult();
}