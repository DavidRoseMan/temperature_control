#include"temperature.h"

unsigned int code Temperature_Convert_Data[112]=
{
	47354,45165,43082,41083,39162,37320,35653,33897,32323,30822,//-10�桫-1��
	29394,28041,26760,25548,24403,23319,22292,21317,20390,19505,//  0�桫 9��
	18659,17863,17107,16388,15703,15052,14432,13641,13278,12741,// 10�桫19��
	12229,11741,11257,10830,10406,10000, 9612, 9242, 8888, 8549,// 20�桫29��
	 8225, 7915, 7619, 7335, 7063, 6802, 6553, 6314, 6085, 5865,// 30�桫39��
	 5654, 5452, 5258, 5072, 4893, 4721, 4556, 4398, 4245, 4099,// 40�桫49��
	 3958, 3822, 3692, 3657, 3446, 3330, 3218, 3110, 3007, 2907,// 50�桫59��
	 2810, 2718, 2629, 2543, 2460, 2380, 2303, 2229, 2158, 2089,// 60�桫69��
	 2024, 1960, 1899, 1840, 1784, 1730, 1678, 1627, 1580, 1534,// 70�桫79��
	 1491, 1450, 1409, 1371, 1335, 1299, 1266, 1229, 1195, 1160,// 80�桫89��
	 1124, 1093, 1063, 1034, 1006,  979,  953,  928,  903,  880,// 90�桫99��
	  857,    0,                                                //100��
};

void init_temperature(p_temperature_data p_temp)//��ʼ������
{
	p_temp->set = 0;
	p_temp->value = 100;
	p_temp->ctrl = 0;
	p_temp->count = 0;
}

void set_temperature(p_temperature_data p_temp,unsigned char value_set)//�趨�¶�ֵ
{
	p_temp->set = value_set;
}

unsigned char get_temperature_data_ctrl(p_temperature_data p_temp,unsigned int ADC_data)//���������У�ÿ2.5�봦��һ��,���ص�ǰ�¶�ֵ
{
	p_temp->value = TemperatureTest(ADC_data);   
	if(ADC_data<886)p_temp->ctrl = TemperatureCtrl(p_temp->set,p_temp->value);//��������ֵ����65K��������·�𻵣����������㽫�����������
	else            p_temp->ctrl =0;//�����������
	return p_temp->value;
}

void close_temperature_ctrl(p_temperature_data p_temp)//�رշ��ȹ���,����ֵΪ��ǰ�¶�ֵ
{
	p_temp->ctrl =  0;
	p_temp->count = 0;
}


bit get_temperature_output(p_temperature_data p_temp)//���ն��У�ÿ1ms����һ��
{
	unsigned char a;
	bit HotCtrl_IO=0;

	p_temp->count++;if(p_temp->count>=4+0)p_temp->count=0;
	a=p_temp->ctrl;if(a){if(a<3)a=3;}
	if(p_temp->count<a)HotCtrl_IO=1;
	else               HotCtrl_IO=0;
	
	return HotCtrl_IO;
}

unsigned char TemperatureCtrl(unsigned char data Temperature_Set,unsigned char data Temperature)
{
    unsigned char TemperatureCtrl_Data;
    
    if(Temperature_Set>=Temperature)
    {
             if((Temperature_Set-Temperature)==0)TemperatureCtrl_Data=1;//��ͨ���ȵ�Դ��
        else if((Temperature_Set-Temperature)<=2)TemperatureCtrl_Data=2;//��ͨ���ȵ�Դ��
        else if((Temperature_Set-Temperature)<=6)TemperatureCtrl_Data=3;
        else                                     TemperatureCtrl_Data=4;
    }
    else                                         TemperatureCtrl_Data=0;
    
    return TemperatureCtrl_Data;
}

unsigned char TemperatureTest(unsigned int ADC)
{
    unsigned char data a,b;
    unsigned int  data c;
    unsigned long data d;
    unsigned char data i;
    #define real_resistance  ADC
    #define real_volt        ADC
    #define AD               real_resistance
    #define R_Ohm            real_resistance
    unsigned char code Calculate_Data[8]={
										0x80,
										0x40,
										0x20,
										0x10,
										0x08,
										0x04,
										0x02,
										0x01,
                                 };
	extern unsigned int code Temperature_Convert_Data[];
    d = (unsigned long)10000*(unsigned long)ADC/(unsigned long)(1024-ADC);//�����¶ȴ������ĵ���ֵ��
    if(d>47354)d=47354;
    R_Ohm=(unsigned int)d;
    for(i=0+1,a=0;i<8;i++)
    {//������ʵ���¶�ֵ��
        b=a;
        a|=Calculate_Data[i];
        c=Temperature_Convert_Data[a];
        if(c<R_Ohm)a=b;
    }
	if(a>=10)a -= 10;
	else a = 0;
    
    return a;//����ʵ���¶�ֵ��
}