/**
 * @file timer.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "sysc.h"
#include "timer.h"
#include "iom.h"

/**
 * @brief  timer timing init
 *
 * @param timer :timer 0-4
 * @param delay :us
 */
void Timer_Timing_Init(Timer_t timer,u16 delay,u8 tcks)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER_PCKEN;

    switch(timer)
    {
    case TIMER0:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER0_PCKEN;
    	TIMERS->T0CR |= TIMER0_T0CR_T0EN;
    	TIMERS->T0CR &=~TIMER0_T0CR_PSA;
    	TIMERS->T0CR |= 0x001;
    	TIMERS->T0    = delay & 0xFF;
    	TIMERS->TIE  |= TIMER0_TIE;
    	TIMERS->TIF  |= TIMER0_TIF;
    	break;
    	break;
    case TIMER1:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER1_PCKEN;
    	TIM1->TCR &= ~TIMER_TCR_PWMON;
    	TIM1->TCR &= ~TIMER_TCR_TGC;
    	TIM1->TCR &= ~TIMER_TCR_TCS;
    	TIM1->TCR |= tcks << 2;
    	TIM1->TN   = delay;
    	TIMERS->TIE |= TIMER1_TIE;
    	TIMERS->TIF |= TIMER1_TIF;
    	break;
    case TIMER2:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER2_PCKEN;
    	TIM2->TCR &= ~TIMER_TCR_PWMON;
    	TIM2->TCR &= ~TIMER_TCR_TGC;
    	TIM2->TCR &= ~TIMER_TCR_TCS;
    	TIM2->TCR |= tcks << 2;
    	TIM2->TN   = delay;
    	TIMERS->TIE |= TIMER2_TIE;
    	TIMERS->TIF |= TIMER2_TIF;
    	break;
    case TIMER3:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER3_PCKEN;
    	TIM3->TCR &= ~TIMER_TCR_PWMON;
    	TIM3->TCR &= ~TIMER_TCR_TGC;
    	TIM3->TCR &= ~TIMER_TCR_TCS;
    	TIM3->TCR |= tcks << 2;
    	TIM3->TN   = delay;
    	TIMERS->TIE |= TIMER3_TIE;
    	TIMERS->TIF |= TIMER3_TIF;
    	break;
    case TIMER4:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER4_PCKEN;
    	TIM4->TCR &= ~TIMER_TCR_PWMON;
    	TIM4->TCR &= ~TIMER_TCR_TGC;
    	TIM4->TCR &= ~TIMER_TCR_TCS;
    	TIM4->TCR |= tcks << 2;
    	TIM4->TN   = delay;
    	TIMERS->TIE |= TIMER4_TIE;
    	TIMERS->TIF |= TIMER4_TIF;
    	break;
    default:
    	break;
    }
}

/**
 * @brief  timer Count init
 *
 * @param timer :timer 0-4
 * @param count :count
 */
void Timer_Count_Init(Timer_t timer,u16 count, u16 tcks)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER_PCKEN;

    switch(timer)
    {
    case TIMER0:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER0_PCKEN;
    	TIMERS->T0CR |= TIMER0_T0CR_T0RLDEN;
    	TIMERS->T0CR &=~TIMER0_T0CR_PSA;
    	TIMERS->T0CR |= 0x001;
    	TIMERS->T0RLD = count;
    	TIMERS->TIE |= TIMER0_TIE;
    	TIMERS->TIF |= TIMER0_TIF;
    	break;
    case TIMER1:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER1_PCKEN;
    	TIM1->TCR &= ~TIMER_TCR_PWMON;
    	TIM1->TCR &= ~TIMER_TCR_TGC;
    	TIM1->TCR |= TIMER_TCR_TCS;
    	TIM1->TCR |= tcks << 2;
    	TIM1->TN   = count;
    	TIMERS->TIE |= TIMER1_TIE;
    	TIMERS->TIF |= TIMER1_TIF;
    	break;
    case TIMER2:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER2_PCKEN;
    	TIM2->TCR &= ~TIMER_TCR_PWMON;
    	TIM2->TCR &= ~TIMER_TCR_TGC;
    	TIM2->TCR |= TIMER_TCR_TCS;
    	TIM2->TCR |= tcks << 2;
    	TIM2->TN   = count;
    	TIMERS->TIE |= TIMER2_TIE;
    	TIMERS->TIF |= TIMER2_TIF;
    	break;
    case TIMER3:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER3_PCKEN;
    	TIM3->TCR &= ~TIMER_TCR_PWMON;
    	TIM3->TCR &= ~TIMER_TCR_TGC;
    	TIM3->TCR |= TIMER_TCR_TCS;
    	TIM3->TCR |= tcks << 2;
    	TIM3->TN   = count;
    	TIMERS->TIE |= TIMER3_TIE;
    	TIMERS->TIF |= TIMER3_TIF;
    	break;
    case TIMER4:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER4_PCKEN;
    	TIM4->TCR &= ~TIMER_TCR_PWMON;
    	TIM4->TCR &= ~TIMER_TCR_TGC;
    	TIM4->TCR |= TIMER_TCR_TCS;
    	TIM4->TCR |= tcks << 2;
    	TIM4->TN   = count;
    	TIMERS->TIE |= TIMER4_TIE;
    	TIMERS->TIF |= TIMER4_TIF;
    	break;
    default:
    	break;
    }
}

