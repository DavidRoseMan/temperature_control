#ifndef _TEMPERATURECONTROL_H
#define _TEMPERATURECONTROL_H

/*
@exmaple:
s_temperature_data s_example;
void main()
{
	init_temperature(&s_example);
	while(1)
	{
		2.5s()//每2.5s执行一次
		{	
			set_temperature(&s_example,temperature_set);//temperature_set为所想要设定的温度值
			ADC_data=function_getADC();
			if(Work_bit==1...)Temperature=get_temperature_data_ctrl(&s_example,ADC_data);此函数返回值为当前温度值
			else 
			{
				close_temperature_ctrl(&s_example);
				Termpeature=TemperatureTest(ADC_data);//可显示当前的温度值 
			}
		}
	}
}

void interrupt()//1ms
{
	IO=get_temperature_output(&s_example);
}
*/

typedef xdata struct temperature_data{
	volatile unsigned char set;
	volatile unsigned char value;
	volatile unsigned char ctrl;
	volatile unsigned char count;
}handle_heat_type;


void Init_handle_heat(handle_heat_type* p_temp);//初始化一个发热手柄
void Set_temperature_handle_heat(handle_heat_type* p_temp,unsigned char value_set);//对手柄设定温度值
unsigned char Get_ctrldata_handle_heat(handle_heat_type* p_temp,unsigned int ADC_data);//每2.5秒处理一次手柄数据,返回当前手柄挡墙温度值
void Close_handle_heat(handle_heat_type* p_temp);//关闭手柄发热功能
bit Set_output_handle_heat(handle_heat_type* p_temp);//每1ms处理一次，返回值赋给发热mos管控制脚。
unsigned char TemperatureCtrl(unsigned char Temperature_Set,unsigned char Temperature);
unsigned char TemperatureTest(unsigned int ADC);//测温

#endif
