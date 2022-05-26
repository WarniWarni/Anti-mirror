#ifndef DimmerControl_h
#define DimmerControl_h
#include <TriacDimmer.h>
#include <Arduino.h>

void increaseTransparency(float stepSize=0.01, int incrementTime=50);

void decreaseTransparency(float stepSize=0.01, int incrementTime=50);

void setTransparencyLevel(float level, int secsToHold);

#endif
