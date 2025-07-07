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


// motro ulto cha ; low high forward jancha 
void setup() {
    pinMode(IR_L, INPUT);
  pinMode(IR_C, INPUT);
  pinMode(IR_R, INPUT);
  // put your setup code here, to run once:
  pinMode(EN_left,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN_right,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

}

void loop() {
   bool irL = !digitalRead(IR_L);  // Active LOW (black line = true)
    bool irC = !digitalRead(IR_C);
    bool irR = !digitalRead(IR_R);
    
  float d_L = leftUltrasonic.getCM();
  float d_R = rightUltrasonic.getCM();
  float d_F = frontUltrasonic.getCM();
  
    if( irC&& !irL && !irR)
{
   forward();
}

// slightlyleft
    else if(irL)
{
   slightleft();

}
// sharpleft
   else if(irL && irC)
{
  if (irC)
  {
   
   forward();
   
  }
  
   
   sharpleft();
   
  
  
}

// slightlyright
    if(irR)
{
   slightright();
}

// sharplyright
    if(irR && irC)
{
    if (irC)
  {
   
   forward();
   
  }
 sharpright();
}

 if (!irR && !irL && !irC && ( d_R<25 || d_L<25))
 {
  wallFollow();
 }
// 
////forward();
////delay(1000);
////backward();
  
}

void motorStop() {
    
   analogWrite(EN_left,0);  //0 to 255
  digitalWrite(IN1,0);
  digitalWrite(IN2,0);
  
   analogWrite(EN_right, 0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,0);
}

// centre ;  past dirn ; dirn l ; dir r ; dlast 
void backward()
{
  
  
   analogWrite(EN_left,150);  //0 to 255
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  
   analogWrite(EN_right, 170);
  digitalWrite(IN3,0);
  digitalWrite(IN4,1);
}
void forward()
{
   analogWrite(EN_left,165);
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  
   analogWrite(EN_right, 180);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);
}
 void sharpleft()
 {
    analogWrite(EN_left,200);
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  
   analogWrite(EN_right, 240);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);
 }

  void slightleft()
 {
    analogWrite(EN_left,150);
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  
   analogWrite(EN_right, 170);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);
 }
 
 void slightright()
 {
      analogWrite(EN_left,150);
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
  
    analogWrite(EN_right, 170);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
 }

 void sharpright()
 {


  
    analogWrite(EN_left,150);
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  
   analogWrite(EN_right, 170);
  digitalWrite(IN3,0);
  digitalWrite(IN4,1);
 }

 void wallFollow(){
  float d_L = leftUltrasonic.getCM();
  float d_R = rightUltrasonic.getCM();
  float d_F = frontUltrasonic.getCM();

float diff= d_R-d_L;


if (diff>3 && d_F>30)
{
  
  slightrightUS();
}
else if (diff<-3 && d_F>30)
{
  slightleftUS();
}
else if (diff>10 && d_F<=13)
{
  sharprightUS();
}
else if (diff<-10 &&d_f<=13)
{
  sharpleft();
}
else 
{
  forwardUS();
}

 }

 void slightrightUS(){
  analogWrite(EN_left,150);
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
  
    analogWrite(EN_right, 170);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
}

void slightleftUS(){
    analogWrite(EN_left,120);
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  
   analogWrite(EN_right, 136);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);

}

void forwardUS(){
   analogWrite(EN_left,159);
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  
   analogWrite(EN_right, 180);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);
}

void sharpleftUS(){

    analogWrite(EN_left,140);
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  
   analogWrite(EN_right, 180);
  digitalWrite(IN3,1);
  digitalWrite(IN4,0);
}

void sharprightUS(){

    analogWrite(EN_left,140);
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  
   analogWrite(EN_right, 160);
  digitalWrite(IN3,0);
  digitalWrite(IN4,1);
}