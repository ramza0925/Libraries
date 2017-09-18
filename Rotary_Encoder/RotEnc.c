#include "stm32f0xx_hal.h"
#include "RotEnc.h"

#define RETURN_WITH_STATUS(p, s)    (p)->Rotation = s; return s

void TM_RE_Init(TM_RE_t* data, GPIO_TypeDef* GPIO_A_Port, uint16_t GPIO_A_Pin, GPIO_TypeDef* GPIO_B_Port, uint16_t GPIO_B_Pin) {
   /* Save parameters */
   data->GPIO_A = GPIO_A_Port;
   data->GPIO_B = GPIO_B_Port;
   data->GPIO_PIN_A = GPIO_A_Pin;
   data->GPIO_PIN_B = GPIO_B_Pin;
   
   /* Set default mode */
   data->Mode = TM_RE_Mode_Zero;
   
   /* Set default */
   data->RE_Count = 0;
   data->Diff = 0;
   data->Absolute = 0;
   data->LastA = 1;
}
/**********************************************************************************************************/
TM_RE_Rotate_t TM_RE_Get(TM_RE_t* data) {
   /* Calculate everything */
   data->Diff = data->RE_Count - data->Absolute;
   data->Absolute = data->RE_Count;
   
   /* Check */
   if (data->RE_Count < 0) {
      RETURN_WITH_STATUS(data, TM_RE_Rotate_Decrement);
   } else if (data->RE_Count > 0) {
      RETURN_WITH_STATUS(data, TM_RE_Rotate_Increment);
   }
   
   RETURN_WITH_STATUS(data, TM_RE_Rotate_Nothing);
}
/**********************************************************************************************************/
void TM_RE_SetMode(TM_RE_t* data, TM_RE_Mode_t mode) {
   /* Set mode */
   data->Mode = mode;
}
/**********************************************************************************************************/
/** @brief iki adimda bir sayiyor
*/
void TM_RE_Process_IRQ(TM_RE_t* data) 
{
   uint8_t now_a;
   uint8_t now_b;
   
   /* Read inputs */
   now_a = HAL_GPIO_ReadPin(data->GPIO_A, data->GPIO_PIN_A);
   now_b = HAL_GPIO_ReadPin(data->GPIO_B, data->GPIO_PIN_B);
   
   /* Check difference */
   if (now_a != data->LastA) 
		 {
      data->LastA = now_a;
      
      if (data->LastA == 0) 
				{
         /* Check mode */
         if (data->Mode == TM_RE_Mode_Zero) 
				 {
            if (now_b == 1) {data->RE_Count--;} 
						else { data->RE_Count++; }
         } 
				 
				 else 
				 {
            if (now_b == 1) {data->RE_Count++;} 
						else {data->RE_Count--;}
         }
      }
   }
}
/**********************************************************************************************************/
/** @brief Bu fonksiyon her adimda bir sayar.
*/
void RE_Process_IRQ(TM_RE_t* data)
{
		uint8_t aState;
	
		aState = HAL_GPIO_ReadPin(data->GPIO_A, data->GPIO_PIN_A);

   if (aState != data->LastA)
		 {     
     if (HAL_GPIO_ReadPin(data->GPIO_B, data->GPIO_PIN_B) != aState) data->RE_Count++;
		 else data->RE_Count--;
     }
		 data->LastA = aState;
} 
/**********************************************************************************************************/
//not working
void TM_RE_Process_IRQqq(TM_RE_t* data)
{
	 uint8_t now_a,temp,temp1;
   uint8_t now_b;
	
   
   /* Read inputs */
   now_a = HAL_GPIO_ReadPin(data->GPIO_A, data->GPIO_PIN_A);
   now_b = HAL_GPIO_ReadPin(data->GPIO_B, data->GPIO_PIN_B);
	now_a = now_a << 1;
	temp = now_a | now_b;
	if((data->LastA & 2)^(temp & 1)) data->RE_Count++; 
	else data->RE_Count--;
	
	data->LastA = temp;
	
}

