/**
 * @file lptimer.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#ifndef __LPTIMER_H__
#define __LPTIMER_H__
#include "../include/phnx05.h"

// register  defines
#define LPTIM_CR_REG               REG32(LPTIM_BASE + 0x00)
#define LPTIM_CFG_REG              REG32(LPTIM_BASE + 0x04)
#define LPTIM_CNT_REG              REG32(LPTIM_BASE + 0x08)
#define LPTIM_INTSTS_REG           REG32(LPTIM_BASE + 0x0c)

// register bits defines
// LPTIM_CR
#define LPTIM_PS                   BITS(4, 6)
#define LPTIM_CR_IE                BIT(3)
#define LPTIM_CR_PITE              BIT(2)
#define LPTIM_CR_EN                BIT(0)
// LPTIM_CFG
#define LPTIM_CFG                  BITS(0, 15)
#define LPTIM_CFG_pos              (0) // 0-0xffff:(x+1)*(1/fclk)
// LPTIM_CNT
#define LPTIM_CNT                  BITS(0, 15)
// LPTIM_STS
#define LPTIM_STS                  BIT(0)

typedef enum _CNT_MODE
{
    LPT_SIG_TIME_CNT = 0,
    LPT_PIT_CNT,
} eCntModeType;

#define LPT_GetIntFlag() ( LPTIM_INTSTS_REG & LPTIM_STS)
#define LPT_ClrIntFlag() { LPTIM_INTSTS_REG = LPTIM_STS; }

// lptimer function
void LPT_Init(u16 iDel, u16 iMode, u16 iPS);
void LPT_DeInit(void);
void LPT_EnableControl(int iCtrl);
void LPT_EnableIRQ(void);
void LPT_DisableIRQ(void);
u16  LPT_GetCount(void);

#endif /*__LPTIMER_H__*/
