// Tested with ESP32-WROOM-DA Module and 3 sensors

// JSN-SR04T
#define trigPin1 GPIO_NUM_5          // pin RX Trig Output  
#define echoPin1 GPIO_NUM_35         // pin TX Echo Input    

// HC-SR04
#define trigPin2 GPIO_NUM_4          // pin RX Trig Output 
#define echoPin2 GPIO_NUM_26         // pin TX Echo Input    

// RCWL-1670
#define trigPin3 GPIO_NUM_14         // pin RX Trig Output
#define echoPin3 GPIO_NUM_34         // pin TX Echo Input  

#include "MySonarJC.h"

MySonarJC myObjSonar;

void setup() {
    Serial.begin(115200);
    delay(100);
    
    /*
      .begin(set the number of sensors you need to use)

    In this case, initialization with 3 ultrasonic sensors
    In the loop , use the function myObjSonar.distance(with index 0,1 or 2)
    
    Note: there is no need to set the INPUT and OUTPUT pinMode(), this is done automatically
    */    
    
    myObjSonar.begin(3); 

    /*
       .parameters(index, RX-PIN, TX-PIN, Min. Distance, Max. Distance, Max.retry, fine tuning pulse, debug) 

    1) Index = object index for simultaneous use of multiple distance sensors
    2) Pin-RX = RX Pin trigger for the ultrasonic sensor
    3) Pin-TX = TX Pin echo for the ultrasonic sensor
    4) Minimum distance of reading capacity of your ultrasonic sensor (This value is not mandatory and the default value is 5 cm)
    5) Maximum distance of reading capacity of your ultrasonic sensor (This value is not mandatory and the default value is 300 cm)    
    6) Fine tuning pulse = This setting allows you to adjust the timeout that depends on the ultrasonic sensors.
      Finding the minimum that works well with your sensor will minimize the time needed to read the echo and the processor resources.
      (default value 200 - Min.value 50 & Max value 300)
    7) Debug = true : Allows to display the echo duration (variable: durationSonar) to optimize the distance calculation function   
    */

    // Setup the JSN-SR04T index=0, RX PIN, TX PIN, from 23 cm to 300 cm
    myObjSonar.parameters(0, trigPin1, echoPin1, 23, 300); 
    
    // Setup the HC-SR04  index=1, RX PIN, TX PIN  
    myObjSonar.parameters(1, trigPin2, echoPin2); 
    
    // Setup the RCWL-1670 index=2, pin-RX, pin-TX, (5 cm , 300 cm, 2 max.retry, 130 for fine tuning pulse, true to display debug values)   
    myObjSonar.parameters(2, trigPin3, echoPin3, 5, 300, 2, 130, true); 
}

void loop() {
  int distance1 = myObjSonar.distance(0); // Read the first sonar
  int distance2 = myObjSonar.distance(1); // Read the second sonar
  int distance3 = myObjSonar.distance(2); // Read the third sonar

  Serial.println("Distance 1:" + String(distance1) + "              Distance 2:" + String(distance2) + "              Distance 3:" + String(distance3));
  delay(50); 
}