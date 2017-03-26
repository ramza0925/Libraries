#include "stm32f4xx_hal.h"
#include "L3G4200D.h"

/*
 void Gyroscope_Values()
{
   Gyroscope_Values_Raw();

    for (int j = 0; j<3; j++)
   {
      deltaR[j] = (float32)Rm[j] - Ro[j];

      if (abs(deltaR[j]) > Rth[j])
      {
            gyroRate[j] = gyroRate[j] + deltaR[j] * 0.07 * deltaT; // 6230*deltaT = 90 degree
      }
   }
}
 */
//########################################################################################################
void L3G4200D_Setup(I2C_HandleTypeDef *hi2c,GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{

	if(HAL_I2C_IsDeviceReady(hi2c,L3G4200D_I2C_Adress,5,100) == HAL_OK)
	{
		L3G4200DSetup[0]=0x24;
		HAL_I2C_Mem_Write(hi2c,L3G4200D_I2C_Adress,CTRL_REG2,I2C_MEMADD_SIZE_8BIT,L3G4200DSetup,1,50);//Normal mode ,High pass filter cut off frecuency:8
		L3G4200DSetup[0]=0x08;
		HAL_I2C_Mem_Write(hi2c,L3G4200D_I2C_Adress,CTRL_REG3,I2C_MEMADD_SIZE_8BIT,L3G4200DSetup,1,50);// I2_DRDY,I2_WTM,I2_ORun,I2_Empty etkin ,push-pull--FIFO etkin olmadýðý durumda push-pull hariç diðerleri geçersiz
		L3G4200DSetup[0]=0xB0;
		HAL_I2C_Mem_Write(hi2c,L3G4200D_I2C_Adress,CTRL_REG4,I2C_MEMADD_SIZE_8BIT,L3G4200DSetup,1,50);//BDU:1,2000 dps,self-test disabled(normal mode)
		L3G4200DSetup[0]=0x00;
		HAL_I2C_Mem_Write(hi2c,L3G4200D_I2C_Adress,CTRL_REG5,I2C_MEMADD_SIZE_8BIT,L3G4200DSetup,1,50);//HPF disabled - Data in DataReg and FIFO are non-high-passfiltered - Data in DataReg and FIFO are non-highpass- filtered
		L3G4200DSetup[0]=0xCF;
		HAL_I2C_Mem_Write(hi2c,L3G4200D_I2C_Adress,CTRL_REG1,I2C_MEMADD_SIZE_8BIT,L3G4200DSetup,1,50);// 800Hz,30 cut-off/ X,Y,Z etkin*/

		HAL_Delay(252);
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

void L3G4200D_Raw_Values(I2C_HandleTypeDef *hi2c, int16_t *GyroRaw)
	{
			HAL_I2C_Mem_Read(hi2c,L3G4200D_I2C_Adress,STATUS_REG,I2C_MEMADD_SIZE_8BIT,temp1,1,1000);


			while((temp1[0] & 0x08) == 0)//3. bit veri yoklama
		  	  {
			  	  HAL_I2C_Mem_Read(hi2c,L3G4200D_I2C_Adress,STATUS_REG,I2C_MEMADD_SIZE_8BIT,temp1,1,1000);
		  	  }

		  HAL_I2C_Mem_Read(hi2c,L3G4200D_I2C_Adress,OUT_X_L_INC,I2C_MEMADD_SIZE_8BIT,out1,6,1000);

		  GyroRaw[x_eksen] = (int16_t)(((uint16_t)out1[1]<<8) | out1[0]);
		  GyroRaw[y_eksen] = (int16_t)(((uint16_t)out1[3]<<8) | out1[2]);
		  GyroRaw[z_eksen] = (int16_t)(((uint16_t)out1[5]<<8) | out1[4]);
	}

uint8_t L3G4200D_Temperature(I2C_HandleTypeDef *hi2c)
{
	uint8_t t;
	HAL_I2C_Mem_Read(hi2c,L3G4200D_I2C_Adress,OUT_TEMP,I2C_MEMADD_SIZE_8BIT,temp1,1,1000);
	t = (25 - temp1[0]) + 25;
	return t;
}

//########################################################################################################






