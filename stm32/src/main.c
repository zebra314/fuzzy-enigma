#include "main.h"

int main(void) 
{
  /* ------------------------- Begin of Initialization ------------------------ */

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_DMA_Init();
  MX_USART2_UART_Init();

  Encoder_Init();

  /* -------------------------- End of Initialization ------------------------- */

  char output_buffer[OUTPUT_BUFFER_SIZE];
  int count, len;

  while (1)
  {
    count = __HAL_TIM_GET_COUNTER(&htim2);
    len = snprintf(output_buffer, sizeof(output_buffer), "TO: %d\n", count);
    HAL_UART_Transmit_DMA(&huart2, (uint8_t*)output_buffer, len);    
    HAL_Delay(100);
  }
}