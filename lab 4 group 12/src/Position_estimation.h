#ifndef POSITION_ESTIMATION
#define POSITION_ESTIMATION

#include <Romi32U4.h>

class Position{
    private:
        float x, y, theta;
        float x_theoretical, y_theoretical, theta_theoretical;
        unsigned long time_prev, time_now;
        const float l = 0.142875; //assignment
        float ICC, w, v; //w is omega I'm sorry
        float ICC_theoretical, w_theoretical, v_theoretical;
        
        
    public:
        struct pose_data {
            float X;
            float Y;
            float THETA;
        };
        void Init(void);
        void UpdatePose(float,float);
        pose_data ReadPose(void);
        void PrintPose(void);
        void Stop(void);
};

#endif