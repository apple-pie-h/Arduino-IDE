#include <Ultrasonic.h>

// ==== MOTOR DRIVER PINS ====
#define EN_left 11
#define IN1 10
#define IN2 9
#define EN_right 6
#define IN3 8
#define IN4 7

// ==== ULTRASONIC SENSOR PINS ====
#define TRIG_LEFT A0
#define ECHO_LEFT A1
#define TRIG_RIGHT A3
#define ECHO_RIGHT A2
#define TRIG_FRONT A5
#define ECHO_FRONT A4


// ==== SENSOR OBJECTS ====
Ultrasonic leftUltrasonic(TRIG_LEFT, ECHO_LEFT);
Ultrasonic rightUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
Ultrasonic frontUltrasonic(TRIG_FRONT, ECHO_FRONT);


void setup() {
  // put your setup code here, to run once:
  pinMode(EN_left,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN_right,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float d_L = leftUltrasonic.read();
  float d_R = rightUltrasonic.read();
  float d_F = frontUltrasonic.read();

Serial.println("Left:");
Serial.println(d_L);
delay(1000);
Serial.println("Center:");
Serial.println(d_F);
delay(1000);
Serial.println("Right:");
Serial.println(d_R);
delay(1000);

}
