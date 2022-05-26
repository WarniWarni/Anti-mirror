//#include <TriacDimmer.h>
#include "DimmerControl.h"
#include "utils.h"
//#include "tests.h"

unsigned char sync = 8; //sync pin == ZeroCrossing

#define S1_echo 3
#define S1_trig 2
#define S2_echo 5
#define S2_trig 4
#define S3_echo 7
#define S3_trig 6
#define S4_echo 12
#define S4_trig 11
#define P1_OUT 14//A0
#define P2_OUT 15//A1
//
#define relayPin 9
//
//  various variables
bool isEnabled = 0;
char message[300];
char message2[300];
//int thresholdDistance = 100;
int timer = 0;
//  end


void setup() {
  Serial.begin(9600);

  pinMode(S1_trig, OUTPUT);
  pinMode(S1_echo, INPUT);
  pinMode(S2_trig, OUTPUT);
  pinMode(S2_echo, INPUT);
  pinMode(S3_trig, OUTPUT);
  pinMode(S3_echo, INPUT);
  pinMode(S4_trig, OUTPUT);
  pinMode(S4_echo, INPUT);
  pinMode(P1_OUT, INPUT);
  pinMode(P2_OUT, INPUT);

//  pinMode(relayPin, OUTPUT);

  //TriacDimmer::begin(pulse_length = 20, min_trigger = 2000, on_thresh = 2, off_thresh = 0.01)
  TriacDimmer::begin(70, 3000, 2, 0.01); // default: 20, 2000, 2, 0.01

  TCCR0A |= (1 << WGM01); //Set the CTC mode
  OCR0A = 0xF9;          //Set the value for 1ms
  TIMSK0 |= (1 << OCIE0A); //Set the interrupt request
  sei();                 //Enable interrupt
  TCCR0B |= (1 << CS01); //Set the prescale 1/64 clock
  TCCR0B |= (1 << CS00);

  
  Serial.print("STARTING\n");
}

// Interrupt every 1 ms, timer increment
ISR(TIMER0_COMPA_vect) {   //This is the interrupt request
  timer++;
}

void controlMirror(int threshold) {
  // the function checks the state of each sensor

  int S1_distance = getDistance(S1_trig, S1_echo);
  int S2_distance = getDistance(S2_trig, S2_echo);
  int S3_distance = getDistance(S3_trig, S3_echo);
  int S4_distance = getDistance(S4_trig, S4_echo);

  bool S1_state = getUltrasoundSensorState(S1_distance, threshold);
  bool S2_state = getUltrasoundSensorState(S2_distance, threshold);
  bool S3_state = getUltrasoundSensorState(S3_distance, threshold);
  bool S4_state = getUltrasoundSensorState(S4_distance, threshold);

  bool P1_state = digitalRead(P1_OUT);
  bool P2_state = digitalRead(P2_OUT);
  
  int S1_min = minimumDistance1InLast5seconds(S1_distance);
  int S2_min = minimumDistance2InLast5seconds(S2_distance);
  int S3_min = minimumDistance3InLast5seconds(S3_distance);
  int S4_min = minimumDistance4InLast5seconds(S4_distance);

  bool S1_state_lagging = getUltrasoundSensorState(S1_min, threshold);
  bool S2_state_lagging = getUltrasoundSensorState(S2_min, threshold);
  bool S3_state_lagging = getUltrasoundSensorState(S3_min, threshold);
  bool S4_state_lagging = getUltrasoundSensorState(S4_min, threshold);
  bool P1_state_lagging = maximumStateP1inLast10seconds(P1_state);
  bool P2_state_lagging = maximumStateP2inLast10seconds(P2_state);


  if ((S1_state_lagging || S2_state_lagging || S3_state_lagging || S4_state_lagging) && (P1_state_lagging || P2_state_lagging)) { // jeśli czujniki PIR wykryły ruch, a czujniki ultradźwiękowe obecność
//    relayOff(relayPin);
    decreaseTransparency(0.01, 20); //float stepSize=0.01, int incrementTime=50
    isEnabled = 1;
  }
  else if ((S1_state_lagging || S2_state_lagging || S3_state_lagging || S4_state_lagging) && isEnabled == 1){ // jeśli czujnik/i ultradzwiekowe czuja obecnosc, ale PIR nie widzi ruchu, a stan jest wysoki:
    
  }
  else { // jesli nie ma ruchu ani obecnosci bliskiej
//    relayOn(relayPin);
    increaseTransparency(0.02, 20); //float stepSize=0.01, int incrementTime=50
    isEnabled = 0;
  }

  printMessage1(message2, S1_distance, S2_distance, S3_distance, S4_distance, P1_state_lagging, P2_state_lagging);
  printMessage2(message, S1_state_lagging, S2_state_lagging, S3_state_lagging, S4_state_lagging, P1_state_lagging, P2_state_lagging);
}


void loop() {
  if (timer > 1000) { // check sensor states every 1000 ms
    controlMirror(200); //thresholdDistance=200

    timer = 0;
  }

}
