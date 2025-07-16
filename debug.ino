#include <DistanceSensor.h>

// ==== MOTOR DRIVER PINS ====
#define EN_left 11
#define IN1 10
#define IN2 9
#define EN_right 6
#define IN3 8
#define IN4 7

// ==== IR SENSOR PINS ====
#define IR_L 3
#define IR_C 2
#define IR_R 4

// ==== ULTRASONIC SENSOR PINS ====
#define TRIG_LEFT A0
#define ECHO_LEFT A1
#define TRIG_RIGHT A3
#define ECHO_RIGHT A2
#define TRIG_FRONT A5
#define ECHO_FRONT A4

// ==== SENSOR OBJECTS ====
DistanceSensor leftUltrasonic(TRIG_LEFT, ECHO_LEFT);
DistanceSensor rightUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
DistanceSensor frontUltrasonic(TRIG_FRONT, ECHO_FRONT);

// ==== SENSOR DATA STRUCT ====
struct IRReadings {
  bool left;
  bool center;
  bool right;
};

struct UltrasonicReadings {
  int left;
  int center;
  int right;
};

// ==== SPEED CONSTANTS ====
int baseLeftSpeed = 150;
int baseRightSpeed = 170;
int slightTurnRatio = 60;  // % of base speed
int sharpTurnSpeed = 120;  // lower PWM for rotation


//direction the turn is exeuting to deal with 3 sensor feedback if it appears during a turn 
bool isTurning = false;



// ==== SETUP ====
void setup() {
  Serial.begin(9600);
  initIRSensors();
  initMotorPins();
  Serial.println("Sensor debug start");
  delay(1000);
}

// ==== MAIN LOOP ====
void loop() {
  IRReadings ir = readIRSensors();
  UltrasonicReadings us = readUltrasonicSensors();

debugUltrasonic(us);
delay(1000);
//debugIR(ir);

//movement testing ; comment it out when it moves as expected ; also check the speed in which it moves forward //

// forward();
//delay(500);
//  slightLeft();
//  delay(1000);
//  slightRight();
//  delay(1000);
//  sharpLeft();
//  delay(1000);
//  sharpRight();
//  delay(1000);
//  backward();
//  delay(1000);

  // movement with ir debug 

 
//  decideLineFollow(ir);

  
}

// ==== SENSOR FUNCTIONS ====

void initIRSensors() {
  pinMode(IR_L, INPUT);
  pinMode(IR_C, INPUT);
  pinMode(IR_R, INPUT);
}

IRReadings readIRSensors() {
  IRReadings readings;
  readings.left   = !digitalRead(IR_L);
  readings.center = !digitalRead(IR_C);
  readings.right  = !digitalRead(IR_R);

  return readings;
}

UltrasonicReadings readUltrasonicSensors() {
  UltrasonicReadings readings;
  readings.left   = leftUltrasonic.getCM();
  readings.right  = rightUltrasonic.getCM();
  readings.center = frontUltrasonic.getCM();
  return readings;
}

void debugIR(IRReadings ir) {
  Serial.println("=== IR SENSOR STATUS ===");
  Serial.print("Left: ");   Serial.println(ir.left ? "ON LINE" : "OFF");
  Serial.print("Center: "); Serial.println(ir.center ? "ON LINE" : "OFF");
  Serial.print("Right: ");  Serial.println(ir.right ? "ON LINE" : "OFF");
  Serial.println("========================\n");
}

void debugUltrasonic(UltrasonicReadings us) {
  Serial.println("=== ULTRASONIC SENSOR STATUS ===");
  Serial.print("Left: ");   Serial.print(us.left);   Serial.println(" cm");
  Serial.print("Right: ");  Serial.print(us.right);  Serial.println(" cm");
  Serial.print("Front: ");  Serial.print(us.center); Serial.println(" cm");
  Serial.println("=================================\n");
}

// line following function 
void decideLineFollow(IRReadings ir) {
//  // If robot is in a turn state
//  if (isTurning) {
//    if (!ir.left && ir.center && !ir.right) {
//      isTurning = false;  // Turn complete
//      forward();
//    }
//    return;  // Don't process new commands while turning
//  }
//
//  // Intersection: all 3 sensors detect line
//  if (ir.left && ir.center && ir.right) {
//    isTurning = true;
//    sharpLeft();  // or: forward(), based on your strategy
//    return;
//  }

  // Normal line-following conditions
  if (!ir.left && ir.center && !ir.right) {
    forward();
  } else if (ir.left && ir.center && !ir.right) {
    sharpLeft();
  } else if (!ir.left && ir.center && ir.right) {
    sharpRight();
  } else if (ir.left && !ir.center && !ir.right) {
    slightLeft();
  } else if (!ir.left && !ir.center && ir.right) {
    slightRight();
  } 
  //else {
  // backward();  // all sensors off
 // }
}




// ==== MOTOR CONTROL FUNCTIONS ====

void initMotorPins() {
  pinMode(EN_left, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN_right, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void setLeftMotorDirection(bool forward) {
  digitalWrite(IN1, forward ? HIGH : LOW);
  digitalWrite(IN2, forward ? LOW : HIGH);
}

void setRightMotorDirection(bool forward) {
  digitalWrite(IN3, forward ? HIGH : LOW);
  digitalWrite(IN4, forward ? LOW : HIGH);
}

void setLeftMotorSpeed(int speed) {
  analogWrite(EN_left, constrain(speed, 0, 255));
}

void setRightMotorSpeed(int speed) {
  analogWrite(EN_right, constrain(speed, 0, 255));
}

void debugMovement(const char* action) {
  Serial.print("Motor Action: ");
  Serial.println(action);
}

// ==== MOVEMENT MODES ====

void forward() { 
  setLeftMotorDirection(true);
  setRightMotorDirection(true);
  setLeftMotorSpeed(baseLeftSpeed);
  setRightMotorSpeed(baseRightSpeed);
  debugMovement("Forward");
}

void backward() {
  setLeftMotorDirection(false);
  setRightMotorDirection(false);
  setLeftMotorSpeed(baseLeftSpeed);
  setRightMotorSpeed(baseRightSpeed);
  debugMovement("Backward");
}

void slightLeft() {
  setLeftMotorDirection(true);
  setRightMotorDirection(true);
  setLeftMotorSpeed((baseLeftSpeed * slightTurnRatio) / 100);
  setRightMotorSpeed(baseRightSpeed);
  debugMovement("Slight Left (Circular)");
}

void slightRight() {
  setLeftMotorDirection(true);
  setRightMotorDirection(true);
  setLeftMotorSpeed(baseLeftSpeed);
  
  setRightMotorSpeed((baseRightSpeed * slightTurnRatio) / 100);
  debugMovement("Slight Right (Circular)");
}

void sharpLeft() {
  setLeftMotorDirection(false);
  setRightMotorDirection(true);
  setLeftMotorSpeed(sharpTurnSpeed);
  setRightMotorSpeed(sharpTurnSpeed);
  debugMovement("Sharp Left (Pivot)");
}

void sharpRight() {
  setLeftMotorDirection(true);
  setRightMotorDirection(false);
  setLeftMotorSpeed(sharpTurnSpeed);
  setRightMotorSpeed(sharpTurnSpeed);
  debugMovement("Sharp Right (Pivot)");
}
