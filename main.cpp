#include <Arduino.h>
#include <Romi32U4.h>
#include "chassis.h"


ROBOT_STATE robot_state = ROBOT_IDLE;
RomiChassis chassis = RomiChassis();
Romi32U4ButtonA buttonA = Romi32U4ButtonA();


void setup() {
    Serial.begin(115200);
}

void loop() 
{
  float speed_left = chassis.SpeedLeft();
  float speed_right = chassis.SpeedRight();
  //chassis.SerialPlotter(speed_left, speed_right, chassis.E_left, chassis.E_right, chassis.u_left, chassis.u_right);
  //Serial.println(robot_state);
  switch(robot_state)
  {
    case ROBOT_IDLE:
      if(buttonA.getSingleDebouncedRelease()) 
      {
        chassis.StartDriving(100, 100, 10000); //contains your program that the robot executes when pushbutton A is pressed
        robot_state = ROBOT_DRIVING;
      }
      break;

    case ROBOT_DRIVING:
      chassis.MotorControl();
      if(chassis.CheckDriveComplete()) 
      {
        chassis.Stop();
        robot_state = ROBOT_IDLE;
      }
      if(buttonA.getSingleDebouncedRelease()) 
      {
        chassis.Stop();
        robot_state = ROBOT_IDLE;
      }
      /*if(!chassis.CheckDriveComplete()){
        chassis.UpdateEffortDriveWheelsPI(10,10);
      }*/
  }
}