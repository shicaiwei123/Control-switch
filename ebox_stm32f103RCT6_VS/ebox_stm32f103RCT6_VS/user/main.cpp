#include "ebox.h"
#include "my_math.h"
#include "accurate_pwm.h"
#include "uartReamp.h"


InCapture remote1(&PA0);//创建输入捕获的对象-遥控器
InCapture remote2(&PA1);
InCapture remote3(&PA2);
InCapture remote4(&PA3);
InCapture remote5(&PA6);
InCapture rx1(&PA7);//创建输入捕获的对象-瑞萨
InCapture rx2(&PB0);
InCapture rx3(&PB1);
InCapture rx4(&PB8);
AccuratePwm pwm1(&PA8);//创建PWM输出对象
AccuratePwm pwm2(&PA9);
AccuratePwm pwm3(&PA10);
AccuratePwm pwm4(&PA11);
uartRemap uart(USART1, &PB6, &PB7);
uint32_t remote[5][2];// 用于保存计数器的值
uint32_t rx[4][2];
FpsCounter fps;
void measure_1()//输入捕获中断事件
{
	if (remote1.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		remote[0][0] = remote1.get_capture();
		remote1.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		remote[0][1] = remote1.get_capture();
		remote1.set_polarity_falling();//切换检测下降沿
	}
}
void measure_2()//输入捕获中断事件
{
	if (remote2.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		remote[1][0] = remote2.get_capture();
		remote2.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		remote[1][1] = remote2.get_capture();
		remote2.set_polarity_falling();//切换检测下降沿
	}
}
void measure_3()//输入捕获中断事件
{
	if (remote3.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		remote[2][0] = remote3.get_capture();
		remote3.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		remote[2][1] = remote3.get_capture();
		remote3.set_polarity_falling();//切换检测下降沿
	}
}
void measure_4()//输入捕获中断事件
{
	if (remote4.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		remote[3][0] = remote4.get_capture();
		remote4.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		remote[3][1] = remote4.get_capture();
		remote4.set_polarity_falling();//切换检测下降沿
	}
}

void measure_5()//输入捕获中断事件
{
	if (remote5.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		remote[4][0] = remote5.get_capture();
		remote5.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		remote[4][1] = remote5.get_capture();
		remote5.set_polarity_falling();//切换检测下降沿
	}
}
void measure_6()//输入捕获中断事件
{
	if (rx1.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		rx[0][0] = rx1.get_capture();
		rx1.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		rx[0][1] = rx1.get_capture();
		rx1.set_polarity_falling();//切换检测下降沿
	}
}
void measure_7()//输入捕获中断事件
{
	if (rx2.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		rx[1][0] = rx2.get_capture();
		rx2.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		rx[1][1] = rx2.get_capture();
		rx2.set_polarity_falling();//切换检测下降沿
	}
}
void measure_8()//输入捕获中断事件
{
	if (rx3.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		rx[2][0] = rx3.get_capture();
		rx3.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		rx[2][1] = rx3.get_capture();
		rx3.set_polarity_falling();//切换检测下降沿
	}
}


void measure_9()//输入捕获中断事件
{
	if (rx4.polarity == TIM_ICPOLARITY_FALLING)//检测到下降沿，测量高电平时间完成
	{
		rx[3][0] = rx4.get_capture();
		rx4.set_polarity_rising();//切换检测上升沿
	}
	else//检测到上升沿，测量低电平时间完成
	{
		rx[3][1] = rx4.get_capture();
		rx4.set_polarity_falling();//切换检测下降沿
	}
}


