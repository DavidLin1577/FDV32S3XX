/**
 * @file sdc_soft_example.c
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

int sdc_soft_example(void)
{
	int temp_AD;
#if 0
	ANAC->ME_CTL |= BIT(0);                          // Step1：设置ME_CLT.ANAC_EN为1，开启SDC工作模块。
	SYSC->ANCLKDIV &= ~(BITS(0, 3));                 // Step2：配置SYSC.ANCLKDIV，设置ADC采样时钟即转换速度即anac_clk_500k=500KHz。
	SYSC->ANCLKDIV |= (1 << 0);                      //       ADC_CLK 4分频，2M
	SYSC->ANCLKDIV &= ~(BITS(4, 8));
	SYSC->ANCLKDIV |= (3 << 4);                      //       4分频 500KHz
	ANAC->ADC_CFG  &= ~(BITS(4, 5));                 // Step3：配置ADC_CFG.VRSEL，选择ADC参考电压输入源。
	                                                 // Step4：配置ADC_CTL.IE，使能ADC中断。不需要中断
	                                                 // Step5：设置ADC_CFG.VOLTREF_EN为1，使能内部参考电压模块；设置ADC.CFG.VOLTREF_VRSEL，选择内部参考电压档位。
	ANAC->ADC_CFG |= BIT(0);
	ANAC->ADC_CFG &= ~(BITS(1, 3));
	ANAC->ADC_CFG |= (2 << 1);
	ANAC->ADC_CTL &= ~(BITS(4, 5));                  // Step6：配置ADC_CTL.SMP_CYCLE，设置ADC输入信号采样时间。
	ANAC->ADC_CTL |= (3 << 6) | (1 << 3);            // Step7：配置ADC_CTL.SMP_TIME，设置ADC多次转换次数
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG |= BIT(6);	                     // Step6：设置ANAC_CFG.BGR_EN为1，使能BGR模块。
	DelayNus(150);	                                 // Step7：延时150us，等待BGR模块启动完成。
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG |= BIT(7);                        // Step8：设置ANAC_CFG.ALDO4A_EN为1，使能ALDO4A模块。
	DelayNus(70);                                    // Step9：延时70us，等待ALDO4A模块启动完成。
	ANAC->DC_CFG |= BIT(11);                         // Step10:  设置DCBZ_CFG.DISCH为1，开启DCDC输出放电。
	                                                 // Setp13：设置DCBZ_CFG.VOSW为2’b10，DCDC输出和ledDrv连接。
	ANAC->DC_CFG &= ~(BITS(9, 10));
	ANAC->DC_CFG |= (2 << 9);
	                                                 // Setp14：设置DCBZ_CFG.VSL为2’b01，配置DCDC输出为5.5V档，并设置DCBZ_CFG.EN=1，开启DCDC模块。
	ANAC->DC_CFG &= ~(BITS(3, 4));
	ANAC->DC_CFG |= (1 << 3);                        // 5.5v
	ANAC->DC_CFG |= 0x01;
	DelayNus(500);
	while (!(ANAC->ANAC_FLAG & ANAC_ANAC_FLAG_DCDC_VOK)); // 等待FLAG.DC_VOK为1。
	ANAC->DC_CFG &= ~(BIT(11));                      // Setp12： 设置DCBZ_CFG.DISCH为0，关闭DCDC输出放电。
	ANAC->DLY_CFG = (0x32 << 18) | (0x23 << 10);     // Step15：配置寄存器DLY_CFG，确定每个步骤的时间长度。寄存器DLY_CFG的默认值是按照anac_clk_500k=500KHz计算所得。

	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG &= ~(BIT(6) | BIT(7));
	ANAC->ME_CTL |= BIT(0);                          // Step16：配置ME_CTL.ANAC_EN=0x01开启测量模块使能。
	ANAC->ME_CTL |= BIT(4);                          // Step17：配置ME_CTL.ME_AUTO=0x01启动自动测量模式。
	ANAC->ME_CTL |= BITS(5, 6);                      // Step18：配置ME_CTL.MODE_SEL=0x03选择烟雾检测模式。
	ANAC->ME_CTL &= ~(BIT(3));                       // Step19：配置ME_CTL.ME_MODE=0x00选择SST位作为ADC转换触发。
	ANAC->PDSENS_CFG |= BIT(7);                      // Step20：设置PDSENS_CFG.CHRG为1，开启PDSENSOR电容充电。
	DelayNus(1000);                                  // Step21：延时1ms，等待PDSENSOR电容充电完成。设置PDSENS_CFG.CHRG为0。
	ANAC->PDSENS_CFG &= ~(BIT(7));
	                                                 // Setp22：设置LED_CFG.IIRLED_CC，配置LED发光管的电流。
	ANAC->LED_CFG &= ~(BITS(1, 5));
	ANAC->LED_CFG |= (16 << 1);
	ANAC->LED_CFG &= ~(BIT(13));                     // Setp23：设置LED_CFG.LED_SEL，选择LED发光管为红光还是蓝光
	ANAC->ADC_CTL |= BIT(2);                         // Step24：设置ADC_CTL.SST为1，启动ADC转换。

	                                                 // Step25：等待ADC中断或查询ANAC_CFG.ADC_INTF为1，读取ADC_VALx寄存器以获取ADC转换结果即为烟雾PDSENSOR检测值。
	while (!(ANAC->ANAC_FLAG & (1 << 0)));

	temp_AD = ANAC->AVG_VAL;
	ANAC->ANAC_FLAG = (1 << 0);

	ANAC->ADC_CTL &= ~(BIT(0));
	ANAC->ADC_CFG &= ~(BIT(6));
	ANAC_WPT_UNLOCK();
	ANAC->ANAC_CFG &= ~(BIT(6) | BIT(7));
#endif
    return temp_AD;
}
SHELL_EXPORT_CMD(sdc_soft, sdc_soft_example, sdc soft example);
