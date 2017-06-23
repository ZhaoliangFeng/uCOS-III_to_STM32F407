/*****************************************************
* @Author  :  Fengzhaoliang
* @File    :  bsp.c
* @Date    :  2017-04-29
* @Function:  UCOSIII transplant template
******************************************************/
#include "bsp.h"
#include "includes.h"

/*
*********************************************************************************************************
*                                             REGISTERS
*********************************************************************************************************
*/

#define  DWT_CR      *(CPU_REG32 *)0xE0001000
#define  DWT_CYCCNT  *(CPU_REG32 *)0xE0001004
#define  DEM_CR      *(CPU_REG32 *)0xE000EDFC
#define  DBGMCU_CR   *(CPU_REG32 *)0xE0042004

#define  DEM_CR_TRCENA                   (1 << 24)

#define  DWT_CR_CYCCNTENA                (1 <<  0)

unsigned int BSP_CPU_ClkFreq(void)
{
    RCC_ClocksTypeDef   rcc_clocks;
    RCC_GetClocksFreq(&rcc_clocks);
    return ((unsigned int)rcc_clocks.HCLK_Frequency);
}

void SysTick_init(void)
{
    unsigned int cpu_clk_freq;
    unsigned int cnts;
    cpu_clk_freq = BSP_CPU_ClkFreq();
    cnts = cpu_clk_freq / (unsigned int)OS_TICKS_PER_SEC;
    SysTick_Config(cnts);
}

void Bsp_Init(void)
{
    SysTick_init();
    Bsp_Led_Init();
}


#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit (void)
{
    CPU_INT32U  cpu_clk_freq_hz;


    DEM_CR         |= (CPU_INT32U)DEM_CR_TRCENA;                /* Enable Cortex-M3's DWT CYCCNT reg.                   */
    DWT_CYCCNT      = (CPU_INT32U)0u;
    DWT_CR         |= (CPU_INT32U)DWT_CR_CYCCNTENA;

    cpu_clk_freq_hz = BSP_CPU_ClkFreq();
    CPU_TS_TmrFreqSet(cpu_clk_freq_hz);
}
#endif

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR  CPU_TS_TmrRd (void)
{
    return ((CPU_TS_TMR)DWT_CYCCNT);
}
#endif

