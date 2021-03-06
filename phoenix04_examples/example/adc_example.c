/**
 * @file adc_example.c
 * @author david.lin
 * @brief
 * @version 1.0
 * @date 2021-07-06
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#include "lib_include.h"
#include "platform.h"
#include "shell.h"

int adc_example(int time)
{
	int temp = 0;
	SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;
                                               // 软件采样，使用内部参考电压
    switch(time)
    {
    case 0:
		SDC->ME_CTL |= BIT(0);                 // Step1：设置SDC.ME_CLT.ANAC_EN为1，开启ADC工作模块。
		IOM->ADS |= BIT(16);                   // Step2：配置IOM.ADS相应的位，将转化的ADC输入通道配置为模拟端口。
		IOM->AF1 |= 1;
											   // Step3：设置IOM.ADS第14位为1，将ADC外部参考电压引脚配置为模拟端口。
											   // 注：如果ADC参考电压不选择外部参考电压引脚，则此步骤可忽略。
		SYSC->ANCLKDIV &= ~(BITS(0, 3));       // Step4：配置SYSC.ANCLKDIV，设置ADC采样时钟即转换速度。
		SYSC->ANCLKDIV |= (1 << 0);            //       ADC_CLK 4分频，2M
		SYSC->ANCLKDIV &= ~(BITS(4, 8));
		SYSC->ANCLKDIV |= (3 << 4);            //       4分频 500KHz
		ADC->CFG &=~BITS(4,5);                 // Step5：配置ADC.CFG.VRSEL，选择ADC参考电压输入源。
		ADC->CFG |= BIT(0);                    // Step6：设置ADC.CFG.VOLTREF_EN为1，使能内部参考电压模块；设置ADC.CFG.VOLTREF_VRSEL，选择内部参考电压档位。

											   // 注：如果ADC参考电压选择外0部参考电压引脚，则此步骤可忽略。

	    SDC->ANAC_CFG |= BIT(6);               // Step7：设置SDC.ANAC_CFG.BGR_EN为1，使能BGR模块。
	    DelayNus(150);                         // Step8：延时150us，等待BGR模块启动完成。
	    SDC->ANAC_CFG |= BIT(7);               // Step9：设置SDC.ANAC_CFG.ALDO4A_EN为1，使能ALDO4A模块。
	    DelayNus(70);                          // Step10：延时70us，等待ALDO4A模块启动完成。
	    ADC->CFG |= BIT(6);                    // Step11：设置ADC.CFG.BUF_EN为1，使能BUF模块。
	    ADC->CTL |= BIT(0);                    // Step12：设置ADC.CTL.ADC_EN为1，使能ADC模块。
	    DelayNus(2);                           // Step13：延时2us，等待ADC模块启动完成。
	    ADC->CFG &= ~BITS(11,12);              // Step14：配置ADC.CTL.SMP_CYCLE，配置ADC输入信号采样时间。
	    ADC->CFG &= ~BITS(13,14);              // Step15：设置ADC.CTL.SMP_TIME为0，选择单次转换模式。
	    ADC->CFG &= ~(BITS(7,10));             // Step16：配置ADC.CFG.CHSEL，选择待转换的输入通道。
	    ADC->CTL |= BIT(2);                    // Step17：设置ADC.CTL.SST为1，启动ADC转换。
	    while (!(ANAC->ANAC_FLAG & (1 << 0))); // Step18：等待ADC中断或SDC.ANAC_CFG.ADC_INTF为1，读取ADC_VALx寄存器以获取ADC转换结果。
	    temp = ADC->AVG_VAL;                   // 如需对其它通道进行转换，重复执行Step16~Step18。
	    ADC->CTL &= ~BIT(0);                   // Step19：设置ADC.CTL.ADC_EN，ADC.CFG.BUF_EN，SDC.ANAC_CFG.ALDO4A_EN，SDC.ANAC_CFG.BGR_EN为0，关闭BUF模块，ADC模块，ALDO4A模块，BGR模块。
	    ADC->CFG &= ~BIT(6);
		SDC->ANAC_CFG &= ~BIT(7);
		SDC->ANAC_CFG &= ~BIT(6);
		break;
	case 1:
	case 2:
	case 3:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;
		SDC->ME_CTL |= BIT(0);                 // Step1：设置SDC.ME_CLT.ANAC_EN为1，开启ADC工作模块。
		IOM->ADS |= BIT(16);                   // Step2：配置IOM.ADS相应的位，将转化的ADC输入通道配置为模拟端口。
		IOM->AF1 |= 1;
		                                       // Step3：设置IOM.ADS第14位为1，将ADC外部参考电压引脚配置为模拟端口。
		                                       // 注：如果ADC参考电压不选择外部参考电压引脚，则此步骤可忽略。
		SYSC->ANCLKDIV &= ~(BITS(0, 3));       // Step4：配置SYSC.ANCLKDIV，设置ADC采样时钟即转换速度。
		SYSC->ANCLKDIV |= (1 << 0);            //       ADC_CLK 4分频，2M
		SYSC->ANCLKDIV &= ~(BITS(4, 8));
		SYSC->ANCLKDIV |= (3 << 4);            //       4分频 500KHz
		ADC->CFG &=~BITS(4,5);                 // Step5：配置ADC.CFG.VRSEL，选择ADC参考电压输入源。
		ADC->CFG |= BIT(0);                    // Step6：设置ADC.CFG.VOLTREF_EN为1，使能内部参考电压模块；设置ADC.CFG.VOLTREF_VRSEL，选择内部参考电压档位。
		ADC->CFG &=~BITS(1,3);                 // 注：如果ADC参考电压选择外部参考电压引脚，则此步骤可忽略。
		SDC->ANAC_CFG |= BIT(6);               // Step7：设置SDC.ANAC_CFG.BGR_EN为1，使能BGR模块。
		DelayNus(150);                         // Step8：延时150us，等待BGR模块启动完成。
		SDC->ANAC_CFG |= BIT(7);               // Step9：设置SDC.ANAC_CFG.ALDO4A_EN为1，使能ALDO4A模块。
		DelayNus(70);                          // Step10：延时70us，等待ALDO4A模块启动完成。
		ADC->CFG |= BIT(6);                    // Step11：设置ADC.CFG.BUF_EN为1，使能BUF模块。
		ADC->CTL |= BIT(0);                    // Step12：设置ADC.CTL.ADC_EN为1，使能ADC模块。
		DelayNus(2);                           // Step13：延时2us，等待ADC模块启动完成。
		ADC->CFG &= ~BITS(11,12);              // Step14：配置ADC.CTL.SMP_CYCLE，配置ADC输入信号采样时间。
		ADC->CFG |= time << 13;                // Step15：配置ADC.CTL.SMP_TIME，选择转换次数。
		ADC->CFG &= ~(BITS(7,10));             // Step16：配置ADC.CFG.CHSEL，选择待转换的输入通道。
		ADC->CTL |= BIT(2);                    // Step17：设置ADC.CTL.SST为1，启动ADC转换。
		while (!(ANAC->ANAC_FLAG & (1 << 0))); // Step18：等待ADC中断或SDC.ANAC_CFG.ADC_INTF为1，读取ADC_VALx寄存器以获取ADC转换结果。
		temp = ADC->AVG_VAL;                   // 如需对其它通道进行转换，重复执行Step17~Step19。
		ADC->CTL &= ~BIT(0);                   // Step19：设置ADC.CTL.ADC_EN，ADC.CFG.BUF_EN，SDC.ANAC_CFG.ALDO4A_EN，SDC.ANAC_CFG.BGR_EN为0，关闭BUF模块，ADC模块，ALDO4A模块，BGR模块。
		ADC->CFG &= ~BIT(6);
		SDC->ANAC_CFG &= ~BIT(7);
		SDC->ANAC_CFG &= ~BIT(6);
		break;
	default:
		break;
	}

    return temp;
}
SHELL_EXPORT_CMD(adc, adc_example, adc <time> <mode> <value1>);

int adc_temp_sensor(int time, int value)
{
	int adc_value = 0;
	int temperature = 0;
	int vref = 0;

	switch(time)
	{
	case 0:                                    // 软件采样温度，使用内部参考电压
		SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;
		SDC->ME_CTL |= BIT(0);                 // Step1：设置SDC.ME_CLT.ANAC_EN为1，开启ADC工作模块。

		ANAC_WPT_UNLOCK();
		SDC->ANAC_CFG |= BIT(15);              // 使能温度传感器功能
		IOM->ADS      |= BIT(15);              // Step2：配置IOM.ADS相应的位，将转化的ADC输入通道配置为模拟端口。
		ANAC->AINSEL  &= ~BIT(15);             // Step3：GP15使能TRDRV功能
		IOM->OE       |= BIT(15);              // 必须保证IOM.OE=1，IOM.DATA=0，IOM.OTYPE=1
		IOM->DATA     &= ~BIT(15);
		IOM->OTYPE    |= BIT(15);
	                                           // 注：如果ADC参考电压不选择外部参考电压引脚，则此步骤可忽略。
	    SYSC->ANCLKDIV &= ~(BITS(0, 3));       // Step4：配置SYSC.ANCLKDIV，设置ADC采样时钟即转换速度。
		SYSC->ANCLKDIV |= (1 << 0);            //       ADC_CLK 4分频，2M
		SYSC->ANCLKDIV &= ~(BITS(4, 8));
		SYSC->ANCLKDIV |= (3 << 4);            //       4分频 500KHz
	    ADC->CFG &=~BITS(4,5);                 // Step5：配置ADC.CFG.VRSEL，选择ADC参考电压输入源。
	    ADC->CFG |= BIT(0);                    // Step6：设置ADC.CFG.VOLTREF_EN为1，使能内部参考电压模块；设置ADC.CFG.VOLTREF_VRSEL，选择内部参考电压档位。

	                                           // 注：如果ADC参考电压选择外0部参考电压引脚，则此步骤可忽略。
    	ADC->CFG &=~BITS(1,3);
    	switch(value)
    	{
    	case 0:
    		//1.2V
    	    ADC->CFG &= ~BITS(1,3);
    	    ADC->CFG |= 0 << 1;
    	    vref = 1.2;
    	    break;
    	case 1:
    		//1.5V
    		ADC->CFG &= ~BITS(1,3);
    		ADC->CFG |= 1 << 1;
    		vref = 1.5;
    		break;
    	case 2:
    		//2.0V
    		ADC->CFG &= ~BITS(1,3);
    		ADC->CFG |= 2 << 1;
    		vref = 2;
    		break;
    	case 3:
    		//2.5V
    		ADC->CFG &= ~BITS(1,3);
    		ADC->CFG |= 3 << 1;
    		vref = 2.5;
    		break;
    	}
    	ANAC_WPT_UNLOCK();
	    SDC->ANAC_CFG |= BIT(6);               // Step7：设置SDC.ANAC_CFG.BGR_EN为1，使能BGR模块。
	    DelayNus(150);                         // Step8：延时150us，等待BGR模块启动完成。
	    ANAC_WPT_UNLOCK();
	    SDC->ANAC_CFG |= BIT(7);               // Step9：设置SDC.ANAC_CFG.ALDO4A_EN为1，使能ALDO4A模块。
	    DelayNus(70);                          // Step10：延时70us，等待ALDO4A模块启动完成。
	    ADC->CFG |= BIT(6);                    // Step11：设置ADC.CFG.BUF_EN为1，使能BUF模块。
	    ADC->CTL |= BIT(0);                    // Step12：设置ADC.CTL.ADC_EN为1，使能ADC模块。
	    DelayNus(2);                           // Step13：延时2us，等待ADC模块启动完成。
	    ADC->CFG &= ~BITS(11,12);              // Step14：配置ADC.CTL.SMP_CYCLE，配置ADC输入信号采样时间。
	    ADC->CFG &= ~BITS(13,14);              // Step15：设置ADC.CTL.SMP_TIME为0，选择单次转换模式。
	    ADC->CFG &= ~(BITS(7,10));             // Step16：配置ADC.CFG.CHSEL，选择待转换的输入通道。
	    ADC->CTL |= BIT(2);                    // Step17：设置ADC.CTL.SST为1，启动ADC转换。
	    while (!(ANAC->ANAC_FLAG & (1 << 0))); // Step18：等待ADC中断或SDC.ANAC_CFG.ADC_INTF为1，读取ADC_VALx寄存器以获取ADC转换结果。
	    adc_value = ADC->AVG_VAL;              // 如需对其它通道进行转换，重复执行Step16~Step18。
	    printf("adc_value %d\n", adc_value);
	    temperature = 25 + (839 * vref * adc_value /10000);
	    printf("temperature %d\n", temperature);
	    ADC->CTL &= ~BIT(0);                   // Step19：设置ADC.CTL.ADC_EN，ADC.CFG.BUF_EN，SDC.ANAC_CFG.ALDO4A_EN，SDC.ANAC_CFG.BGR_EN为0，关闭BUF模块，ADC模块，ALDO4A模块，BGR模块。
	    ADC->CFG &= ~BIT(6);
	    ANAC_WPT_UNLOCK();
		SDC->ANAC_CFG &= ~BIT(7);
		ANAC_WPT_UNLOCK();
		SDC->ANAC_CFG &= ~BIT(6);
		break;
	case 1:
	case 2:
	case 3:
		SYSC->CLKENCFG |= SYSC_CLKENCFG_ANAC | SYSC_CLKENCFG_IOM;
		SDC->ME_CTL |= BIT(0);                 // Step1：设置SDC.ME_CLT.ANAC_EN为1，开启ADC工作模块。
		IOM->ADS |= BIT(16);                   // Step2：配置IOM.ADS相应的位，将转化的ADC输入通道配置为模拟端口。
		IOM->AF1 |= 1;
		                                       // Step3：设置IOM.ADS第14位为1，将ADC外部参考电压引脚配置为模拟端口。
		                                       // 注：如果ADC参考电压不选择外部参考电压引脚，则此步骤可忽略。
		SYSC->ANCLKDIV &= ~(BITS(0, 3));       // Step4：配置SYSC.ANCLKDIV，设置ADC采样时钟即转换速度。
		SYSC->ANCLKDIV |= (1 << 0);            //       ADC_CLK 4分频，2M
		SYSC->ANCLKDIV &= ~(BITS(4, 8));
		SYSC->ANCLKDIV |= (3 << 4);            //       4分频 500KHz
		ADC->CFG &=~BITS(4,5);                 // Step5：配置ADC.CFG.VRSEL，选择ADC参考电压输入源。
		ADC->CFG |= BIT(0);                    // Step6：设置ADC.CFG.VOLTREF_EN为1，使能内部参考电压模块；设置ADC.CFG.VOLTREF_VRSEL，选择内部参考电压档位。
		ADC->CFG &=~BITS(1,3);                 // 注：如果ADC参考电压选择外部参考电压引脚，则此步骤可忽略。
		ANAC_WPT_UNLOCK();
		SDC->ANAC_CFG |= BIT(6);               // Step7：设置SDC.ANAC_CFG.BGR_EN为1，使能BGR模块。
		DelayNus(150);                         // Step8：延时150us，等待BGR模块启动完成。
		ANAC_WPT_UNLOCK();
		SDC->ANAC_CFG |= BIT(7);               // Step9：设置SDC.ANAC_CFG.ALDO4A_EN为1，使能ALDO4A模块。
		DelayNus(70);                          // Step10：延时70us，等待ALDO4A模块启动完成。
		ANAC_WPT_UNLOCK();
		ADC->CFG |= BIT(6);                    // Step11：设置ADC.CFG.BUF_EN为1，使能BUF模块。
		ADC->CTL |= BIT(0);                    // Step12：设置ADC.CTL.ADC_EN为1，使能ADC模块。
		DelayNus(2);                           // Step13：延时2us，等待ADC模块启动完成。
		ADC->CFG &= ~BITS(11,12);              // Step14：配置ADC.CTL.SMP_CYCLE，配置ADC输入信号采样时间。
		ADC->CFG |= time << 13;                // Step15：配置ADC.CTL.SMP_TIME，选择转换次数。
		ADC->CFG &= ~(BITS(7,10));             // Step16：配置ADC.CFG.CHSEL，选择待转换的输入通道。
		ADC->CTL |= BIT(2);                    // Step17：设置ADC.CTL.SST为1，启动ADC转换。
		while (!(ANAC->ANAC_FLAG & (1 << 0))); // Step18：等待ADC中断或SDC.ANAC_CFG.ADC_INTF为1，读取ADC_VALx寄存器以获取ADC转换结果。
		adc_value = ADC->AVG_VAL;              // 如需对其它通道进行转换，重复执行Step17~Step19。
		printf("adc_value %d\n", adc_value);
		temperature = 25 + (839 * vref * adc_value /10000);
		printf("temperature %d\n", temperature);
		ADC->CTL &= ~BIT(0);                   // Step19：设置ADC.CTL.ADC_EN，ADC.CFG.BUF_EN，SDC.ANAC_CFG.ALDO4A_EN，SDC.ANAC_CFG.BGR_EN为0，关闭BUF模块，ADC模块，ALDO4A模块，BGR模块。
		ADC->CFG &= ~BIT(6);
		ANAC_WPT_UNLOCK();
		SDC->ANAC_CFG &= ~BIT(7);
		ANAC_WPT_UNLOCK();
		SDC->ANAC_CFG &= ~BIT(6);
		break;
	default:
		break;
	}

    return adc_value;
}
SHELL_EXPORT_CMD(adc_temp, adc_temp_sensor, adc time<0-3>  <value>);

