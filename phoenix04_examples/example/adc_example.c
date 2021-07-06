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
#include "shell.h"


int adc_example(void)
{
	// Step1：设置SDC.ME_CLT.ANAC_EN为1，开启ADC工作模块。
	// Step2：配置IOM.ADS相应的位，将转化的ADC输入通道配置为模拟端口。
	// Step3：设置IOM.ADS第14位为1，将ADC外部参考电压引脚配置为模拟端口。
	// 注：如果ADC参考电压不选择外部参考电压引脚，则此步骤可忽略。
	// Step4：配置SYSC.ANCLKDIV，设置ADC采样时钟即转换速度。
	// Step5：配置ADC.CFG.VRSEL，选择ADC参考电压输入源。
	// Step6：设置ADC.CFG.VOLTREF_EN为1，使能内部参考电压模块；设置ADC.CFG.VOLTREF_VRSEL，选择内部参考电压档位。
	// 注：如果ADC参考电压选择外部参考电压引脚，则此步骤可忽略。
	// Step7：设置SDC.ANAC_CFG.BGR_EN为1，使能BGR模块。
	// Step8：延时150us，等待BGR模块启动完成。
	// Step9：设置SDC.ANAC_CFG.ALDO4A_EN为1，使能ALDO4A模块。
	// Step10：延时70us，等待ALDO4A模块启动完成。
	// Step11：设置ADC.CFG.BUF_EN为1，使能BUF模块。
	// Step12：设置ADC.CTL.ADC_EN为1，使能ADC模块。
	// Step13：延时2us，等待ADC模块启动完成。
	// Step14：配置ADC.CTL.SMP_CYCLE，配置ADC输入信号采样时间。
	// Step15：设置ADC.CTL.MULTI_MODE为0，选择单次转换模式。
	// Step16：配置ADC.CFG.CHSEL，选择待转换的输入通道。
	// Step17：设置ADC.CTL.SST为1，启动ADC转换。
	// Step18：等待ADC中断或SDC.ANAC_CFG.ADC_INTF为1，读取ADC_VALx寄存器以获取ADC转换结果。
	// 如需对其它通道进行转换，重复执行Step16~Step18。
	// Step19：设置ADC.CTL.ADC_EN，ADC.CFG.BUF_EN，SDC.ANAC_CFG.ALDO4A_EN，SDC.ANAC_CFG.BGR_EN为0，关闭BUF模块，ADC模块，ALDO4A模块，BGR模块。

    return 0;
}
SHELL_EXPORT_CMD(adc, adc_example, adc example);
