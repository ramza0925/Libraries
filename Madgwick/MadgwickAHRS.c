#include "stm32f4xx_hal.h"
#include "MadgwickAHRS.h"
#include "math.h"

void MadgwickAHRSupdateIMU(Madgwick_Instance *M,float *g, float *a,float *q)
{
	// Rate of change of quaternion from gyroscope
	M->qDot1 = 0.5f * (q[1] * g[x_eksen] - q[2] * g[y_eksen] - q[3] * g[z_eksen]);
	M->qDot2 = 0.5f * (q[0] * g[x_eksen] + q[2] * g[z_eksen] - q[3] * g[y_eksen]);
	M->qDot3 = 0.5f * (q[0] * g[y_eksen] - q[1] * g[z_eksen] + q[3] * g[x_eksen]);
	M->qDot4 = 0.5f * (q[0] * g[z_eksen] + q[1] * g[y_eksen] - q[2] * g[x_eksen]);

		// Normalise accelerometer measurement
		M->recipNorm = invSqrt(M,a[x_eksen] * a[x_eksen] + a[y_eksen] * a[y_eksen] + a[z_eksen] * a[z_eksen]);
		a[x_eksen] *= M->recipNorm;
		a[y_eksen] *= M->recipNorm;
		a[z_eksen] *= M->recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		M->_2q0 = 2.0f * q[0];
		M->_2q1 = 2.0f * q[1];
		M->_2q2 = 2.0f * q[2];
		M->_2q3 = 2.0f * q[3];
		M->_4q0 = 4.0f * q[0];
		M->_4q1 = 4.0f * q[1];
		M->_4q2 = 4.0f * q[2];
		M->_8q1 = 8.0f * q[1];
		M->_8q2 = 8.0f * q[2];
		M->q0q0 = q[0] * q[0];
		M->q1q1 = q[1] * q[1];
		M->q2q2 = q[2] * q[2];
		M->q3q3 = q[3] * q[3];

		// Gradient decent algorithm corrective step
		M->s0 = M->_4q0 * M->q2q2 + M->_2q2 * a[x_eksen] + M->_4q0 * M->q1q1 - M->_2q1 * a[y_eksen];
		M->s1 = M->_4q1 * M->q3q3 - M->_2q3 * a[x_eksen] + 4.0f * M->q0q0 * q[1] - M->_2q0 * a[y_eksen] - M->_4q1 + M->_8q1 * M->q1q1 + M->_8q1 * M->q2q2 + M->_4q1 * a[z_eksen];
		M->s2 = 4.0f * M->q0q0 * q[2] + M->_2q0 * a[x_eksen] + M->_4q2 * M->q3q3 - M->_2q3 * a[y_eksen] - M->_4q2 + M->_8q2 * M->q1q1 + M->_8q2 * M->q2q2 + M->_4q2 * a[z_eksen];
		M->s3 = 4.0f * M->q1q1 * q[3] - M->_2q1 * a[x_eksen] + 4.0f * M->q2q2 * q[3] - M->_2q2 * a[y_eksen];
		M->recipNorm = invSqrt(M,M->s0 * M->s0 + M->s1 * M->s1 + M->s2 * M->s2 + M->s3 * M->s3); // normalise step magnitude

		M->s0 *= M->recipNorm;
		M->s1 *= M->recipNorm;
		M->s2 *= M->recipNorm;
		M->s3 *= M->recipNorm;

		// Apply feedback step
		M->qDot1 -= M->beta * M->s0;
		M->qDot2 -= M->beta * M->s1;
		M->qDot3 -= M->beta * M->s2;
		M->qDot4 -= M->beta * M->s3;

	// Integrate rate of change of quaternion to yield quaternion
	q[0] += M->qDot1 * M->deltaT;
	q[1] += M->qDot2 * M->deltaT;
	q[2] += M->qDot3 * M->deltaT;
	q[3] += M->qDot4 * M->deltaT;

	// Normalise quaternion
	M->recipNorm = invSqrt(M,q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
	q[0] *= M->recipNorm;
	q[1] *= M->recipNorm;
	q[2] *= M->recipNorm;
	q[3] *= M->recipNorm;
}
//---------------------------------------------------------------------------------------------------
float invSqrt(Madgwick_Instance *M,float x)
{
	M->halfx = 0.5f * x;
	M->y = x;
	M->i = *(long*)&M->y;
	M->i = 0x5F3759DF - (M->i>>1);
	M->y = *(float*)&M->i;
	M->y = M->y * (1.5f - (M->halfx * M->y * M->y));
	return M->y;
}
void Madgwick_Init(Madgwick_Instance *M)
{
	M->beta = 0.1; // 2 * proportional gain
	M->deltaT = 0.00125F;
}
