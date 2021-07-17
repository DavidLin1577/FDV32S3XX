/**
 * @file d2a_testctrl_example.c
 * @author david.lin
 * @brief
 * @version 1.0
 * @date 2021-06-25
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */
#include "lib_include.h"
#include "platform.h"
#include "shell.h"

#define TEST_PIN          GPIO_PIN12

#define PIN_ON            GPIO_SetPin(TEST_PIN)
#define PIN_OFF           GPIO_ClrPin(TEST_PIN)

int d2a_testctrl_example(int num, int pin)
{
	SYSC->CLKENCFG |= 0xFFFFFFFF;

	switch(num)
	{
	case 0:
		if(pin == 15)
		{
			ANAC_WPT_UNLOCK();
			ANAC->ANAC_TEST    |= 0x5500;

            //d2a_testctrl<0>
			ANAC->ANAC_TESTCTL &= ~BIT(0);
			ANAC->ANAC_TESTCTL |=  BIT(0);

			IOM->ADS           |= BIT(15);
			//[15]=1：GP15选择ATVC
			ANAC->AINSEL       |= BIT(15);

			ANAC_WPT_UNLOCK();
			SDC->ANAC_CFG      &= ~BIT(15);  // 关闭温度传感器功能
		}
		break;
	case 1:
		break;
	case 15:
		if(pin == 15)
		{
		    ANAC_WPT_UNLOCK();
		    ANAC->ANAC_TEST    |= 0x5500;

		    ANAC_WPT_UNLOCK();
		    SDC->ANAC_CFG      |= 0x00C4;

		    ANAC->ANAC_TESTCTL |= BIT(16) | BIT(17) | BIT(19);
		    ANAC->AINSEL       |= BIT(15);
		    IOM->ADS           |= BIT(15);

		    ANAC_WPT_UNLOCK();
		    SDC->ANAC_CFG      &= ~BIT(15);  // 关闭温度传感器功能
		}
		break;
	case 41:
		break;
	default:
		break;
	}

	return num;
}
SHELL_EXPORT_CMD(d2a_test, d2a_testctrl_example, num<1-41> func<4-19>);
