/**
  ******************************************************************************
  * 
  * @author  Emrah Duatepe
  * @version V1.0
  * @date    01-January-2018
  * @brief   Getting value respectively from UART.
	*
	******************************************************************************
**/

#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include "TRProtocol.h"

HAL_StatusTypeDef TR_Receive(char *rData,char *buffer,int8_t rDataDim)
{	
	int8_t i=0,j=0,k=0,n;
	char data[rDataDim];
	n = rDataDim-1;
	
	while(rData[i]!='T')
	{
		i++;
		if(i>n)
		return HAL_ERROR;
	}
	while(rData[j]!='\n')
	{
		j++;
		if(j>n)
		return HAL_ERROR;		
	}
	while(i<rDataDim)
	{
		data[k] = rData[i];
		i++;
		k++;
	}		
	while(j>-1)
	{
		data[n] = rData[j];
		n--;
		j--;
	}
	for(i=0;i<5;i++)
	{
		buffer[i] = data[i+1];
	}
	
	return HAL_OK;
}
////*****************************************************************************************//
HAL_StatusTypeDef TR_Receive_Multi(char *rData,char *buffer,int8_t rDataDim)
{	
	int8_t i=0,j=0,k=0,n,numberOfint16;
	char data[rDataDim];
	n = rDataDim-1;
	numberOfint16 = (rDataDim-2)/5; // int16_t adedi
	
	while(rData[i]!='T')
	{
		i++;
		if(i>n)
		return HAL_ERROR;
	}
	while(rData[j]!='\n')
	{
		j++;
		if(j>n)
		return HAL_ERROR;		
	}
	while(i<rDataDim)
	{
		data[k] = rData[i];
		i++;
		k++;
	}		
	while(j>-1)
	{
		data[n] = rData[j];
		n--;
		j--;
	}
	for(i=0;i<numberOfint16;i++)
	{
		for(j=0;j<5;j++)
		{
			buffer[j+5*i] = data[(j+1)+(5*i)];
		}
	}
	
	return HAL_OK;
}
////*****************************************************************************************//
void TR_Transmit(int16_t data,char *buffer,int8_t bufferDim)
{
	char temp[5]={0};

	sprintf(temp,"%d",data);
	
	buffer[0] = 'T';
	for(uint8_t i=1;i<=bufferDim-2;i++)
	{
		buffer[i] = temp[i-1];
	}
	buffer[bufferDim-1] = '\n';
}
////*****************************************************************************************//
void TR_Transmit_Multi(int16_t *data,char *buffer,int8_t bufferDim,int8_t dataDim)
{
	uint8_t i=0,j=0;
	char temp[5]={0};
	
	buffer[0] = 'T';
	
	for(i=0;i<dataDim;i++)
	{
		sprintf(temp,"%d",data[i]);

		for(j=1;j<=5;j++)
		{
			buffer[j+5*i] = temp[j-1];
			temp[j-1]=0;
		}
	}
	
	buffer[bufferDim-1] = '\n';
}
