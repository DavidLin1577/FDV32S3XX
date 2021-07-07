#include "lib_include.h"
#include "platform.h"


int hal_init(void)
{
	// ��ʼ��Timer1
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_TIM1_CNT;
	SYSC->TIMCLKDIV = SystemCoreClock / 1000000 - 1; // 1M
	TIMERS->INTCLR |= BIT(0); // ��TIMER1�жϱ��
    // 32λ��������ģʽ
	TIM1->CTCG1 = 0;
	TIMERS->CON |= BIT(0); // ʹ��TIMER1

	return 0;
}

void DelayNus(u32 delay)
{
    unsigned int start = TIM1->CTVAL;
    while(TIME_DIFF(start, TIM1->CTVAL) < delay) __asm("NOP");
}
