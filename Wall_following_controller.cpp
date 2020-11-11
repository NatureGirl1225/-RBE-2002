#include <Romi32U4.h>
#include "Encoders.h"
#include "Wall_following_controller.h"
#include "IR_sensor.h"
#include "Sonar_sensor.h"

IRsensor SharpIR;
SonarSensor HCSR04;
void WallFollowingController::Init(void)
{
    SharpIR.Init();
    HCSR04.Init();
}

float WallFollowingController::Process(float target_distance, float distance)
{
  //assignment 2: write a PD controller that outputs speed as a function of distance error
  distance = SharpIR.ReadData();
  E_distance = target_distance - distance;
    float de = E_distance - prev_e_distance;
  float speed = Kp*E_distance + Kd*de;
  prev_e_distance = E_distance;

  return speed;
} 
/*
float prev_sum_error_left = 0;
  float prev_sum_error_right = 0;
 float E_left =  target_speed_left - SpeedLeft();
 float sum_error_left = prev_sum_error_left + E_left;
 //The current error is now the previous sum of error. 
    float u_left = Kp*E_left + Ki*sum_error_left;
    float E_right =  target_speed_right - SpeedRight();
 float sum_error_right = prev_sum_error_right + E_right;
    float u_right = Kp*E_right + Ki*sum_error_right;
    motors.setEfforts(u_left,u_right);
prev_sum_error_left = sum_error_left;
prev_sum_error_right = sum_error_right;
*/