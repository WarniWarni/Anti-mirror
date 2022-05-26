#include "DimmerControl.h"

unsigned char channel_2 = 10; // channel 2 pin
// Funkcje służące do obsługi dimmera 
void increaseTransparency(float stepSize=0.01, int incrementTime=50){
  Serial.println("\nIncrease Brightness\n");
    for(float brightness = 1.00; brightness > 0.00; brightness -= stepSize){
  
    TriacDimmer::setBrightness(channel_2, 1 - brightness); // 0, 0.5, 1 -- dodajemy prądu == robimy bardziej przezroczyste
    delay(incrementTime);
//    Serial.println(1-brightness);
  }
}

void decreaseTransparency(float stepSize=0.01, int incrementTime=50){
  Serial.println("\nDecrease Brightness\n");
    for(float brightness = 0.00; brightness < 1.00; brightness += stepSize){
    TriacDimmer::setBrightness(channel_2, 1 - brightness); // 1, 0.5, 0 -- odejmujemy prądu == robimy bardziej matowe
    delay(incrementTime);
//    Serial.println(1-brightness);
  }
}

void setTransparencyLevel(float level){
  TriacDimmer::setBrightness(channel_2, level);
}
