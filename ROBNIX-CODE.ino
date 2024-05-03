#include <Servo.h>

// Motor pins
const int leftMotorPin1 = 2;
const int leftMotorPin2 = 3;
const int rightMotorPin1 = 4;
const int rightMotorPin2 = 5;

// IR sensor pins
const int rightIRSensorPin = A3;
const int leftIRSensorPin = A0;

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Servo motor pin
const int servoPin = 8;

// Ultrasonic sensor variables
long duration;
int distance;

Servo servo;

void setup() {
  // Motor pins
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  // IR sensor pins
  pinMode(rightIRSensorPin, INPUT);
  pinMode(leftIRSensorPin, INPUT);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Servo motor
  servo.attach(servoPin);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Read IR sensors
  int rightIRValue = analogRead(rightIRSensorPin);
  int leftIRValue = analogRead(leftIRSensorPin);

  // Adjust servo angle based on ultrasonic sensor reading
  if (distance < 20) {
    servo.write(90); // Center position
  } else if (distance >= 20 && distance <= 40) {
    servo.write(45); // Turn right
  } else {
    servo.write(145); // Turn left
  }

  // Adjust motor speed based on IR sensor readings
  if (rightIRValue < 500 && leftIRValue < 500) {
    // Both sensors detect obstacle, stop
    stopMotors();
  } else if (rightIRValue < 500) {
    // Right sensor detects obstacle, turn left
    turnLeft();
  } else if (leftIRValue < 500) {
    // Left sensor detects obstacle, turn right
    turnRight();
  } else {
    // No obstacle detected, move forward
    moveForward();
  }

  // Debugging: Print sensor readings
  Serial.print("Right IR: ");
  Serial.print(rightIRValue);
  Serial.print(" | Left IR: ");
  Serial.print(leftIRValue);
  Serial.print(" | Distance: ");
  Serial.println(distance);

  // Add a delay to prevent rapid readings
  delay(200);
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, HIGH);
}

// Function to turn the robot left
void turnLeft() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

// Function to stop the robot
void stopMotors() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}