/**
 * @brief pwm init
 *
 * @param timer :timer 1-4
 * @param freq : Hz
 * @param duty :exp:duty=50 (50%)
 */
void Timer_PWMInit(Timer_t timer, u16 freq, u16 duty)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER_PCKEN;

    switch(timer)
    {
    case TIMER1:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER1_PCKEN;
    	TIM1->TCR   |= TIMER_TCR_PWMON;
    	TIM1->TCR   &= ~TIMER_TCR_TGC;
    	TIM1->TCR   &= ~TIMER_TCR_TCS;
    	TIM1->TCR   |= 0x00 << 2;
    	TIM1->PWMPD  = freq;
    	TIM1->PWMDC  = duty;
    	TIMERS->TIE |= TIMER1_TIE;
    	TIMERS->TIF |= TIMER1_TIF;
    	break;
    case TIMER2:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER2_PCKEN;
    	TIM2->TCR   |= TIMER_TCR_PWMON;
    	TIM2->TCR   &= ~TIMER_TCR_TGC;
    	TIM2->TCR   &= ~TIMER_TCR_TCS;
    	TIM2->TCR   |= 0x00 << 2;
    	TIM2->PWMPD  = freq;
    	TIM2->PWMDC  = duty;
    	TIMERS->TIE |= TIMER2_TIE;
    	TIMERS->TIF |= TIMER2_TIF;
    	break;
    case TIMER3:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER3_PCKEN;
    	TIM3->TCR  |= TIMER_TCR_PWMON;
    	TIM3->TCR  &= ~TIMER_TCR_TGC;
    	TIM3->TCR  &= ~TIMER_TCR_TCS;
    	TIM3->TCR  |= 0x00 << 2;
    	TIM3->PWMPD = freq;
    	TIM3->PWMDC = duty;
    	TIMERS->TIE |= TIMER3_TIE;
    	TIMERS->TIF |= TIMER3_TIF;
    	break;
    case TIMER4:
    	SYSC->CLKENCFG |= SYSC_CLKENCFG_TIMER4_PCKEN;
    	TIM4->TCR   |= TIMER_TCR_PWMON;
    	TIM4->TCR   &= ~TIMER_TCR_TGC;
    	TIM4->TCR   &= ~TIMER_TCR_TCS;
    	TIM4->TCR   |= 0x00 << 2;
    	TIM4->PWMPD  = freq;
    	TIM4->PWMDC  = duty;
    	TIMERS->TIE |= TIMER4_TIE;
    	TIMERS->TIF |= TIMER4_TIF;
    	break;
    default:
    	break;
    }
}
/**
 * @brief Timer deinit
 *
 * @param timer:timer 0-4
 */
void Timer_DeInit(Timer_t timer)
{
    switch(timer)
    {
    case TIMER0:
    	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIMER0_PCKEN;
    	break;
    case TIMER1:
    	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIMER1_PCKEN;
    	break;
    case TIMER2:
    	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIMER2_PCKEN;
    	break;
    case TIMER3:
    	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIMER3_PCKEN;
    	break;
    case TIMER4:
    	SYSC->CLKENCFG &= ~SYSC_CLKENCFG_TIMER4_PCKEN;
    	break;
    default:
    	break;
    }
}
/**
 * @brief timer enable control
 *
 * @param timer : timer 0-4
 * @param iCtrl ENABLE or DISABLE
 */
