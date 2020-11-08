//#include <wpi-32u4-library.h>
#include <Romi32U4.h>
#include <Arduino.h>
#include "chassis.h"

Romi32U4Motors motors; 

float RomiChassis::SpeedLeft(void)
{
    // !!! ATTENTION !!!
    // Assignment 1
    //Serial.println(count_left-prev_count_left);
    return((count_left-prev_count_left)*C_wheel*1000)/(N_wheel* /*interval*/ (now-last_update)); //[mm/s]
    //Serial.println(now-last_update);
    //Serial.println((count_left-prev_count_left)/(now-last_update));
    //return((count_left-50)*C_wheel)/(N_wheel*1000*interval); //[mm/s]
    
}

float RomiChassis::SpeedRight(void)
{
    // !!! ATTENTION !!!
    // Assignment 1
    return ((count_right-prev_count_right)*C_wheel*1000)/(N_wheel*interval); //[mm/s]
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

void RomiChassis::UpdateEffortDriveWheelsPI(int target_left, int target_right)
{
  
  // !!! ATTENTION !!!
  // Assignment 2


  if(!CheckDriveComplete()){
    //count_left = encoders.getCountsLeft();
    //count_right = encoders.getCountsRight();
    //Serial.println(count_left);
 E_left =  target_left - SpeedLeft();
 //Serial.println(E_left);
 sum_error_left = prev_sum_error_left + E_left;
 //Serial.println(sum_error_left);
 //The current error is now the previous sum of error. 
    u_left = Kp*E_left + Ki*sum_error_left;
   // Serial.println(u_left);
    E_right =  target_right - SpeedRight();
    sum_error_right = prev_sum_error_right + E_right;
    u_right = Kp*E_right + Ki*sum_error_right;
    motors.setEfforts(u_left, u_right);
prev_sum_error_left = sum_error_left;
prev_sum_error_right = sum_error_right;
//prev_count_left = count_left;
//Serial.println(prev_count_left);
//prev_count_right = count_right;
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
  now = millis();
  if((now - last_update) >= interval)
  {    
    prev_count_left = count_left;
    prev_count_right = count_right;
    count_left = encoders.getCountsLeft();
    count_right = encoders.getCountsRight();
    previous_time = millis();
    //Serial.println(previous_time);
    //Serial.println(millis());
    UpdateEffortDriveWheelsPI(u_left, u_right);
    last_update = now;
  }
}

void RomiChassis::StartDriving(float left, float right, uint32_t duration)
{
  target_left = left; 
  target_right = right;
  start_time = millis();
  last_update = start_time;
  end_time = start_time + duration; //fails at rollover
  UpdateEffortDriveWheelsPI(target_left, target_right);
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