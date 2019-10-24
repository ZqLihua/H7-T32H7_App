/*
*********************************************************************************************************
*
*	模块名称 : 12bit DAC芯片MCP4725驱动模块
*	文件名称 : bsp_i2c_mcp4725.c
*	版    本 : V1.0
*	说    明 : DAC控制波形的直流偏值
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2019-03-31  armfly  正式发布
*
*	Copyright (C), 2018-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名: bsp_InitMCP4725
*	功能说明: 初始化MCP4725
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitMCP4725(void)
{
	MCP4725_SetVolt(0, 1250);
	MCP4725_SetVolt(1, 1250);
}

/*
*********************************************************************************************************
*	函 数 名: MCP4725_SetVolt
*	功能说明: 设置偏值电压
*	形    参: _ch : 0-1
*			  _volt : 偏置电压 mV, 
*	返 回 值: 无
*********************************************************************************************************
*/
void MCP4725_SetVolt(uint8_t _ch, uint16_t _volt)
{
	uint16_t dac;

	dac = (_volt * 4095) / 5080;

	MCP4725_WriteData(_ch, dac);
}

/*
*********************************************************************************************************
*	函 数 名: MCP4725_WriteCmd
*	功能说明: 向芯片发送DAC数据
*	形    参: _ch : 0-1 通道
*			  _usDac : 12bitDAC数据 （0-4095）
*	返 回 值: 无
*********************************************************************************************************
*/
void MCP4725_WriteData(uint8_t _ch, uint16_t _usDac)
{
	if (_usDac > 4095)
	{
		_usDac = 4095;
	}

	i2c_Start(); /* 总线开始信号 */

	i2c_SendByte(MCP4025_SLAVE_ADDRESS + _ch * 2); /* 发送设备地址+写信号 */
	i2c_WaitAck();

	i2c_SendByte(_usDac >> 8); /* 高4bit */
	i2c_WaitAck();

	i2c_SendByte(_usDac); /* 低8bit */
	i2c_WaitAck();

	i2c_Stop(); /* 总线停止信号 */
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
