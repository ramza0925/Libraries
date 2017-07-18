#ifndef __Kalman1D_H
#define __Kalman1D_H

#include "stm32f0xx_hal.h"

typedef struct
{
	float xkPrevious ;
	float covarPrevious;

} Kalman1D_Instance;

float Kalman1D(Kalman1D_Instance* S,float x,float R,float Q);
void Kalman1D_Init(Kalman1D_Instance* S);

#endif

