#include "lib_include.h"
#include "platform.h"


int hal_init(void)
{
	//timer 1 init
	PARAM_CHECK(SystemCoreClock < 1000000);
	SYSC->TIMCLKDIV = (SystemCoreClock / 1000000 - 1);
	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIM_PCK | SYSC_CLKENCFG_TIM1_CNT;
	TIM1->CTCG1 = 0;
	TIM1->CTCG2 = 0;

	return 0;
}
