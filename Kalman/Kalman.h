#ifndef __KALMAN_H
#define __KALMAN_H
//#define deltaT 0.00125F//0.07F * 0.00125F;
//#define Qteta  0.001F
//#define Qb     0.003F
//#define Rangle 0.03F

typedef struct
{
	float P00,P01,P10,P11,teta,b,
	y,S,K0,K1,tempP00,tempP01,samplingInterval,
	Qteta,Qb,Rangle;
} Kalman_Instance;


void  Kalman_Specific_Init(Kalman_Instance *D);
float Kalman(Kalman_Instance *D,float acc,float gyro);

#endif
