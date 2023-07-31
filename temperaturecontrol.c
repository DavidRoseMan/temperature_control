#include "temperaturecontrol.h"

unsigned int code Temperature_Convert_Data[112] =
	{
		47354, 45165, 43082, 41083, 39162, 37320, 35653, 33897, 32323, 30822, //-10℃～-1�?
		29394, 28041, 26760, 25548, 24403, 23319, 22292, 21317, 20390, 19505, //  0℃～ 9�?
		18659, 17863, 17107, 16388, 15703, 15052, 14432, 13641, 13278, 12741, // 10℃～19�?
		12229, 11741, 11257, 10830, 10406, 10000, 9612, 9242, 8888, 8549,	  // 20℃～29�?
		8225, 7915, 7619, 7335, 7063, 6802, 6553, 6314, 6085, 5865,			  // 30℃～39�?
		5654, 5452, 5258, 5072, 4893, 4721, 4556, 4398, 4245, 4099,			  // 40℃～49�?
		3958, 3822, 3692, 3657, 3446, 3330, 3218, 3110, 3007, 2907,			  // 50℃～59�?
		2810, 2718, 2629, 2543, 2460, 2380, 2303, 2229, 2158, 2089,			  // 60℃～69�?
		2024, 1960, 1899, 1840, 1784, 1730, 1678, 1627, 1580, 1534,			  // 70℃～79�?
		1491, 1450, 1409, 1371, 1335, 1299, 1266, 1229, 1195, 1160,			  // 80℃～89�?
		1124, 1093, 1063, 1034, 1006, 979, 953, 928, 903, 880,				  // 90℃～99�?
		857, 0,																  // 100�?
};

unsigned char code Calculate_Data[8] = {
	0x80,
	0x40,
	0x20,
	0x10,
	0x08,
	0x04,
	0x02,
	0x01,
};

void Init_handle_heat(handle_heat_type *p_temp) // 初始化函�?
{
	p_temp->set = 0;
	p_temp->value = 100;
	p_temp->ctrl = 0;
	p_temp->count = 0;
}

void Set_temperature_handle_heat(handle_heat_type *p_temp, unsigned char value_set) // 设定温度�?
{
	p_temp->set = value_set;
}

unsigned char Get_ctrldata_handle_heat(handle_heat_type *p_temp, unsigned int ADC_data) // �?2.5秒处理一�?,返回当前温度�?
{
	p_temp->value = TemperatureTest(ADC_data);
	if (ADC_data < 886)
		p_temp->ctrl = TemperatureCtrl(p_temp->set, p_temp->value); // 热敏电阻值大�?65K被视做开路损坏，否则程序计算将出现溢出错误�?
	else
		p_temp->ctrl = 0; // 热敏电阻出错�?
	return p_temp->value;
}

void Close_handle_heat(handle_heat_type *p_temp) // 关闭发热功能
{
	p_temp->ctrl = 0;
	p_temp->count = 0;
}

bit Set_output_handle_heat(handle_heat_type *p_temp) // �?1ms处理一�?
{
	unsigned char a;
	bit HotCtrl_IO = 0;

	p_temp->count++;
	if (p_temp->count >= 4 + 0)
		p_temp->count = 0;
	a = p_temp->ctrl;
	if (a)
	{
		if (a < 3)
			a = 3;
	}
	if (p_temp->count < a)
		HotCtrl_IO = 1;
	else
		HotCtrl_IO = 0;

	return HotCtrl_IO;
}

unsigned char TemperatureCtrl(unsigned char Temperature_Set, unsigned char Temperature)
{
	unsigned char TemperatureCtrl_Data;

	if (Temperature_Set >= Temperature)
	{
		if ((Temperature_Set - Temperature) == 0)
			TemperatureCtrl_Data = 1; // 接通加热电源�?
		else if ((Temperature_Set - Temperature) <= 2)
			TemperatureCtrl_Data = 2; // 接通加热电源�?
		else if ((Temperature_Set - Temperature) <= 6)
			TemperatureCtrl_Data = 3;
		else
			TemperatureCtrl_Data = 4;
	}
	else
		TemperatureCtrl_Data = 0;

	return TemperatureCtrl_Data;
}

unsigned char TemperatureTest(unsigned int ADC)
{
	unsigned char xdata a, b;
	unsigned int xdata c;
	unsigned long xdata d;
	unsigned char xdata i;
	extern unsigned char code Calculate_Data[];
	extern unsigned int code Temperature_Convert_Data[];

#define real_resistance ADC
#define real_volt ADC
#define AD real_resistance
#define R_Ohm real_resistance

	d = (unsigned long)10000 * (unsigned long)real_volt/ (unsigned long)(1024 - real_volt); // 计算温度传感器的电阻值�?
	if (d > 47354)
		d = 47354;
	R_Ohm = (unsigned int)d;
	for (i = 0 + 1, a = 0; i < 8; i++)
	{ // 查表计算实际温度值�?
		b = a;
		a |= Calculate_Data[i];
		c = Temperature_Convert_Data[a];
		if (c < R_Ohm)
			a = b;
	}
	if (a >= 10)
		a -= 10;
	else
		a = 0;

	return a; // 返回实际温度值�?
}