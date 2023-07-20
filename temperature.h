#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

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

xdata struct temperature_data{
	volatile unsigned char set;
	volatile unsigned char value;
	volatile unsigned char ctrl;
	volatile unsigned char count;
};

typedef struct temperature_data   s_temperature_data;
typedef struct temperature_data*  p_temperature_data;

void init_temperature(p_temperature_data p_temp);//初始化函数
void set_temperature(p_temperature_data p_temp,unsigned char value_set);//设定温度值
unsigned char get_temperature_data_ctrl(p_temperature_data p_temp,unsigned int ADC_data);//在主函数中，每2.5秒处理一次,返回当前温度值
void close_temperature_ctrl(p_temperature_data p_temp);//关闭发热功能
bit get_temperature_output(p_temperature_data p_temp);//在终端中，每1ms处理一次
unsigned char TemperatureCtrl(unsigned char data Temperature_Set,unsigned char data Temperature);
unsigned char TemperatureTest(unsigned int ADC);//测的当前温度值

#endif