void Timer_EnableControl(Timer_t timer, u16 iCtrl)
{
    switch(timer)
    {
    case TIMER0:
    	TIMERS->TIF = (1 << 0);
    	if(iCtrl == ENABLE)
    	{
    		TIMERS->T0CR |= TIMER0_CTRL_EN;
    	}
    	else
    	{
    		TIMERS->T0CR &= ~TIMER0_CTRL_EN;
    	}
    	break;
    case TIMER1:
    	if(iCtrl == ENABLE)
    	{
    		TIMERS->TCR1 |= TIMER1_CTRL_EN;
    	}
    	else
    	{
    		TIMERS->TCR1 &= ~TIMER1_CTRL_EN;
    	}
    	break;
    case TIMER2:
    	if(iCtrl == ENABLE)
    	{
    		TIMERS->TCR2 |= TIMER2_CTRL_EN;
    	}
    	else
    	{
    		TIMERS->TCR2 &= ~TIMER2_CTRL_EN;
    	}
    	break;
    case TIMER3:
    	if(iCtrl == ENABLE)
    	{
    		TIMERS->TCR3 |= TIMER3_CTRL_EN;
    	}
    	else
    	{
    		TIMERS->TCR3 &= ~TIMER3_CTRL_EN;
    	}
    	break;
    case TIMER4:
    	if(iCtrl == ENABLE)
    	{
    		TIMERS->TCR4 |= TIMER4_CTRL_EN;
    	}
    	else
    	{
    		TIMERS->TCR4 &= ~TIMER4_CTRL_EN;
    	}
    	break;
    default:
    	break;
    }
}
/**
 * @brief Timer interrupt enable
 *
 * @param timer:timer 0-4
 */
void Timer_EnableIRQ(Timer_t timer)
{
    switch(timer)
    {
    case TIMER0:
    	TIMERS->TIE |= (1 << 0);
    	break;
    case TIMER1:
    	TIMERS->TIE |= (1 << 1);
    	break;
    case TIMER2:
    	TIMERS->TIE |= (1 << 2);
    	break;
    case TIMER3:
    	TIMERS->TIE |= (1 << 3);
    	break;
    case TIMER4:
    	TIMERS->TIE |= (1 << 4);
    	break;
    default:
    	break;
    }
}

/**
 * @brief Timer interrupt disable
 *
 * @param timer:timer 0-4
 */
void Timer_DisableIRQ(Timer_t timer)
{
    switch(timer)
    {
    case TIMER0:
    	TIMERS->TIE &= ~(1 << 0);
    	break;
    case TIMER1:
    	TIMERS->TIE &= ~(1 << 1);
    	break;
    case TIMER2:
    	TIMERS->TIE &= ~(1 << 2);
    	break;
    case TIMER3:
    	TIMERS->TIE &= ~(1 << 3);
    	break;
    case TIMER4:
    	TIMERS->TIE &= ~(1 << 4);
    	break;
    default:
    	break;
    }
}


/**
 * @brief get timer interrupt flag
 *
 * @param timer :timer 0-4
 * @return FlagStatus : SET , RESET
 */
FlagStatus Timer_GetIntFlag(Timer_t timer)
{
    int ret = RESET;

    if(TIMER0 == timer)
    {
    	ret =  (TIMERS->TIF & (1 << 0) ? SET : RESET);
    }
    else if(TIMER1 == timer)
    {
    	ret =  (TIMERS->TIF & (1 << 1) ? SET : RESET);
    }
    else if(TIMER2 == timer)
    {
    	ret =  (TIMERS->TIF & (1 << 2) ? SET : RESET);
    }
    else if(TIMER3 == timer)
    {
    	ret =  (TIMERS->TIF & (1 << 3) ? SET : RESET);
    }
    else if(TIMER4 == timer)
    {
    	ret =  (TIMERS->TIF & (1 << 4) ? SET : RESET);
    }

    return (FlagStatus)ret;
}
/**
 * @brief clear timer interrupt flag
 *
 * @param timer :timer 0-4
 */
void Timer_ClrIntFlag(Timer_t timer)
{
    switch(timer)
    {
    case TIMER0:
    	TIMERS->TIF = (1 << 0);
    	break;
    case TIMER1:
    	TIMERS->TIF = (1 << 1);
    	break;
    case TIMER2:
    	TIMERS->TIF = (1 << 2);
    	break;
    case TIMER3:
    	TIMERS->TIF = (1 << 3);
    	break;
    case TIMER4:
    	TIMERS->TIF = (1 << 4);
    	break;
    default:
    	break;
    }
}
