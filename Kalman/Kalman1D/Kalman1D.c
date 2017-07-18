#include "stm32f0xx_hal.h"
#include "Kalman1D.h"
		
float Kalman1D(Kalman1D_Instance* S,float x,float R,float Q)
{
	float xkPriori = S->xkPrevious;
	float pPriori = S->covarPrevious + Q;
	float K = pPriori / (pPriori + R);
	float xk = xkPriori + K*(x - xkPriori);
	pPriori = (1-K) * S->covarPrevious;
	S->covarPrevious = pPriori;
	S->xkPrevious = xk;
	return xk;
}
void Kalman1D_Init(Kalman1D_Instance* S)
{
	S->covarPrevious = 1;
	S->xkPrevious = 0;
}

