# 温度控制

## a example of use

```c

handle_heat_type handle_example;//定义一个发热手柄对象
Init_handle_heat(handle_heat_type* &handle_example);//初始化一个发热手柄
Set_temperature_handle_heat(handle_heat_type* &handle_example,50);//设定手柄温度为50℃
temperature = Get_ctrlhdata_handle_heat(handle_heat_type* &handle_example,ADC_data)//此函数每2.5s执行一次，ADC_data为10位的，此函数返回当前的手柄温度值
Close_handle_heat(handle_heat_type* &handle_example);//关闭此手柄的发热功能
P00 = Set_output_handle_heat(handle_heat_type* &handle_example)//此函数每1ms处理一次，控制MOS管的发热引脚
temperature = TemperatureTest(ADC_data);//此函数也可以测得温度

```
