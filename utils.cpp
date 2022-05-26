#include "utils.h"


int distance1array[5] = {999};
int distance2array[5] = {999};
int distance3array[5] = {999};
int distance4array[5] = {999};
int stateP1array[10] = {0};
int stateP2array[10] = {0};

int duration = 0;



int getMin(int* array, int size) {
  // function returns minimal value of an array
  int minIndex = 0;
  int min = array[minIndex];
  for (int i = 1; i < size; i++) {
    if (min > array[i]) {
      minIndex = i;
      min = array[i];
    }
  }
  return array[minIndex];
}

int getMax(int* array, int size) {
  // function returns maximal value of an array
  int minIndex = 0;
  int min = array[minIndex];
  for (int i = 1; i < size; i++) {
    if (min < array[i]) {
      minIndex = i;
      min = array[i];
    }
  }
  return array[minIndex];
}

int getDistance(int trigPin, int echoPin) {
  // the function calculates the distance of the object from the sensor.
  // returns the distance in cm
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

bool getUltrasoundSensorState(int measured_distance, int threshold) {
  // the functions checks if the minimal threshold distance was breeched
  // if so, the state is set as 1

  if (measured_distance < threshold) {
    return 1; //distance less than threshold, state HIGH
  }
  else
  {
    return 0; //state LOW
  }
}

// functions to calculate extreme values per specified time
int minimumDistance1InLast5seconds(int distance1) {
  // get time, save last X=5 records for each distance and return its minimum
  memcpy(distance1array, &distance1array[1], sizeof(distance1array) - sizeof(int));
  distance1array[4] =  distance1;

  return getMin(distance1array, 5);
}
int minimumDistance2InLast5seconds(int distance2) {
  // get time, save last X=5 records for each distance and return its minimum
  memcpy(distance2array, &distance2array[1], sizeof(distance2array) - sizeof(int)); //przesuń ostatnie wartości o jeden w lewo (usun najstarszy, dodaj najnowszy)
  distance2array[4] =  distance2;

  return getMin(distance2array, 5); // return the lowest value from the array
}

int minimumDistance3InLast5seconds(int distance3) {
  // get time, save last X=5 records for each distance and return its minimum
  memcpy(distance3array, &distance3array[1], sizeof(distance3array) - sizeof(int)); //przesuń ostatnie wartości o jeden w lewo (usun najstarszy, dodaj najnowszy)
  distance3array[4] =  distance3;

  return getMin(distance3array, 5); // return the lowest value from the array
}
int minimumDistance4InLast5seconds(int distance4) {
  // get time, save last X=5 records for each distance and return its minimum
  memcpy(distance4array, &distance4array[1], sizeof(distance4array) - sizeof(int)); //przesuń ostatnie wartości o jeden w lewo (usun najstarszy, dodaj najnowszy)
  distance4array[4] =  distance4;

  return getMin(distance4array, 5); // return the lowest value from the array
}

int maximumStateP1inLast10seconds(bool stateP1) {
  // get time, save last X=5 records for each distance and return its minimum
  memcpy(stateP1array, &stateP1array[1], sizeof(stateP1array) - sizeof(int));
  stateP1array[4] =  stateP1;

  return getMax(stateP1array, 10);
}

int maximumStateP2inLast10seconds(bool stateP2) {
  // get time, save last X=5 records for each distance and return its minimum
  memcpy(stateP2array, &stateP2array[1], sizeof(stateP2array) - sizeof(int));
  stateP2array[4] =  stateP2;

  return getMax(stateP2array, 10);
}
//

void relayOn(int relayP) {
  // the functions changes the relay state to HIGH
  digitalWrite(relayP, LOW);
  Serial.print("Lights on, state HIGH \n");
  //  delay(2000);
}
void relayOff(int relayP) {
  // the functions changes the relay state to LOW
  digitalWrite(relayP, HIGH);
  Serial.print("Lights off, state LOW \n");
  //  delay(2000);
}
//
void printMessage1(char mess[], int S1, int S2, int S3, int S4, bool P1, bool P2){
  sprintf(mess, "\nS1: %d \tS2: %d \tS3: %d \t S4: %d \n\tP1: %d \tP2: %d", S1, S2, S3, S4, P1, P2);
  Serial.println(mess);
}
void printMessage2(char mess[], int S1, int S2, int S3, int S4, bool P1, bool P2){
  Serial.println("----------------------------------------------------------------------------");
  sprintf(mess, "\nLagging states: \nS1: %d \tS2: %d \tS3: %d \t S4: %d \n\tP1: %d \tP2: %d", S1, S2, S3, S4, P1, P2);
  Serial.println(mess);
}
