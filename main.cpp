#include <Arduino.h>
#include <Romi32U4.h>
#include "Behaviors.h"
#include "Speed_controller.h"
#include "IMU.h"

Behaviors collisionBehavior;
SpeedController controller;
IMU_sensor sensor;
Romi32U4ButtonA button;

void setup() {
  //collisionBehavior.Init();
}

void loop() {
  //collisionBehavior.Run();
  /*if (button.getSingleDebouncedPress()){
  controller.Turn(90, true);
  }*/
  sensor.PrintAcceleration();
  //sensor.PrintAcceleration();
}