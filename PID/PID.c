#include "stm32f4xx_hal.h"
#include "math.h"
#include "PID.h"

float Constrain_f(float test, float a,float b)
{
   if(test < a) return a;
   else if(test > b) return b;
   else return test;
}

void PID_Default_Init(PID_Instance_f *S)
{
	S->Kd=2.3F; S->Ki=0.4F; S->Kp=0.6F; S->derivative=0; S->error=0;
	S->integral=0; S->previousError=0; S->samplingInterval=0.00125F;
	S->integralLimitMax=500; S->integralLimitMin=-500; S->maxOut=500;
	S->minOut=-500;
}//limitmax=7000
//################################################################################################



float PID_f(PID_Instance_f *S,float target,float current)
{
   //S->error = fabs(target - current);
   S->error = target - current;

   S->integral = Constrain_f((S->integral + S->error*S->samplingInterval),
		   	   	   	   	   	   	   	     S->integralLimitMin,S->integralLimitMax);

   S->derivative = (S->error - S->previousError) / S->samplingInterval;

   S->previousError = S->error;

   S->out = S->Kp*S->error + S->Ki*S->integral + S->Kd*S->derivative,S->minOut,S->maxOut;

   return S->out;
}

