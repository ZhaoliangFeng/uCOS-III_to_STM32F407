/*****************************************************
* @Author  :  Fengzhaoliang
* @File    :  led.c
* @Date    :  2017-04-29
* @Function:  UCOSIII transplant template
******************************************************/
#include "led.h"

static void Bsp_Led_Gpio_Init()
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOG, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;         
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;            
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                  
    GPIO_Init(GPIOE, &GPIO_InitStructure);                        
}

void  Led_On(void)
{
    GPIO_SetBits(GPIOE, GPIO_Pin_3 | GPIO_Pin_4);
}

void  Led_Off(void)
{
    GPIO_ResetBits(GPIOE, GPIO_Pin_3 | GPIO_Pin_4);
}

void Bsp_Led_Init(void)
{
    Bsp_Led_Gpio_Init();
}

