#ifndef __NRF24L01_H
#define __NRF24L01_H


//#include "gpio.h"
#include "stm32f4xx_hal.h"
//#include "main.h"

/* Pins configuration */
#define NRF24L01_CE_LOW          HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET)
#define NRF24L01_CE_HIGH         HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET)
#define NRF24L01_CSN_LOW         HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define NRF24L01_CSN_HIGH        HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)

/* Interrupt masks */
#define NRF24L01_IRQ_DATA_READY     0x40 /*!< Data ready for receive */
#define NRF24L01_IRQ_TRAN_OK        0x20 /*!< Transmission went OK */
#define NRF24L01_IRQ_MAX_RT         0x10 /*!< Max retransmissions reached, last transmission failed */

/**
 * @brief  Interrupt structure 
 */
typedef union _TM_NRF24L01_IRQ_t 
{
   struct {
      uint8_t reserved0:4;
      uint8_t MaxRT:1;     /*!< Set to 1 if MAX retransmissions flag is set */
      uint8_t DataSent:1;  /*!< Set to 1 if last transmission is OK */
      uint8_t DataReady:1; /*!< Set to 1 if data are ready to be read */
      uint8_t reserved1:1;
   } F;
   uint8_t Status;          /*!< NRF status register value */
} TM_NRF24L01_IRQ_t;

/**
 * @brief  Transmission status enumeration
 */
typedef enum _TM_NRF24L01_Transmit_Status_t 
{
   TM_NRF24L01_Transmit_Status_Lost = 0x00,   /*!< Message is lost, reached maximum number of retransmissions */
   TM_NRF24L01_Transmit_Status_Ok = 0x01,     /*!< Message sent successfully */
   TM_NRF24L01_Transmit_Status_Sending = 0xFF /*!< Message is still sending */
} TM_NRF24L01_Transmit_Status_t;

/**
 * @brief  Data rate enumeration
 */
typedef enum _TM_NRF24L01_DataRate_t 
{
   TM_NRF24L01_DataRate_2M = 0x00, /*!< Data rate set to 2Mbps */
   TM_NRF24L01_DataRate_1M,        /*!< Data rate set to 1Mbps */
   TM_NRF24L01_DataRate_250k       /*!< Data rate set to 250kbps */
} TM_NRF24L01_DataRate_t;

/**
 * @brief  Output power enumeration
 */
typedef enum _TM_NRF24L01_OutputPower_t 
{
   TM_NRF24L01_OutputPower_M18dBm = 0x00,/*!< Output power set to -18dBm */
   TM_NRF24L01_OutputPower_M12dBm,       /*!< Output power set to -12dBm */
   TM_NRF24L01_OutputPower_M6dBm,        /*!< Output power set to -6dBm */
   TM_NRF24L01_OutputPower_0dBm          /*!< Output power set to 0dBm */
} TM_NRF24L01_OutputPower_t;
	






void TM_NRF24L01_InitPins(void);
void NRF24L01_FlushTX(SPI_HandleTypeDef *hspi);
void NRF24L01_FlushRX(SPI_HandleTypeDef *hspi);
void TM_NRF24L01_WriteRegister(SPI_HandleTypeDef *hspi, uint8_t reg, uint8_t value) ;
void TM_NRF24L01_WriteRegisterMulti(SPI_HandleTypeDef *hspi, uint8_t reg, uint8_t *data, uint8_t count);
uint8_t TM_NRF24L01_ReadRegister(SPI_HandleTypeDef *hspi, uint8_t reg);
void TM_NRF24L01_ReadRegisterMulti(SPI_HandleTypeDef *hspi, uint8_t reg, uint8_t* data, uint8_t count);
void TM_NRF24L01_WriteBit(SPI_HandleTypeDef *hspi, uint8_t reg, uint8_t bit, uint8_t value);
uint8_t TM_NRF24L01_ReadBit(SPI_HandleTypeDef *hspi, uint8_t reg, uint8_t bit);
uint8_t TM_NRF24L01_Init(SPI_HandleTypeDef *hspi, uint8_t channel, uint8_t payload_size);
void TM_NRF24L01_SetMyAddress(SPI_HandleTypeDef *hspi, uint8_t *adr);
void TM_NRF24L01_SetTxAddress(SPI_HandleTypeDef *hspi, uint8_t *adr);
void TM_NRF24L01_PowerUpTx(SPI_HandleTypeDef *hspi);
void TM_NRF24L01_PowerUpRx(SPI_HandleTypeDef *hspi);
void TM_NRF24L01_PowerDown(SPI_HandleTypeDef *hspi);
void TM_NRF24L01_Transmit(SPI_HandleTypeDef *hspi, uint8_t *data);
void TM_NRF24L01_GetData(SPI_HandleTypeDef *hspi ,uint8_t* data);
uint8_t TM_NRF24L01_DataReady(SPI_HandleTypeDef *hspi);
uint8_t TM_NRF24L01_RxFifoEmpty(SPI_HandleTypeDef *hspi);
uint8_t TM_NRF24L01_GetStatus(SPI_HandleTypeDef *hspi);
TM_NRF24L01_Transmit_Status_t TM_NRF24L01_GetTransmissionStatus(SPI_HandleTypeDef *hspi);
void TM_NRF24L01_SoftwareReset(SPI_HandleTypeDef *hspi);
uint8_t TM_NRF24L01_GetRetransmissionsCount(SPI_HandleTypeDef *hspi);
void TM_NRF24L01_SetChannel(SPI_HandleTypeDef *hspi, uint8_t channel);
void TM_NRF24L01_SetRF(SPI_HandleTypeDef *hspi, TM_NRF24L01_DataRate_t DataRate, TM_NRF24L01_OutputPower_t OutPwr);
uint8_t TM_NRF24L01_Read_Interrupts(SPI_HandleTypeDef *hspi, TM_NRF24L01_IRQ_t* IRQ);
void TM_NRF24L01_Clear_Interrupts(SPI_HandleTypeDef *hspi);



#endif
