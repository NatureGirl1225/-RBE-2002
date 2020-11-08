#ifndef __CHASSIS_H
#define __CHASSIS_H

#include <Romi32U4.h>

class RomiChassis{
    private:
        //Romi specific constants:
        // !!! ATTENTION !!!
        const float N_wheel = 1440; //how many counts equate to one wheel rotation?
        const float R_wheel = 35; //what is the radius of a Romi wheel in [mm]
        const float C_wheel = 2*M_PI*R_wheel; //circumference of wheel

        //declare variables for PI controller
        float target_left = 0;
        float target_right = 0;
        float Kp = 0.3;
        float Ki = 0.1;
        


        //encoder and motor objects
        Romi32U4Encoders encoders;
        Romi32U4Motors motors;

        //declare variables for keeping track of counts and conversion to velocities
        uint32_t start_time = 0;
        uint32_t end_time = 0;
        float interval = 100; // in [ms]
        uint32_t last_update = 0;
        int count_left = 0;
        int count_right = 0;
        int prev_count_left = 0;
        int prev_count_right = 0;
        float previous_time = 0;
        float sum_error_left = 0;
        float sum_error_right = 0;
        float prev_sum_error_left = 0;
        float prev_sum_error_right = 0;


    public:
        float SpeedLeft(void);
        float SpeedRight(void);
        float u_left;
        float u_right;
        float E_left = 0; //accumulated error
        float E_right = 0;

        uint32_t now = 0; 
        void UpdateEffortDriveWheels(int a, int b);
        void UpdateEffortDriveWheelsP(int a, int b);
        void UpdateEffortDriveWheelsPI(int a, int b);

        void MotorControl(void);
        void SerialPlotter(float a, float b, float c, float d, float e, float f);

        void StartDriving(float, float, uint32_t);
        bool CheckDriveComplete(void);
        void Stop(void);

        bool Timer(float);

};

enum ROBOT_STATE {ROBOT_IDLE, ROBOT_DRIVING};
#endif