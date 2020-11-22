#include <Arduino.h>
#include <Romi32U4.h>
#include "Behaviors.h"
#include "Speed_controller.h"
#include "IMU.h"

Behaviors collisionBehavior;
SpeedController controller;
IMU_sensor sensor;

void setup() {
  //collisionBehavior.Init();
}

void loop() {
  //collisionBehavior.Run();
  //controller.Turn(90, true);
  sensor.PrintAcceleration();
}