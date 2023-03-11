#include<Servo.h>

Servo reactionInitiator;  

// Define pins
const int triggerPin = 7;
const int echoPin = 6;
const int ledPin = 13;

// Define variables
long duration;
int distance;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  reactionInitiator.attach(9, 500, 2500);
  reactionInitiator.write(90);

  // Set pin modes
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Generate ultrasonic pulse
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure duration of echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Turn on LED if distance is less than 100cm
  if (distance < 100) {
    digitalWrite(ledPin, HIGH);
    reactionInitiator.write(90);
    delay(5000);
    reactionInitiator.write(0);
  } else {
    digitalWrite(ledPin, LOW);
    reactionInitiator.write(0);
  }

  // Wait for 100ms before next measurement
  delay(100);
}
