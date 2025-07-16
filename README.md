# Arduino-IDE

This repository consists of Arduino Nano code for wall_following and white_line following robot in a black background. 

Use Arduino IDE to run the code or download PlatformIO and run it in Visual Studio Code. The code is in basic C/C++ language.
U will need to add ultrasonic by eric library in Arduino IDE for the headerfile <Ultrasonic.h> and likewise distancesensor for headerfile <DistanceSensor.h>.

The codes are for a robot with 3 InfraRed and 3 UltraSonic sensors. We are using two motors and 2 wheels, 1 free wheel, Arduino Nano, Motor Driver and jumper wires along with breadboard, switch and a 3-cell battery. 

## both_ir_&_ultrasonic_working & both_working_diff_logic_for_ultrasonic 
These file contain both the code for ultrasonic and infrared integrated in one. The logic for ultrasonic is different and depending upon the situtaion one might work and the other might not. In our case, both_working_diff_logic_for_ultrasonic file was the one we used. And since, its basic code in C/C++ u can understand the code logic and flow with a single glance. The code is in its simplest form. 

## ir_only_working_code
This file contains the code only for infrared sensor

## ultrasonic_test 
Using the code here you can test if your sensor is working properly or not. If there is any issues with the sensor you can determine which one of the 3 sensors is having issue using this file. 

## debug
Test sensor readings / movement inference
