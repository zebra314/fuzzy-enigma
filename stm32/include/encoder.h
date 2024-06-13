#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

#define ENCODER_TIM                            htim2

#define ENCODER_GPIO_PORT GPIOA
#define ENCODER_GPIO_CH1 GPIO_PIN_0
#define ENCODER_GPIO_CH2 GPIO_PIN_1

extern TIM_HandleTypeDef htim2;

typedef enum {
  Incremented = 1,
  Decremented = -1,
  Neutral = 0,
} Encoder_Status;


void Encoder_Config(void);
void Encoder_Init(void);
uint16_t Encoder_Read();
Encoder_Status Encoder_Get_Status();

#endif