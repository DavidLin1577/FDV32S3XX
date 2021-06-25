/**
 * @file anac.c
 * @author David.lin
 * @brief
 * @version 0.1
 * @date 2021-06-04
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "anac.h"
#include "sysc.h"

/**
 * @brief anac init
 *
 * @param freq :anac module freq (kHz)
 */
void ANAC_Init(int freq)
{
    SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC_PCKEN;
    SystemCoreClockUpdate();
    int tmp = SystemCoreClock / 1000 / freq;
    PARAM_CHECK(tmp < 2);
    int tmp1 = SystemCoreClock / 1000 / (((tmp / 2 - 1) + 1) * 2) / 500000;
    PARAM_CHECK(tmp1 < 2);
    SYSC_SetANAC_CLKDiv(tmp / 2 - 1, tmp1 - 1);
}

/**
 * @brief anac deinit
 *
 */
void ANAC_DeInit(void)
{
    int i;
    SYSC_WPT_UNLOCK();
    SYSC->MSFTRSTCFG |= SYSC_MSFTRSTCFG_ANAC_SFT_RST;
    for (i = 10; i > 0; --i)
        ;
    SYSC->CLKENCFG &= ~SYSC_CLKENCFG_ANAC_PCKEN;
}
