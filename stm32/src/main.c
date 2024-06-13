#include "main.h"

int main(void) 
{
  /* ------------------------- Begin of Initialization ------------------------ */

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Encoder_Init();

  /* -------------------------- End of Initialization ------------------------- */

  while (1) {}  
}