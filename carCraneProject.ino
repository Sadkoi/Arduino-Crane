/************************************************************************************************************************************
 * This sketch determines the movement of the robot
 * 
 * 
 * motorSpeed(int) --> determines the speed of the dc motor, input: (-255,255)
 * steeringArmPos(int) --> determines angle of steering bar, input: (-90,90)
 * mainArmPos(int) --> determines angle from horizontal of main bar, input: ( -10, 80)
 * secondaryArmPos(int) --> determines angle from horizontal of secondary arm, input (-90,90)
 * clawOnOff(boolean) --> determines if claw is open or closed (true/false) true --> open, false --> closed
 * 
 * 
 * Predetermined behaviour of robot:
 * - place down robot in enclousure
 * - robot turns 45 degrees and moves forward 1 meter (call this vector A) and picks up a lego block
 * - whilst holding the lego, robot executes a 3 point turn such that it travels along vector A to 
 *   its initial point, where it drops the lego
 * - robot repeats the above for 2 more lego blocks that lie at the end of vector B and vector C
 * 
 * 
 * Vector definitions:
 * - Vector A: 1 meter 45 degrees (right) of robot's initial position/orientation
 * - Vector B: 1 meter straight ahead of robot's initial position/orientation
 * - Vector C: 1 meter -45 degrees (left) of robot's initial position/orientation
 **************************************************************************************************************************************/


#include <Servo.h>
//Servo Motor motion 
int MainArmServoPin = 3;
int MainArmServoPin2 = 4;
int SecondaryArmServoPin = 6;
int steeringPin = 5;
int clawServoPin = 9;
int trig = 2;
int echo = 22; 
Servo primaryArm;
Servo primaryArm2;
Servo secondaryArm;
Servo steeringArm;
Servo claw;

//DC Motor 
int motorL_2 = 22;
int motorL_1 = 24;
int motorL_E = 7;
int legLength = 2000;

//miscellaneous variables
boolean doneDidIt;
long duration, inches, cm;
int numLegos;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //pinMode(MainArmServoPin, OUTPUT);
  primaryArm.attach(MainArmServoPin);
  primaryArm2.attach(MainArmServoPin2);
  secondaryArm.attach(SecondaryArmServoPin);
  steeringArm.attach(steeringPin);
  claw.attach(clawServoPin);
  pinMode(motorL_2, OUTPUT);
  pinMode(motorL_1, OUTPUT);
  pinMode(motorL_E, OUTPUT);

  //misc
  doneDidIt = HIGH;
  steeringArm.write(72);
  mainArmPos(0);
  numLegos = 0;
}

void loop() {
  motorSpeed(0);
  secondArmPos(170); //position for picking up --> secondArmPos(170), mainArmPos(8)
  mainArmPos(8);
  secondArmPos(140);
  secondaryArm.write(30);
  mainArmPos(0);
  steeringArm.write(72 + 45);
  steeringArmPos(-45);
  moveTheBot();
  pickUpPos();
  ultraSonicSensor();
  
  delay(5000) // 5 second delay before start
  while(numLegos < 2){
    if(checkBlockage()){ //if route is clear, go ahead
      motorSpeed(255);
    }else{ // if its not, check if its the first blockage or the second
      if(numLegos == 0){ //if first blockage, its the first lego. Pick it up
        
      }else{
        if(numLegos == 1){//if second blockage, its the box. Drop the lego in it.
          
        }
      }
    }
  }
  /*
  if(doneDidIt){
    delay(5000) //five second delay before start
    while( 
    if(checkBlockage()){//if route is clear, move forward
      motorSpeed(255);
    }else{
      




    doneDidIt = LOW;
  }else{
    motorSpeed(0);
    steeringArm.write(72 - 0);
  }
  */
}


bool checkBlockage(){ //returns true if path is clear, returns false if path is blocked by lego
  return true;
}



void drivingArmPos(){
  mainArmPos(0);
  secondArmPos(5);  
}

void pickUpPos(){
  mainArmPos(25);
  secondArmPos(170);
}

void holdingPos(){
  mainArmPos(20);
  secondArmPos(180);
}

void ultraSonicSensor(){
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
 
// The echo pin is used to read the signal: a HIGH
// pulse whose duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
 
  pinMode(echo,INPUT);
  duration = pulseIn(echo, HIGH);
 
  // convert the time into a distance
 
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
 
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
  return duration
}

void motorSpeed(int y){
  if(y >= 0){
    motorBehaviour(y, HIGH, LOW);
  }else{
    motorBehaviour(abs(y), LOW, HIGH);
  }
}

void clawOnOff(boolean x){
  if(x){
    claw.write(170);
  }else{
    claw.write(110);
  }
}
  
void mainArmPos(int angle){
  primaryArm.write(180 - (angle + 40));rite(170);
}

void secondArmPos(int angle){
  secondaryArm.write(angle);
}

void steeringArmPos(int angle){
    steeringArm.write(72 - angle);
}

  primaryArm2.write(angle + 40);  
}

//
void motorBehaviour(int EN_L, boolean L_1, boolean L_2){
  analogWrite(motorL_E, EN_L);
  digitalWrite(motorL_1, L_1);
  digitalWrite(motorL_2, L_2);
}

 
long microsecondsToInches(long microseconds)
{
return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
return microseconds / 29 / 2;
}
