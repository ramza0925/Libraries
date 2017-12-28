#include "stm32f4xx_hal.h"
#include "math.h"
#include "PID.h"

float Constrain_f(float test, float a,float b)
{
   if(test < a) return a;
   else if(test > b) return b;
   else return test;
}
int16_t Constrain_i16(float test, float a,float b)
{
   if(test < a) return a;
   else if(test > b) return b;
   else return (int16_t)test;
}

//################################################################################################
void PID_Default_Init(PID_Instance_f *S)
{
	S->Kd=0.0F; S->Ki=0.0F; S->Kp=0.0F; S->derivative=0; S->error=0;
	S->integral=0; S->previousError=0; S->samplingInterval=0.00125F;
	S->integralLimitMax=50;
	S->integralLimitMin=-50;
}
//################################################################################################



float PID_f(PID_Instance_f *S,float target,float current)
{
   //S->error = fabs(target - current);
   S->error = target - current;

	 S->integral = S->integral + S->error*S->samplingInterval;
	
   S->derivative = (S->error - S->previousError) / S->samplingInterval;

   S->previousError = S->error;

   S->out = S->Kp*S->error + S->Ki*S->integral + S->Kd*S->derivative;

   return S->out;
}

float PID_f2(PID_Instance_f *S,float target,float current,float w)
{
   //S->error = fabs(target - current);
   S->error = target - current;

   S->integral = S->integral + w;
		   	   	   	   	   	   	   	    

   S->derivative = (w - S->previousError) / S->samplingInterval;

   S->previousError = w;

   S->out = S->Kp*S->error + S->Ki*S->integral + S->Kd*S->derivative;

   return S->out;
}
