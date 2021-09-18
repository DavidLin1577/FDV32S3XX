/**
 * @file anac_example.c
 * @author david.lin
 * @brief
 * @version 1.0
 * @date 2021-06-30
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"
#include "shell.h"


int hrc_example(void)
{
	int temp = 0;

	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC;

	ANAC_WPT_UNLOCK();
    REG32(0x40011C1C) = 0x07;

    return temp;
}
SHELL_EXPORT_CMD(hrc, hrc_example, hrc example);
