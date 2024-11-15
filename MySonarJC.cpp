#include "MySonarJC.h"

MySonarJC::MySonarJC() {
   numSensors = 0;   
   _minDistance = nullptr;
   _maxDistance = nullptr;
   _maxRetry = nullptr;
   _trigPin = nullptr;
   _echoPin = nullptr;
   _pulseTuning = nullptr;
   _debug = nullptr;
   lastDistanceSonar = nullptr;
}

void MySonarJC::begin(int numberOfSensors) {
    kalmanFilter.setAngle(0);
    kalmanFilter.setQangle(0.001);
    kalmanFilter.setQbias(0.003);
    kalmanFilter.setRmeasure(0.03);  
    numSensors = numberOfSensors;
    _minDistance = new int[numberOfSensors];
    _maxDistance = new int[numberOfSensors];
    _maxRetry = new int[numberOfSensors];
    _trigPin = new int[numberOfSensors];
    _echoPin = new int[numberOfSensors];
	_pulseTuning = new int[numberOfSensors];
	_debug = new int[numberOfSensors];
    lastDistanceSonar = new int[numberOfSensors];
}

void MySonarJC::parameters(int index, int trigPin, int echoPin, int mindistance, int maxdistance, int maxRetry, int pulseTuning, bool debug) {
    _minDistance[index] = mindistance;
    _maxDistance[index] = maxdistance;
    _maxRetry[index] = maxRetry;
    _trigPin[index] = trigPin;
    _echoPin[index] = echoPin;
	_pulseTuning[index] = pulseTuning;
	_debug[index] = debug;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);    
}

int MySonarJC::distance(int index) {
    // Check if index is valid
    if (index >= numSensors || index < 0) {
        return -1;
    }
    
    float durationSonar=0;
    int distanceSonar=0;
    int retryCount=0;   
    bool bReceive=false;
	int pt=_pulseTuning[index];
	constrain(pt, 50,300); 
    while (retryCount < _maxRetry[index]) 
    {   
        // Disable interrupts
		portDISABLE_INTERRUPTS();        
        digitalWrite(_trigPin[index], LOW);
        delayMicroseconds(2);
        digitalWrite(_trigPin[index], HIGH);
        delayMicroseconds(10);
        digitalWrite(_trigPin[index], LOW);
        durationSonar = pulseIn(_echoPin[index], HIGH,_maxDistance[index]*pt); 
        // Re-enable interrupts
        portENABLE_INTERRUPTS();
        
		if (_debug[index]) {Serial.println("index :"+String(index)+"   retryCount :"+String(retryCount)+"    durationSonar :"+String(durationSonar));}
		
        if (durationSonar>0)
        {
			bReceive=true;
			break;
		}
        else
        {retryCount++;}    
    }

    if (durationSonar == 0) 
    {
        distanceSonar = lastDistanceSonar[index]; 
    }
    else 
    {
        // Apply Kalman filter
        float rawDistance = (durationSonar * 0.034 / 2);
        kalmanFilter.setAngle(rawDistance);
        // Calculate distance in centimeters
        distanceSonar = static_cast<int>(kalmanFilter.getAngle(rawDistance, 0, 0.1));
    }
    distanceSonar = constrain(distanceSonar, _minDistance[index], _maxDistance[index]);  
    if (bReceive)
	{
		lastDistanceSonar[index] = distanceSonar;
	}
    else
    {
		// The echo did not come back, we assume the target is too far away
		lastDistanceSonar[index] = _maxDistance[index];
	}		
    return distanceSonar; 
}