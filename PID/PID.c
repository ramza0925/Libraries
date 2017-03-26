#include "stm32f4xx_hal.h"
#include "math.h"
#include "PID.h"

uint16_t Constrain(float test, uint16_t a,uint16_t b)
{
   if(test < a) return a;
   else if(test > b) return b;
   else return (uint16_t)test;
}

void PID_Specific_Init(PID_Instance_u16 *S)
{
	S->Kd=1.5; S->Ki=0.3; S->Kp=0.6; S->derivative=0; S->error=0;
	S->integral=0; S->previousError=0; S->samplingInterval=0.00125F;
	S->integralLimitMax=7000; S->integralLimitMin=0; S->maxOut=19999;
	S->minOut=0;
}
//################################################################################################

uint16_t PID_u16(PID_Instance_u16 *S,uint16_t value,float target,float current)
{
   S->error = fabs(target - current);

   S->integral = (float)Constrain((S->integral + S->error*S->samplingInterval),
		   	   	   	   	   	   	   	     S->integralLimitMin,S->integralLimitMax);

   S->derivative = (S->error - S->previousError) / S->samplingInterval;

   S->previousError = S->error;

   return (Constrain(value + S->Kp*S->error + S->Ki*S->integral + S->Kd*S->derivative,S->minOut,S->maxOut));
}

