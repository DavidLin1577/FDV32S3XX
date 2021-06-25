/**
 * @file wdt_rst_example.c
 * @author david.lin 
 * @brief
 * @version 1.0
 * @date 2021-06-25
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"

#define LED_PIN GPIO_PIN8

#define LED_ON GPIO_SetPin(LED_PIN)
#define LED_OFF GPIO_ClrPin(LED_PIN)

int wdt_rst_example(void)
{
    int i, j;
    printf("test\r\n");
    GPIO_PinConfigure(LED_PIN, DISABLE, ENABLE, ENABLE, DISABLE, DISABLE);
    for (i = 0; i < 4; ++i) {
        LED_ON;
        for (j = 1000000; j > 0; j--)
            ;
        LED_OFF;
        for (j = 1000000; j > 0; j--)
            ;
    }
    WDT_Init(4, LP_CLKSEL_LRC, WDT_OV_RST);
    while (1)
        ;
}
