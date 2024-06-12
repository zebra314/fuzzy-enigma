#include "main.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}


int main(void) 
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();

  MX_USART2_UART_Init();
  MX_UART2_DMA_Init();

  uint8_t outgoing[] = "Done\n";
  int len = sizeof(outgoing) / sizeof(outgoing[0]);
  
  // uint8_t dma_buffer[2000];

  // for(int i = 0; i < 1998; i++) 
  // {
  //   dma_buffer[i] = 'x';
  // }

  // dma_buffer[1998] = '\r';
  // dma_buffer[1999] = '\n';

  while (1) 
  {
    HAL_UART_Transmit_DMA(&huart2, (uint8_t*)outgoing, len);
    // HAL_UART_Transmit(&huart2, (uint8_t*)outgoing, len, 1000);
  }
}
