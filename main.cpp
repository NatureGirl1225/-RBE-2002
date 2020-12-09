#include <Arduino.h>
#include <Romi32U4.h>
#include "Behaviors.h"
#include "Speed_controller.h"
#include "IMU.h"
#include <LSM6.h>

//Behaviors collisionBehavior;
//SpeedController controller;
IMU_sensor sensor;
//Romi32U4ButtonA button;
int now = millis();

void setup() {
  //collisionBehavior.Init();
  Serial.begin(9600);
}

void loop() {
  //collisionBehavior.Run();
  /*if (button.getSingleDebouncedPress()){
  controller.Turn(90, true);
  }*/
  
  if (millis() - now >= 50){
    sensor.PrintAcceleration();
    now = millis();
    
   
  }
}