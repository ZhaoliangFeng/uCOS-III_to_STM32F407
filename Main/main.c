/*****************************************************
* @Author  :  Fengzhaoliang
* @File    :  main.c
* @Date    :  2017-04-29
* @Function:  UCOSIII transplant template
******************************************************/

#include "stm32f4xx.h"
#include "bsp.h"
#include "includes.h"

#define  TEST_TASK_STK_SIZE                   256
#define  TEST_Idle_STK_SIZE                   256
#define  OSTASK_TEST_PRIO            				  3
#define  OSTASK_Idle_PRIO            				  5

static void  Test_Task(void *p_arg);
static void  Test_Idle(void *p_arg);

static  OS_TCB   Test_Task_TCB;
static  OS_TCB   Test_Idle_TCB;

static  CPU_STK  Test_Task_STK[TEST_TASK_STK_SIZE];
static  CPU_STK  Test_Idle_STK[TEST_TASK_STK_SIZE];

void TaskCreateAppTask(void);

static void Test_Task(void *p_arg)
{
	OS_ERR  err;
	(void)p_arg;

	TaskCreateAppTask();
	
	while(1) 
	{
      Led_On();
      OSTimeDlyHMSM(0, 0,1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
      Led_Off();
      OSTimeDlyHMSM(0, 0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

static void Test_Idle(void *p_arg)
{
	OS_ERR  err;
	(void)p_arg;

	while(1) 
	{
      OSTimeDlyHMSM(0, 0, 1,0,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

void TaskCreateAppTask(void)
{
   OS_ERR  err;
								 
   OSTaskCreate((OS_TCB       *)&Test_Idle_TCB,              /* Create the start task                                */
                 (CPU_CHAR     *)"Idle",
                 (OS_TASK_PTR   )Test_Idle,
                 (void         *)0u,
                 (OS_PRIO       )OSTASK_Idle_PRIO,
                 (CPU_STK      *)&Test_Idle_STK[0u],
                 (CPU_STK_SIZE  )Test_Idle_STK[TEST_Idle_STK_SIZE / 10u],
                 (CPU_STK_SIZE  )TEST_Idle_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

}

void TaskCreate(void)
{
    OS_ERR  err;
					 
    OSTaskCreate((OS_TCB       *)&Test_Task_TCB,              /* Create the start task                                */
                 (CPU_CHAR     *)"TEST",
                 (OS_TASK_PTR   )Test_Task,
                 (void         *)0u,
                 (OS_PRIO       )OSTASK_TEST_PRIO,
                 (CPU_STK      *)&Test_Task_STK[0u],
                 (CPU_STK_SIZE  )Test_Task_STK[TEST_TASK_STK_SIZE / 10u],
                 (CPU_STK_SIZE  )TEST_TASK_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

}


int main(){
	OS_ERR  err;
	
	Bsp_Init();
	
	OSInit(&err); 
	/* Create the start task */
	TaskCreate();
	OSStart(&err);
	(void)&err;
	return (0u);
}



