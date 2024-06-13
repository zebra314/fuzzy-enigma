#include "main.h"

int main(void) 
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_DMA_Init();
  MX_USART2_UART_Init();

  char output_buffer[OUTPUT_BUFFER_SIZE];
  int len;
  int i = 123;
  len = snprintf(output_buffer, sizeof(output_buffer), "TO: %d\n", i);

  while (1) 
  {
    HAL_UART_Transmit_DMA(&huart2, (uint8_t*)output_buffer, len);    
    HAL_Delay(100);
  }
}