# MySonarJC Arduino Library

A versatile Arduino library for managing multiple ultrasonic distance sensors simultaneously. The library has been tested with ESP32-WROOM-DA Module and supports various ultrasonic sensors including JSN-SR04T, HC-SR04, and RCWL-1670.

## Features

- Support for multiple ultrasonic sensors
- Automatic pin mode configuration
- Configurable distance ranges
- Fine-tuning capabilities for pulse timing
- Debug mode for echo duration monitoring
- Customizable retry attempts for reliable readings

## Compatible Sensors

- JSN-SR04T
- HC-SR04
- RCWL-1670
- Other similar ultrasonic sensors

## Installation

1. Download the MySonarJC library
2. Include it in your Arduino project using:
```cpp
#include "MySonarJC.h"
```

## API Reference

### Class Initialization
```cpp
MySonarJC myObjSonar;
```

### Methods

#### begin()
Initializes the sonar system with the specified number of sensors.
```cpp
void begin(int numberOfSensors);
```
- `numberOfSensors`: Number of ultrasonic sensors to be used (required)

#### parameters()
Configures individual sensor parameters.
```cpp
void parameters(int index, int rxPin, int txPin, int minDistance = 5, int maxDistance = 300, int maxRetry = 2, int fineTuningPulse = 200, bool debug = false);
```

Parameters:
- `index`: Sensor index (0-based) for multiple sensor management (required)
- `rxPin`: Trigger pin number (required)
- `txPin`: Echo pin number (required)
- `minDistance`: Minimum measurable distance in cm (default: 5)
- `maxDistance`: Maximum measurable distance in cm (default: 300)
- `maxRetry`: Maximum number of retry attempts (default: 2)
- `fineTuningPulse`: Echo timeout adjustment (default: 200, range: 50-300)
- `debug`: Enable debug mode for echo duration display (default: false)

#### distance()
Reads the distance from a specified sensor.
```cpp
int distance(int index);
```
- `index`: Sensor index to read from (required)
- Returns: Distance in centimeters

## Usage Example

```cpp
#include "MySonarJC.h"

// Pin definitions
#define TRIG_PIN1 5
#define ECHO_PIN1 35
#define TRIG_PIN2 4
#define ECHO_PIN2 26

MySonarJC sonar;

void setup() {
    Serial.begin(115200);
    
    // Initialize for 2 sensors
    sonar.begin(2);
    
    // Configure sensors
    sonar.parameters(0, TRIG_PIN1, ECHO_PIN1, 23, 300);  // JSN-SR04T
    sonar.parameters(1, TRIG_PIN2, ECHO_PIN2);           // HC-SR04
}

void loop() {
    int distance1 = sonar.distance(0);
    int distance2 = sonar.distance(1);
    
    Serial.println("Distance 1: " + String(distance1) + " cm");
    Serial.println("Distance 2: " + String(distance2) + " cm");
    
    delay(50);
}
```

## Fine-Tuning Guidelines

1. **Pulse Timing Adjustment**
   - Start with default value (200)
   - Decrease if sensor responds quickly
   - Increase if readings are unstable
   - Valid range: 50-300

2. **Retry Settings**
   - Default: 2 retries
   - Increase for noisy environments
   - Decrease for faster readings

3. **Distance Range**
   - Set according to sensor specifications
   - JSN-SR04T: 23-300cm
   - HC-SR04: 5-300cm
   - RCWL-1670: 5-300cm

## Debug Mode

Enable debug mode to monitor echo duration:
```cpp
sonar.parameters(0, TRIG_PIN, ECHO_PIN, 5, 300, 2, 200, true);
```
This will output echo duration values to Serial monitor for optimization.

## Performance Considerations

- Maintain minimum 50ms delay between readings
- Higher fineTuningPulse values increase accuracy but reduce speed
- Multiple sensors require more processing time
- Consider sensor placement to avoid cross-interference

## Limitations

- Maximum number of sensors depends on available GPIO pins
- Reading accuracy affected by environmental conditions
- Temperature affects sound wave speed
- Reflective surfaces may cause false readings

## Contributing

Contributions to improve the library are welcome. Please submit pull requests with:
- Clear description of changes
- Test results with different sensors
- Documentation updates
- Code following Arduino style guide

## License

This library is released under the MIT License.
