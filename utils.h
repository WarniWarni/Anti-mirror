#ifndef utils_h
#define utils_h
#include <Arduino.h>


int getMin(int* array, int size);
int getMax(int* array, int size);

int getDistance(int trigPin, int echoPin);
bool getUltrasoundSensorState(int measured_distance, int threshold);

// functions to calculate extreme values per specified time
int minimumDistance1InLast5seconds(int distance1);
int minimumDistance2InLast5seconds(int distance2);
int minimumDistance3InLast5seconds(int distance3);
int minimumDistance4InLast5seconds(int distance4);

int maximumStateP1inLast10seconds(bool stateP1);

int maximumStateP2inLast10seconds(bool stateP2);

// functions to 
void relayOn(int relayP);
void relayOff(int relayP);

void printMessage1(char mess[], int S1, int S2, int S3, int S4, bool P1, bool P2);
void printMessage2(char mess[], int S1, int S2, int S3, int S4, bool P1, bool P2);

#endif
