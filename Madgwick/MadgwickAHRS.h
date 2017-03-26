#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h
//----------------------------------------------------------------------------------------------------
#define x_eksen 0
#define y_eksen 1
#define z_eksen 2

typedef struct
{
	float halfx,y;
	long i;
	float beta,deltaT;				// algorithm gain
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

}Madgwick_Instance;


//---------------------------------------------------------------------------------------------------
// Function declarations

void MadgwickAHRSupdateIMU(Madgwick_Instance *M,float *g, float *a,float *q);
void Madgwick_Init(Madgwick_Instance *M);
float invSqrt(Madgwick_Instance *M,float x);

#endif
//=====================================================================================================
// End of file
//=====================================================================================================
