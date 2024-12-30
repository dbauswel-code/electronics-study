float grades[25];
float sortedGrades[25];
int numGrades;
int br = 9600;
int dt = 50000;
float hi = 0;
float lo = 100;

void setup() {
  Serial.begin(br);
  // put your setup code here, to run once:

}

void swap(float arr[], int i, int j){
  float tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

int partition(float arr[], int l, int r){
    int pivot = arr[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] > pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i+1, r);  
    return i + 1;
}

void quickSort(float arr[], int l, int r){
  if(l <r){
    int part = partition(arr, l, r);
    quickSort(arr, l, part-1);
    quickSort(arr, part+1, r);
  }

}
void sort(float arr[], int sz){
  quickSort(arr, 0, sz-1);
}

void loop() {
  float sum = 0;
  Serial.println("How many students? ");
  while(Serial.available() == 0){
  }
  numGrades = Serial.parseInt();
  Serial.println(numGrades);
  for(int i = 0; i < numGrades; i++){
    Serial.print("Grade for student ");
    Serial.print(i);
    Serial.println("? ");
    while(Serial.available() == 0){
    }
    grades[i] = Serial.parseFloat();
    sum += grades[i];
    if(grades[i] > hi){
      hi = grades[i];
    }

    if(grades[i] < lo){
      lo = grades[i];
    }
  }
  for(int i = 0; i < numGrades; i++){
    Serial.println("Student " + String(i) + " Grade: " + String(grades[i]));
  }
  float avg = sum/numGrades;
  Serial.println("Class Avg: " + String(avg));
  Serial.println("High: " + String(hi));
  Serial.println("Low: " + String(lo));
  sort(grades, numGrades);

  for(int i = 0; i < numGrades; i++){
    Serial.println("#" + String(i+1) + " " + String(grades[i]));
  }

}
