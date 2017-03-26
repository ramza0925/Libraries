#include "stm32f4xx_hal.h"
#include "Kalman.h"

void  Kalman_Specific_Init(Kalman_Instance *D)
{
	D->K0=0; D->K1=0; D->P00=0; D->P01=0; D->P10=0; D->P11=0; D->Qb=0.003F;
	D->Qteta=0.001F; D->Rangle=0.03F; D->S=0; D->b=0; D->samplingInterval=0.00125F;
	D->tempP00=0; D->tempP01=0; D->teta=0; D->y=0;
}

//###################################################################################

float Kalman(Kalman_Instance *D,float acc,float gyro)
{
    D->teta = D->teta + D->samplingInterval*(gyro - D->b);

    D->P00 = D->P00 + D->samplingInterval *
    		(D->samplingInterval * D->P11-D->P01 - D->P10 + D->Qteta);
    D->P01 = D->P01 - D->samplingInterval * D->P11;
    D->P10 = D->P10 - D->samplingInterval * D->P11;
    D->P11 = D->P11 + D->Qb * D->samplingInterval;

    D->y = acc - D->teta;
    D->S = D->P00 + D->Rangle;

    D->K0 = D->P00/D->S;  D->K1 = D->P10/D->S;

    D->teta = D->teta + D->K0*D->y;
    D->b = D->b + D->K1*D->y;

    D->tempP00=D->P00; D->tempP01=D->P01;
    D->P00 = D->P00 - D->tempP00*(D->K0);
    D->P01 = D->P01 - D->tempP01*(D->K0);
    D->P10 = D->P10 - D->tempP00*(D->K1);
    D->P11 = D->P11 - D->tempP01*(D->K1);

    return D->teta;
}

