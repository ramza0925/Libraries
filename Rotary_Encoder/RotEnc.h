#ifndef __RotEnc_H
#define __RotEnc_H
#include "stm32f0xx_hal.h"
/**
 * @defgroup TM_ROTARY_ENCODER
 * @brief    Rotary encoder library for STM32F4xx devices - http://stm32f4-discovery.com/2014/08/library-26-rotary-encoder-stm32f4
   @Note Codes had been changed as for HAL Library also added an extra function
 * @{
 *
 * This library supports up to 16 rotary encoders at a time.
 * It does not use TIM's rotary input feature but external interrupts for handling.
 *
 *
 * \par Pinout
 *
 * Pinout is fully selectable on rotary initialization.
 *
 * \par Encoder modes
 *
 * By default, if you turn encoder CW, you will increase counter, if CCW, you will decrease counter. Basically, this depends on your wiring for rotary.
 *
 * Library allows you to turn this mode "on the fly" anytime you want. Look for @ref TM_RE_SetMode() function for that.
 
 */
 
 /**
 * @brief  Rotary encoder rotation status
 */
typedef enum {
   TM_RE_Rotate_Increment, /*!< Encoder was incremented */
   TM_RE_Rotate_Decrement, /*!< Encoder was decremented */
   TM_RE_Rotate_Nothing    /*!< Encoder stop at it was before */
} TM_RE_Rotate_t;

/**
 * @brief  Rotary encoder mode selection for rotation
 */
typedef enum {
   TM_RE_Mode_Zero, /*!< Rotary encoder mode zero. It is used for direction when it will be increment od decrement, default used */
   TM_RE_Mode_One   /*!< Rotary encoder mode one. It is used for direction when it will be increment od decrement */
} TM_RE_Mode_t;

/**
 * @brief  Rotary main working structure 
 */
typedef struct {
   int32_t Absolute;        /*!< Absolute rotation from beginning, for public use */
   int32_t Diff;            /*!< Rotary difference from last check, for public use */
   TM_RE_Rotate_t Rotation; /*!< Increment, Decrement or nothing, for public use */
   TM_RE_Mode_t Mode;       /*!< Rotary encoder mode selected */
   uint8_t LastA;           /*!< Last status of A pin when checking. Meant for private use */
   int32_t RE_Count;        /*!< Temporary variable to store data between rotation and user check */
   GPIO_TypeDef* GPIO_A;    /*!< Pointer to GPIOx for Rotary encode A pin. Meant for private use */
   GPIO_TypeDef* GPIO_B;    /*!< Pointer to GPIOx for Rotary encode B pin. Meant for private use */
   uint16_t GPIO_PIN_A;     /*!< GPIO pin for rotary encoder A pin. This pin is also set for interrupt */
   uint16_t GPIO_PIN_B;     /*!< GPIO pin for rotary encoder B pin. */
} TM_RE_t;

/**
 * @}
 */

/**
 * @defgroup TM_ROTARY_ENCODER_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Prepare Rotary Encoder to work
 * @param  *data: Pointer to @ref TM_RE_t structure
 * @retval None
 */
void TM_RE_Init(TM_RE_t* data, GPIO_TypeDef* GPIO_A_Port, uint16_t GPIO_A_Pin, GPIO_TypeDef* GPIO_B_Port, uint16_t GPIO_B_Pin);

/**
 * @brief  Set rotary encoder custom mode
 * @param  *data: Pointer to @ref TM_RE_t structure for specific rotary encoder input
 * @param  mode: Rotary mode you will use. This parameter can be a value of @ref TM_RE_Mode_t enumeration
 * @retval None
 */
void TM_RE_SetMode(TM_RE_t* data, TM_RE_Mode_t mode);

/**
 * @brief  Checks and gets new values of rotary encoder
 * @param  *data: Pointer to @ref TM_RE_t structure
 * @retval Member of @ref TM_RE_Rotate_t
 */
TM_RE_Rotate_t TM_RE_Get(TM_RE_t* data);

/**
 * @brief  Process function.
 * @note   This function have to be called inside your interrupt handler.
 * @param  *data: Pointer to rotary encoder @ret TM_RE_t data where interrupt occured
 * @retval None
 */
 
void RE_Process_IRQ(TM_RE_t* data);
void TM_RE_Process_IRQ(TM_RE_t* data);
void TM_RE_Process_IRQqq(TM_RE_t* data);


#endif
