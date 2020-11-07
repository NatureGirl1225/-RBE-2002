//#include <wpi-32u4-library.h>
#include <Romi32U4.h>
#include <Arduino.h>
#include "chassis.h"

Romi32U4Motors motors; 

float RomiChassis::SpeedLeft(void)
{
    // !!! ATTENTION !!!
    // Assignment 1
    return((count_left-prev_count_left)*C_wheel)/(N_wheel*1000*interval); //[mm/s]
}

float RomiChassis::SpeedRight(void)
{
    // !!! ATTENTION !!!
    // Assignment 1
    return ((count_right-prev_count_right)*C_wheel)/(N_wheel*1000*interval); //[mm/s]
}
/*bool RomiChassis::Timer(float timer_length){
  float start_time = millis();
  float end_time = millis() + timer_length;
  if(millis()>end_time){
  return true;
  }
}*/
void RomiChassis::UpdateEffortDriveWheels(int left, int right)
{ 
    motors.setEfforts(left,right); 
}

void RomiChassis::UpdateEffortDriveWheelsPI(int target_speed_left, int target_speed_right)
{
  
  // !!! ATTENTION !!!
  // Assignment 2
  float prev_sum_error_left = 0;
  float prev_sum_error_right = 0;

  if(!CheckDriveComplete()){
 E_left =  target_speed_left - SpeedLeft();
 sum_error_left = prev_sum_error_left + E_left;
 //The current error is now the previous sum of error. 
    u_left = Kp*E_left + Ki*sum_error_left;
    E_right =  target_speed_right - SpeedRight();
    sum_error_right = prev_sum_error_right + E_right;
    u_right = Kp*E_right + Ki*sum_error_right;
    motors.setEfforts(u_left, u_right);
prev_sum_error_left = sum_error_left;
prev_sum_error_right = sum_error_right;

  }
}

void RomiChassis::SerialPlotter(float SpeedLeft, float SpeedRight, float E_left, float E_right, float u_left, float u_right)
{
    // !!! ATTENTION !!!
    // USE this function for assignment 3!

    Serial.print(SpeedLeft);
    Serial.print('\t');
    Serial.print(SpeedRight);
    Serial.print('\t');
    Serial.print(E_left);
    Serial.print('\t');
    Serial.print(E_right);
    Serial.print('\t');
    Serial.print(u_left);
    Serial.print('\t');
    Serial.print(u_right);
    Serial.print('\t');
    Serial.println();
}

void RomiChassis::MotorControl(void)
{
  uint32_t now = millis();
  if(now - last_update >= interval)
  {    
    prev_count_left = count_left;
    prev_count_right = count_right;
    count_left = encoders.getCountsLeft();
    count_right = encoders.getCountsRight();
    previous_time = millis();
    UpdateEffortDriveWheelsPI(target_left, target_right);
    last_update = now;
  }
}

void RomiChassis::StartDriving(float left, float right, uint32_t duration)
{
  target_left = left; target_right = right;
  start_time = millis();
  last_update = start_time;
  end_time = start_time + duration; //fails at rollover
  UpdateEffortDriveWheelsPI(10, 10);
}

bool RomiChassis::CheckDriveComplete(void)
{
  return millis() >= end_time;
}

void RomiChassis::Stop(void)
{
  target_left = target_right = 0;
  motors.setEfforts(0, 0);
}