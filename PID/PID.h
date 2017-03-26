
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
  	  	  	  	  	  	  	  	  derivative,error,samplingInterval;
} PID_Instance_u16;

void PID_Specific_Init(PID_Instance_u16 *S);
uint16_t PID_u16(PID_Instance_u16 *S,uint16_t value,float target,float current);
uint16_t Constrain(float test, uint16_t a,uint16_t b);
