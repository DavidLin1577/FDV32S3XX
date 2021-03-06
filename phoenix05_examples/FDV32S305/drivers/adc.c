/**
 * @file adc.c
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-06-8
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "sysc.h"
#include "anac.h"
#include "adc.h"

/**
 * @brief adc init
 *
 * @param chn ADC_CHN_xxx
 * @param buffEn ENABLE , DISABLE
 * @param verfSel ADC_VREF_SEL_xxx
 * @param verfVol ADC_VREF_VOLT_xxx
 * @param smpTimes ADC_SMP_TIMS_x
 * @param smpCycle ADC_SMP_CYCLE_xx
 */
void ADC_Init(int chn, int buffEn, int verfSel, int verfVol, int smpTimes, int smpCycle)
{

}
/**
 * @brief ADC enalble
 *
 */
void ADC_Enable(void)
{
	ADC->CFG |= ADC_CFG_ADC_EN_ENABLE;
}

/**
 * @brief ADC disable
 *
 */
void ADC_Disable(void)
{
	ADC->CFG &= ~ADC_CFG_ADC_EN_ENABLE;
}

/**
 * @brief ADC enable interrupt
 *
 */
void ADC_EnableIRQ(void)
{
	ADC->CFG |= ADC_CFG_ADC_IE_ENABLE;
}


/**
 * @brief ADC disable interrupt
 *
 */
void ADC_DisableIRQ(void)
{
	ADC->CFG &= ~ADC_CFG_ADC_IE_ENABLE;
}

/**
 * @brief ADC start convert
 *
 */
void ADC_StartConvert(void)
{
	ADC->CFG |= ADC_CFG_SST_START;
}

/**
 * @brief ADC get single convert result value
 *
 * @param none
 * @return u16 :val
 */
u16 ADC_GetSingleResultValue(void)
{
    return ADC->DATA;
}

/**
 * @brief get interrupt flag
 *
 * @return BOOL
 */
BOOL ADC_GetIntFlag(void)
{
	return (ADC->INTF & 0x01) ? TRUE : FALSE;
}

/**
 * @brief clear interrupt flag
 *
 */
void ADC_ClrIntFlag(void)
{
	ADC->INTF |= 0x01;
}
