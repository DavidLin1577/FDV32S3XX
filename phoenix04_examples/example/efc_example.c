/**
 * @file efc_example.c
 * @author david.lin 
 * @brief
 * @version 1.0
 * @date 2021-06-25
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"
#include "shell.h"

void efc_init(void)
{
	EFC_Init();
}
SHELL_EXPORT_CMD(efc_init, efc_init, first step to init efc);


int efc_singleprogram(int addr, int type, int data)
{
	int ret = 0;

	ret =  EFC_SingleProgram(addr, type, data);

	return ret;
}
SHELL_EXPORT_CMD(efc_singleprogram, efc_singleprogram, addr type<0-2> data);

int efc_example(void)
{
	int ret = 0;
    int addr;
    int type;
    int data;

    EFC_Init();

    //write flash
    addr = 0x1010FE00;
    type = EFC_PRG_BYTE;
    data = 0x5a;
    ret = EFC_SingleProgram(addr, type, data);
    printf("addr %x %x\n", addr, REG32(addr));

    addr = 0x1010FE00;
    type = EFC_PRG_HWORD;
    data = 0x5aa5;
    ret = EFC_SingleProgram(addr, type, data);
    printf("addr %x %x\n", addr, REG32(addr));

    addr = 0x1010FE00;
    type = EFC_PRG_WORD;
    data = 0x5aa5cccc;
    ret = EFC_SingleProgram(addr, type, data);
    printf("addr %x %x\n", addr, REG32(addr));

	return ret;
}
SHELL_EXPORT_CMD(efc_example, efc_example, efc example);