uint16_t p;
void setup()
{
	fps.begin();
	ebox_init();
	uart.remap();
	uart.begin(115200);
	//uart1.begin(115200);
	//uart1.printf("this is a serial example\r\n");
	PD2.mode(OUTPUT_PP);
	fps.begin();
	p = 1;
	remote1.begin(p);//初始化输入捕获参数，p分频
	remote1.attach(measure_1);//绑定捕获中断事件函数
	remote2.begin(p);//初始化输入捕获参数，p分频
	remote2.attach(measure_2);//绑定捕获中断事件函数
	remote3.begin(p);//初始化输入捕获参数，p分频
	remote3.attach(measure_3);//绑定捕获中断事件函数
	remote4.begin(p);//初始化输入捕获参数，p分频
	remote4.attach(measure_4);//绑定捕获中断事件函数
	remote5.begin(p);//初始化输入捕获参数，p分频
	remote5.attach(measure_5);//绑定捕获中断事件函数
	rx1.begin(p);//初始化输入捕获参数，p分频
	rx1.attach(measure_6);//绑定捕获中断事件函数
	rx2.begin(p);//初始化输入捕获参数，p分频
	rx2.attach(measure_7);//绑定捕获中断事件函数
	rx3.begin(p);//初始化输入捕获参数，p分频
	rx3.attach(measure_8);//绑定捕获中断事件函数
	rx4.begin(p);//初始化输入捕获参数，p分频
	rx4.attach(measure_9);//绑定捕获中断事件函数
	pwm1.begin(300, 100);
	pwm1.set_oc_polarity(1);
	pwm2.begin(300, 300);
	pwm2.set_oc_polarity(1);
	pwm3.begin(300, 500);
	pwm3.set_oc_polarity(1);
	pwm4.begin(300, 700);
	pwm4.set_oc_polarity(1);
}
int main(void)
{
	uint16_t pulse[9];
	uint16_t frq[9];
	setup();
	while (1)
	{

		if (remote[0][0] && remote[0][1])
		{
			uart.printf("pluse_1 = %d\r\n", remote[0][0] * 1000 / (remote[0][0] + remote[0][1]));
			pulse[0] = remote[0][0] * 1000 / (remote[0][0] + remote[0][1]);
			frq[0] = 72000000 / p / (remote[0][0] + remote[0][1]);
			remote[0][0] = 0;
			remote[0][1] = 0;
		}
		if (pulse[0] > 500)
			{

				pulse[1] = remote[1][0] * 1000 / (remote[1][0] + remote[1][1]);
				frq[1] = 72000000 / p / (remote[1][0] + remote[1][1]);
				remote[1][0] = 0;
				remote[1][1] = 0;

				pulse[2] = remote[2][0] * 1000 / (remote[2][0] + remote[2][1]);
				frq[2] = 72000000 / p / (remote[2][0] + remote[2][1]);
				remote[2][0] = 0;
				remote[2][1] = 0;

				pulse[3] = remote[3][0] * 1000 / (remote[3][0] + remote[3][1]);
				frq[3] = 72000000 / p / (remote[3][0] + remote[3][1]);
				remote[3][0] = 0;
				remote[3][1] = 0;

				pulse[4] = remote[4][0] * 1000 / (remote[4][0] + remote[4][1]);
				frq[4] = 72000000 / p / (remote[4][0] + remote[4][1]);
				remote[4][0] = 0;
				remote[4][1] = 0;


				pwm1.set_frq(frq[1]);
				pwm1.set_duty(pulse[1]);
				pwm2.set_frq(frq[1]);
				pwm2.set_duty(pulse[2]);
				pwm3.set_frq(frq[1]);
				pwm3.set_duty(pulse[3]);
				pwm4.set_frq(frq[1]);
				pwm4.set_duty(pulse[4]);
				uart.printf("remote2Pulse=%d\r\n", pulse[1]);
				uart.printf("remote2Frq=%d\r\n", frq[1]);
				uart.printf("remote3Pulse=%d\r\n", pulse[2]);
				uart.printf("remote3Frq=%d\r\n", frq[2]);
				uart.printf("remote4Pulse=%d\r\n", pulse[3]);
				uart.printf("remote4Frq=%d\r\n", frq[3]);
				uart.printf("remote5Pulse=%d\r\n", pulse[4]);
				uart.printf("remote5Frq=%d\r\n", frq[4]);

			}
			else
			{
				pulse[5] = rx[0][0] * 1000 / (rx[0][0] + rx[0][1]);
				frq[5] = 72000000 / p / (rx[0][0] + rx[0][1]);
				rx[0][0] = 0;
				rx[0][1] = 0;

				pulse[6] = rx[1][0] * 1000 / (rx[1][0] + rx[1][1]);
				frq[6] = 72000000 / p / (rx[1][0] + rx[1][1]);
				rx[1][0] = 0;
				rx[1][1] = 0;


				pulse[7] = rx[2][0] * 1000 / (rx[2][0] + rx[2][1]);
				frq[7] = 72000000 / p / (rx[2][0] + rx[2][1]);
				rx[2][0] = 0;
				rx[2][1] = 0;

				pulse[8] = rx[3][0] * 1000 / (rx[3][0] + rx[3][1]);
				frq[8] = 72000000 / p / (rx[3][0] + rx[3][1]);
				rx[3][0] = 0;
				rx[3][1] = 0;

				pwm1.set_frq(frq[5]);
				pwm1.set_duty(pulse[5]);
				pwm2.set_frq(frq[5]);
				pwm2.set_duty(pulse[6]);
				pwm3.set_frq(frq[5]);
				pwm3.set_duty(pulse[7]);
				pwm4.set_frq(frq[5]);
				pwm4.set_duty(pulse[8]);
				

				uart.printf("rx1Pulse=%d\r\n", pulse[5]);
			//	uart.printf("rx1Frq=%d\r\n", frq[5]);
				uart.printf("rx2Pulse=%d\r\n", pulse[6]);
			//	uart.printf("rx2Frq=%d\r\n", frq[6]);
				uart.printf("rx3Pulse=%d\r\n", pulse[7]);
			//	uart.printf("rx3Frq=%d\r\n", frq[7]);
				uart.printf("rx4Pulse=%d\r\n", pulse[8]);
			//	uart.printf("rx4Frq=%d\r\n", frq[8]);

			}
			PD2.toggle();
		//	delay_us(8000);
			uart.printf("%f\r\n", fps.getFps());
    }

}


