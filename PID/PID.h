#ifndef __PID_H
#define __PID_H

//#define deltaT 0.00125F
/*#define Kp 0.6F
#define Ki 0.3F
#define Kd 3*/


typedef struct
{
  float Kp;
  float Ki;
  float Kd;
  float integral,previousError,minOut,maxOut,integralLimitMin,integralLimitMax,
  	  	  	  	  	  	  	  	  derivative,error,samplingInterval,temp;
  float out;
} PID_Instance_f;


void PID_Specific_Init(PID_Instance_f *S);

int16_t PID_i16(PID_Instance_f *S,float target,float current);

float Constrain_f(float test, float a,float b);

#endif
