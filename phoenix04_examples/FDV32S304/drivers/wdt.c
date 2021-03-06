/**
 * @file wdt.c
 * @author 
 * @brief
 * @version 0.1
 * @date 2021-06-26
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "wdt.h"
#include "sysc.h"
#include "pmu.h"

/**
 * @brief wdt init
 *
 * @param iDel:  delay ms  (lrc:max 256s xtl:max 64s)
 * @param iClkSrc: LP_CLKSEL_LRC , LP_CLKSEL_XTL
 * @param iOVMode :WDT_OV_INT , WDT_OV_RST
 * note:clk source = lrc  at least 4ms err
 */
void WDT_Init(int iDel, int iClkSrc, eOVModeType iOVMode) 
{
    int iTmp = 1;
    PARAM_CHECK((iClkSrc != LP_CLKSEL_LRC) &&
                (iClkSrc != LP_CLKSEL_XTL));
    PARAM_CHECK((iOVMode != WDT_OV_INT) && (iOVMode != WDT_OV_RST));
    SYSC->CLKENCFG |= SYSC_CLKENCFG_WDT | SYSC_CLKENCFG_PMU;

    iDel = iDel >> 2;
    while (iDel > 2) {
        ++iTmp;
        iDel >>= 1;
    }
    PARAM_CHECK((iTmp > 16) || (iTmp == 0));
    WDT->CR = iTmp - 1;
    if (iOVMode == WDT_OV_INT) {
        WDT->CR |= WDT_CR_WINTEN;
    } else {
        WDT->CR &= ~WDT_CR_WINTEN;
    }
    PMU->WPT = PMU_WPT_V0;
    PMU->WPT = PMU_WPT_V1;
    PMU->CR |= PMU_CR_WDTCLKEN;
    //user start wdt where they need
    //WDT_StartCount();
}

/**
 * @brief wdt deinit
 *
 */
void WDT_DeInit(void) 
{
    PMU->WPT = PMU_WPT_V0;
    PMU->WPT = PMU_WPT_V1;
    PMU->CR &= ~PMU_CR_WDTCLKEN;
    SYSC->CLKENCFG &= ~SYSC_CLKENCFG_WDT;
}
