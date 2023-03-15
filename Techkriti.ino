#include <Servo.h> // Include the servo library

Servo chemicalReleaser;  // create servo object to control a servo
Servo lander;  // create servo object to control a servo

const int chemicalReleaserPin = 8;
const int landerPin = 10;
const bool oneTimeRunner = true;
const int trigPin = 7;
const int echoPin = 4;
// Distance (in cm) to kept before initiating the reaction and activating the landers
const int actionDistance = 20;

// For resetting the state of the components
void resetComponents(){
  chemicalReleaser.write(0);
  lander.write(0);
}

// For testing the components
void tester(){
  resetComponents();

  delay(1000);

  Serial.println("Moving the chemical releaser...");
  chemicalReleaser.write(90);
  Serial.println("Moving the landers...");
  lander.write(90);

  delay(1000);

  resetComponents();
}

// Send a pulse to the ultrasonic sensor to measure the distance with object in front of it
int measureDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the time it takes for the pulse to return
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  int distance = duration / 58;

  return distance;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT); // For controlling thw builtin LED
  chemicalReleaser.attach(chemicalReleaserPin);  // attaches the servo on pin 10 to the servo object
  lander.attach(landerPin);  // attaches the servo on pin 10 to the servo object

  resetComponents();
}

void loop() {
  int objectDist = measureDistance();

  Serial.print("Distance with the object: ");
  Serial.print(objectDist);
  Serial.println(" cm");
  
  if(objectDist < actionDistance){
    chemicalReleaser.write(90);
    lander.write(90);

    delay(3000);

    resetComponents();

  } else {
    resetComponents();
  }

  // Wait before taking the next reading
  delay(500);
}
