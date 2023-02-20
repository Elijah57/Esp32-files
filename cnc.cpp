// Include the required libraries
#include <Stepper.h>
#include <AccelStepper.h>

// Define the pins used for the CNC Shield
#define X_STEP_PIN         2
#define X_DIR_PIN          5
#define Y_STEP_PIN         3
#define Y_DIR_PIN          6
#define Z_STEP_PIN         4
#define Z_DIR_PIN          7

// Define the number of steps per revolution for each stepper motor
#define STEPS_PER_REV      200

// Define the maximum speed and acceleration for each axis
#define MAX_SPEED          1000
#define MAX_ACCELERATION   1000

// Initialize the stepper motors
AccelStepper x_axis(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper y_axis(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper z_axis(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

void setup() {
  // Set the initial speed and acceleration for each axis
  x_axis.setMaxSpeed(MAX_SPEED);
  x_axis.setAcceleration(MAX_ACCELERATION);
  y_axis.setMaxSpeed(MAX_SPEED);
  y_axis.setAcceleration(MAX_ACCELERATION);
  z_axis.setMaxSpeed(MAX_SPEED);
  z_axis.setAcceleration(MAX_ACCELERATION);

  // Set the number of steps per revolution for each axis
  x_axis.setStepsPerRevolution(STEPS_PER_REV);
  y_axis.setStepsPerRevolution(STEPS_PER_REV);
  z_axis.setStepsPerRevolution(STEPS_PER_REV);

  // Enable the CNC Shield
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);

  // Initialize the serial communication
  Serial.begin(115200);

  // Set the Grbl firmware settings
  Serial.println("$");
  Serial.println("$X");
  Serial.println("$10=255");
  Serial.println("$11=0.010");
  Serial.println("$12=0.002");
  Serial.println("$13=0");
  Serial.println("$20=0");
  Serial.println("$21=0");
  Serial.println("$22=0");
  Serial.println("$23=3");
  Serial.println("$24=25.000");
  Serial.println("$25=500.000");
  Serial.println("$26=250");
  Serial.println("$27=1.000");
  Serial.println("$30=1000");
  Serial.println("$31=0");
  Serial.println("$32=0");
}

void loop() {
  // Wait for serial input from the computer
  while (Serial.available() == 0);
  char command = Serial.read();

  // Move the axis as commanded by the computer
  switch (command) {
    case 'X':
      float x_pos = Serial.parseFloat();
      x_axis.moveTo(x_pos);
      break;
    case 'Y':
      float y_pos = Serial.parseFloat();
      y_axis.moveTo(y_pos);
      break;
    case 'Z':
      float z_pos = Serial.parseFloat();
      z_axis.moveTo(z_pos);
      break;
  }

  // Update the stepper motors
  x_axis.run();
  y_axis.run();
  z_axis.run();
