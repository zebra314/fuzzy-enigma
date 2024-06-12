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
  MX_USART2_DMA_Init();
  MX_USART2_UART_Init();

  uint8_t outgoing[] = "Done\n";
  int len = sizeof(outgoing) / sizeof(outgoing[0]);

  while (1) 
  {
    HAL_UART_Transmit_DMA(&huart2, outgoing, len);    
    HAL_Delay(100);
  }
}
