#include "encoder.h"

/* ---------------------------- Global variables ---------------------------- */
TIM_HandleTypeDef htim2;
static uint16_t newCount;
static uint16_t prevCount;
int count = 0;
int len = 0;

/* ----------------------- Begin of Interrupt Handler ----------------------- */

/**
 * @brief Hall Trigger detection callback in non blocking mode.
 * 
 * @param htim 
 */

void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim) 
{
  // if (htim->Instance == TIM2) 
  // {
  //   count = __HAL_TIM_GET_COUNTER(&htim2);
  //   len = snprintf(output_buffer, sizeof(output_buffer), "TO: %d\n", count);
  //   HAL_UART_Transmit_DMA(&huart2, (uint8_t*)output_buffer, len);
  // }
  count = 123;
  len = snprintf(output_buffer, sizeof(output_buffer), "TO: %d\n", count);
  HAL_UART_Transmit_DMA(&huart2, (uint8_t*)output_buffer, len);
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

/* ------------------------ End of Interrupt Handler ------------------------ */

// Encoder_Status Encoder_Get_Status()
// {
//   newCount = Encoder_Read();
//   if (newCount != prevCount)
//   {
//     if (newCount > prevCount)
//     {
//       prevCount = newCount;
//       return Incremented;
//     }
//     else
//     {
//       prevCount = newCount;
//       return Decremented;
//     }
//   }
//   return Neutral;
// }

/**
  * @brief TIM2 Initialization Function (Encoder Mode)
  * @param None
  * @retval None
  */

void MX_TIM2_Encoder_Init(void)
{
  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;     // Capture performed each time an edge is detected on the capture input
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;     // Capture performed each time an edge is detected on the capture input
  sConfig.IC2Filter = 0;
  
  if(HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Base_Start_IT(&htim2);
}

/**
* @brief TIM_Encoder MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_encoder: TIM_Encoder handle pointer
* @retval None
*/

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* htim_encoder)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim_encoder->Instance==TIM2)
  {
    // Peripheral clock enable
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /** TIM2 GPIO Configuration    
     *  PA0-WKUP     ------> TIM2_CH1
     *  PA1     ------> TIM2_CH2 
    */

    GPIO_InitStruct.Pin = ENCODER_GPIO_CH1|ENCODER_GPIO_CH2;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(ENCODER_GPIO_PORT, &GPIO_InitStruct);
  }

}

/**
* @brief TIM_Encoder MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim_encoder: TIM_Encoder handle pointer
* @retval None
*/

void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef* htim_encoder)
{
  if(htim_encoder->Instance==TIM2)
  {

  // Peripheral clock disable 
  __HAL_RCC_TIM2_CLK_DISABLE();
  
  /** TIM2 GPIO Configuration    
   *  PA0-WKUP ------> TIM2_CH1
   *  PA1      ------> TIM2_CH2 
  */

  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1);

  }
}