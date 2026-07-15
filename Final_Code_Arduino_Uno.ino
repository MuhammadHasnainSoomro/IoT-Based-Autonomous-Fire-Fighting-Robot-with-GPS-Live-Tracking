#include <Servo.h>
#include <SoftwareSerial.h>

// Pin definitions
const int flameSensor1 = A0; // Front sensor
const int flameSensor2 = A1; // Left sensor
const int flameSensor3 = A2; // Right sensor
const int ultrasonicTrigger = 9;
const int ultrasonicEcho = 10;
const int servoPin = 11;
const int motor1IN1 = 3;
const int motor1IN2 = 4;
const int motor2IN1 = 5;
const int motor2IN2 = 6;
const int relayPin = 7;
const int motor1Speed = 12; // Changed ENA to pin 12
const int motor2Speed = 13; // Changed ENB to pin 13

Servo waterPumpServo;
bool isPumping = false; // Flag to check if the pump is active
bool autoMode = false; // Flag to check if in auto mode

// Setup Bluetooth Serial communication
SoftwareSerial bluetooth(1, 0); // RX, TX (HC-05 RX to pin 2, TX to pin 3)

void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);

    pinMode(flameSensor1, INPUT);
    pinMode(flameSensor2, INPUT);
    pinMode(flameSensor3, INPUT);
    pinMode(ultrasonicTrigger, OUTPUT);
    pinMode(ultrasonicEcho, INPUT);
    pinMode(servoPin, OUTPUT);
    pinMode(motor1IN1, OUTPUT);
    pinMode(motor1IN2, OUTPUT);
    pinMode(motor2IN1, OUTPUT);
    pinMode(motor2IN2, OUTPUT);
    pinMode(relayPin, OUTPUT);
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor2Speed, OUTPUT);
    
    digitalWrite(relayPin, HIGH);  // Ensure the pump is off at the start (inverted logic)
    waterPumpServo.attach(servoPin); // Attach servo to the pin
    waterPumpServo.write(0); // Initial position of the servo
    delay(1000); // Stabilization delay after power on
}

void loop() {
    // Read Bluetooth commands
    if (bluetooth.available()) {
        char command = bluetooth.read();
        handleBluetoothCommand(command);
    }

    int flameDetected1 = analogRead(flameSensor1);
    int flameDetected2 = analogRead(flameSensor2);
    int flameDetected3 = analogRead(flameSensor3);
    long distance = getUltrasonicDistance();

    // Print sensor values for debugging
    Serial.print("Flame Sensor 1: ");
    Serial.print(flameDetected1);
    Serial.print(" | Flame Sensor 2: ");
    Serial.print(flameDetected2);
    Serial.print(" | Flame Sensor 3: ");
    Serial.println(flameDetected3);
    Serial.print("Distance from Ultrasonic: ");
    Serial.println(distance);

    // Auto mode functionality
    if (autoMode) {
        if (flameDetected1 < 100) { // Fire detected in front
            Serial.println("Fire detected in front. Activating pump.");
            activatePump();
            stopMovement(); // Stop if fire is detected
        } else if (flameDetected2 < 300) { // Fire detected on left
            Serial.println("Fire detected on left. Turning left.");
            turnLeft();
        } else if (flameDetected3 < 300) { // Fire detected on right
            Serial.println("Fire detected on right. Turning right.");
            turnRight();
        } else {
            // Check distance from flame
            if (distance > 12) { // Keep moving forward only if not too close to flame
                Serial.println("No flame detected. Moving forward.");
                moveForward();
            } else {
                Serial.println("Close to flame. Stopping movement.");
                stopMovement();
            }
        }
    }

    delay(100); // Small delay for stability
}

// Function to get distance from ultrasonic sensor
long getUltrasonicDistance() {
    digitalWrite(ultrasonicTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonicTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonicTrigger, LOW);
    return pulseIn(ultrasonicEcho, HIGH) * 0.034 / 2; // Distance in cm
}

// Function to handle Bluetooth commands
void handleBluetoothCommand(char command) {
    switch (command) {
        case 'F': // Forward
            autoMode = false; // Disable auto mode
            moveForward();
            break;
        case 'B': // Backward
            autoMode = false; // Disable auto mode
            moveBackward();
            break;
        case 'L': // Left
            autoMode = false; // Disable auto mode
            turnLeft();
            break;
        case 'R': // Right
            autoMode = false; // Disable auto mode
            turnRight();
            break;
        case 'M': // Servo on
            waterPumpServo.write(90); // Move servo to spray position
            break;
        case 'm': // Servo off
            waterPumpServo.write(0); // Move servo back to initial position
            break;
        case 'N': // Relay on
            digitalWrite(relayPin, LOW); // Turn on pump (inverted logic)
            break;
        case 'n': // Relay off
            digitalWrite(relayPin, HIGH); // Turn off pump (inverted logic)
            break;
        case 'Y': // Stop all movements
            stopMovement();
            autoMode = false; // Disable auto mode
            break;
        case 'A': // Emergency stop to enter auto mode
            autoMode = true; // Activate auto mode
            stopMovement(); // Stop all movement
            break;
    }
}

// Function to move forward
void moveForward() {
    analogWrite(motor1Speed, 255); // Full speed for Motor 1
    analogWrite(motor2Speed, 255); // Full speed for Motor 2
    digitalWrite(motor1IN1, HIGH);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, HIGH);
    digitalWrite(motor2IN2, LOW);
}

// Function to move backward
void moveBackward() {
    analogWrite(motor1Speed, 255); // Full speed for Motor 1
    analogWrite(motor2Speed, 255); // Full speed for Motor 2
    digitalWrite(motor1IN1, LOW);
    digitalWrite(motor1IN2, HIGH);
    digitalWrite(motor2IN1, LOW);
    digitalWrite(motor2IN2, HIGH);
}

// Function to turn right
void turnRight() {
    analogWrite(motor1Speed, 255); // Full speed for Motor 1
    analogWrite(motor2Speed, 0);    // Stop Motor 2
    digitalWrite(motor1IN1, HIGH);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, LOW);
    digitalWrite(motor2IN2, LOW); // Stop right motor
}

// Function to turn left
void turnLeft() {
    analogWrite(motor1Speed, 0);    // Stop Motor 1
    analogWrite(motor2Speed, 255); // Full speed for Motor 2
    digitalWrite(motor1IN1, LOW);
    digitalWrite(motor1IN2, LOW); // Stop left motor
    digitalWrite(motor2IN1, HIGH);
    digitalWrite(motor2IN2, LOW);
}

// Function to stop movement
void stopMovement() {
    analogWrite(motor1Speed, 0); // Stop Motor 1
    analogWrite(motor2Speed, 0); // Stop Motor 2
    digitalWrite(motor1IN1, LOW);
    digitalWrite(motor1IN2, LOW);
    digitalWrite(motor2IN1, LOW);
    digitalWrite(motor2IN2, LOW);
}

// Function to activate water pump
void activatePump() {
    if (!isPumping) { // Only activate pump if not already active
        Serial.println("Activating pump...");
        digitalWrite(relayPin, LOW); // Turn on pump (inverted logic)
        waterPumpServo.write(90); // Move servo to spray position
        delay(5000); // Run for 5 seconds
        digitalWrite(relayPin, HIGH); // Turn off pump (inverted logic)
        waterPumpServo.write(0); // Move servo back to initial position
        isPumping = true; // Set flag to indicate pump is active
        Serial.println("Pump deactivated.");
    }
}
