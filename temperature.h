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
		2.5s()//ÿ2.5sִ��һ��
		{	
			set_temperature(&s_example,temperature_set);//temperature_setΪ����Ҫ�趨���¶�ֵ
			ADC_data=function_getADC();
			if(Work_bit==1...)Temperature=get_temperature_data_ctrl(&s_example,ADC_data);�˺�������ֵΪ��ǰ�¶�ֵ
			else 
			{
				close_temperature_ctrl(&s_example);
				Termpeature=TemperatureTest(ADC_data);//����ʾ��ǰ���¶�ֵ 
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

void init_temperature(p_temperature_data p_temp);//��ʼ������
void set_temperature(p_temperature_data p_temp,unsigned char value_set);//�趨�¶�ֵ
unsigned char get_temperature_data_ctrl(p_temperature_data p_temp,unsigned int ADC_data);//���������У�ÿ2.5�봦��һ��,���ص�ǰ�¶�ֵ
void close_temperature_ctrl(p_temperature_data p_temp);//�رշ��ȹ���
bit get_temperature_output(p_temperature_data p_temp);//���ն��У�ÿ1ms����һ��
unsigned char TemperatureCtrl(unsigned char data Temperature_Set,unsigned char data Temperature);
unsigned char TemperatureTest(unsigned int ADC);//��ĵ�ǰ�¶�ֵ

#endif
