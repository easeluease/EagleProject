#include <Servo.h>

// Pins
const int wingLeftPin = 10;    // Left wing
const int wingRightPin = 9;    // Right wing
const int headPin = 11;        // Head
const int switchPin = 2;       // Toggle switch

// Movement Settings
const int moveSpeed = 25;      // Same speed for wings and head (ms)
const int wingFlapRange = 25;  // 25° wing range
const int headMin = 30, headMax = 150; // Head range

Servo wingLeft, wingRight, head;
int wingPos = 90;              // Current wing position
int headPos = 90;              // Current head position
bool movingOutward = true;     // Wing direction flag

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  
  // Extended pulse range
  wingLeft.attach(wingLeftPin, 500, 2500);
  wingRight.attach(wingRightPin, 500, 2500);
  head.attach(headPin, 500, 2500);
  
  centerAll();
  delay(1000);
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    moveAll(); // Simultaneous movement
  } else {
    centerAll();
  }
}

void moveAll() {
  // Update wing position
  if (movingOutward) {
    wingPos++;
    if (wingPos >= 90 + wingFlapRange) movingOutward = false;
  } else {
    wingPos--;
    if (wingPos <= 90) movingOutward = true;
  }

  // Update head position (continuous sweep)
  headPos++;
  if (headPos > headMax) headPos = headMin;

  // Write all positions
  wingLeft.write(wingPos);
  wingRight.write(180 - wingPos);
  head.write(headPos);
  
  delay(moveSpeed); // Unified speed control
}

void centerAll() {
  wingLeft.write(90);
  wingRight.write(90);
  head.write(90);
  wingPos = 90;
  headPos = 90;
  movingOutward = true;
  delay(200);
}