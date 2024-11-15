// MySonarJC.h
#ifndef MYSONARJC_H
#define MYSONARJC_H

#include <Arduino.h>
#include <Kalman.h>

class MySonarJC {
public:
    MySonarJC();
    void begin(int numSensors);
    void parameters(int index,int trigPin, int echoPin, int minDistance = 5, int maxDistance = 300, int maxRetry = 3, int pulseTuning = 200, bool debug = false);
    int distance(int index);

private:
    Kalman kalmanFilter;
    int numSensors;
    int* _minDistance;
    int* _maxDistance;
    int* _maxRetry;
    int* _trigPin;
    int* _echoPin;
	int* _pulseTuning;
	int* _debug;
    int* lastDistanceSonar;
};

#endif // MYSONARJC_H