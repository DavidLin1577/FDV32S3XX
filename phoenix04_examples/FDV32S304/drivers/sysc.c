/**
 * @file sysc.c
 * @author 
 * @brief
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Fanhai Data Tech. (c) 2020
 *
 */

#include "sysc.h"

/**
 * @brief select system clock source
 *
 * @param clkSrc :LP_CLKSEL_LRC , LP_CLKSEL_XTL
 */
void SYSC_SelectClockSource(int clkSrc) 
{
    PARAM_CHECK((iClkSrc != LP_CLKSEL_LRC) &&
                (iClkSrc != LP_CLKSEL_XTL));
    SYSC_WPT_UNLOCK();
    SYSC->CLKCTRCFG &= ~SYSC_CLKCTRCFG_SYS_CLK_SEL;
    SYSC_WPT_UNLOCK();
    SYSC->CLKCTRCFG |= (clkSrc << 4);
}

/**
 * @brief set APB clk div
 *
 * @param div :DIV1-128
 */
void SYSC_SetAPBCLKDiv(int div) 
{
    PARAM_CHECK((div < DIV1) || (div > DIV128));
    SYSC_WPT_UNLOCK();
    SYSC->CLKCTRCFG &= ~SYSC_CLKCTRCFG_APB_CLK_DIV;
    SYSC_WPT_UNLOCK();
    SYSC->CLKCTRCFG |= (div << SYSC_CLKCTRCFG_APB_CLK_DIV_pos);
}
/**
 * @brief set AHB clk div
 *
 * @param div :DIV1-128
 */
void SYSC_SetAHBCLKDiv(int div) 
{
    PARAM_CHECK((div < DIV1) || (div > DIV128));
    SYSC_WPT_UNLOCK();
    SYSC->CLKCTRCFG &= ~SYSC_CLKCTRCFG_AHB_CLK_DIV;
    SYSC_WPT_UNLOCK();
    SYSC->CLKCTRCFG |= (div << SYSC_CLKCTRCFG_AHB_CLK_DIV_pos);
}

/**
 * @brief :reset peripher
 *
 * @param module:  PRST_XX,支持或操作一次设置多个pin
 *
 */
void SYSC_ResetPeripher(eRSTP_Type module) 
{
    int i;
    SYSC_WPT_UNLOCK();
    SYSC->MSFTRSTCFG = module;
    for (i = 5; i > 0; --i)
        ;
}

/**
 * @brief peripher clock enable
 *
 * @param perp : PCLK_EN_xx,支持或操作一次设置多个pin
 */
void SYSC_PCLKEnable(ePCLKEN_Type perp) { SYSC->CLKENCFG |= perp; }
/**
 * @brief peripher clock disable
 *
 * @param perp :PCLK_EN_xx,支持或操作一次设置多个pin
 */
void SYSC_PCLKDisable(ePCLKEN_Type perp) { SYSC->CLKENCFG &= ~perp; }
/**
 * @brief set anac , adc module clock div
 *
 * @param div : val:0-15 ==> div2-32  even
 * @param m500kDiv: val:1-31 ==> DIV2-32
 */
void SYSC_SetANAC_CLKDiv(int div, int m500kDiv) {
    SYSC->ANCLKDIV &= ~SYSC_ANAC_ANAC_SCLK_DIV;
    SYSC->ANCLKDIV |= div << SYSC_ANAC_ANAC_SCLK_DIV_pos;
    SYSC->ANCLKDIV &= ~SYSC_ANAC_500K_CLK_DIV;
    SYSC->ANCLKDIV |= m500kDiv << SYSC_ANAC_500K_CLK_DIV_pos;
}

/**
 * @brief set time1 clock div
 *
 * @param div :DIVxx
 */
void SYSC_SetTimer1ClkDiv(int div) {
    PARAM_CHECK((div < DIV1) || (div > DIV128));
    SYSC->TIMCLKDIV &= 0xff00;
    SYSC->TIMCLKDIV = div;
}
/**
 * @brief set time2 clock div
 *
 * @param div :DIVxx
 */
void SYSC_SetTimer2ClkDiv(int div) {
    PARAM_CHECK((div < DIV1) || (div > DIV128));
    SYSC->TIMCLKDIV &= 0x00ff;
    SYSC->TIMCLKDIV = div<<8;
}
/**
 * @brief 测试时钟输出控制
 *
 * @param div 分频（div（0-127）+1）*2
 * @param clt
 */
void SYSC_TestClkOutControl(int div,ControlStatus clt)
{
    PARAM_CHECK((div < 0) || (div > 127));
    SYSC->TESTCKSEL = (clt << 7) | div;
}
