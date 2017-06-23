#ifndef _BSP_H
#define _BSP_H

#include "stm32f4xx.h"
#include "led.h"
#include "os_cfg.h"

#define BSP_RCC_TO_VAL   0x00000FFF;  /*Max Timeout for RCC register*/

void Bsp_Init(void);

#endif
