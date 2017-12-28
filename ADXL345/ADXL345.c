#include "stm32f4xx_hal.h"
#include "ADXL345.h"
/*

      float x = 0.004*AccRaw[x_eksen];
      float y = 0.004*AccRaw[y_eksen];
      float z = 0.004*AccRaw[z_eksen];

      tetapitch = atan2(x,z) * 57.29577;
      psiroll   = atan2(y,z) * 57.29577;

}

 */

//########################################################################################################
//Setup ADXL345
void ADXL345_Setup(I2C_HandleTypeDef *hi2c,GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{																						
	if(HAL_I2C_IsDeviceReady(hi2c,ADXL345_I2C_Adress,5,100) == HAL_OK)
	{
		ADXL345Setup[0]=0x0D; //800Hz ODR , Normal mode
		HAL_I2C_Mem_Write(hi2c,ADXL345_I2C_Adress,BW_RATE,I2C_MEMADD_SIZE_8BIT,ADXL345Setup,1,50);
		ADXL345Setup[0]=0x08; ////Measurement mode
		HAL_I2C_Mem_Write(hi2c,ADXL345_I2C_Adress,POWER_CTL,I2C_MEMADD_SIZE_8BIT,ADXL345Setup,1,50);
	}
	else
	{
		while(1)
			{
				HAL_GPIO_TogglePin(GPIOx,GPIO_Pin);
				HAL_Delay(250);
			}
	}
}
//########################################################################################################
// Get Raw Values
void ADXL345_Raw_Values(I2C_HandleTypeDef *hi2c,int16_t* AccRaw)
{

		HAL_I2C_Mem_Read(hi2c,ADXL345_I2C_Adress,INT_SOURCE,I2C_MEMADD_SIZE_8BIT,temp,1,1000);

	  while((temp[0] & 0x80) == 0)
	     {
		  	  HAL_I2C_Mem_Read(hi2c,ADXL345_I2C_Adress,INT_SOURCE,I2C_MEMADD_SIZE_8BIT,temp,1,1000);
	     }

	  HAL_I2C_Mem_Read(hi2c,ADXL345_I2C_Adress,DATAXL_INC,I2C_MEMADD_SIZE_8BIT,out,6,1000);

	  AccRaw[x_eksen] = (int16_t)(((uint16_t)out[1]<<8) | out[0]);
	  AccRaw[y_eksen] = (int16_t)(((uint16_t)out[3]<<8) | out[2]);
	  AccRaw[z_eksen] = (int16_t)(((uint16_t)out[5]<<8) | out[4]);
}

//########################################################################################################
