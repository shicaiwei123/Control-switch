#include "ebox.h"
#include "my_math.h"
#include "accurate_pwm.h"
#include "button.h"
FpsCounter fps;
AccuratePwm pwm1(&PA8);//创建一个PWM输出对象。使用的是PB8引脚。
AccuratePwm pwm2(&PA9);//创建一个PWM输出对象。使用的是PB8引脚。
AccuratePwm pwm3(&PA10);//创建一个PWM输出对象。使用的是PB8引脚。
AccuratePwm pwm4(&PA11);//创建一个PWM输出对象。使用的是PB8引脚。
AccuratePwm pwm5(&PA0);//创建一个PWM输出对象。使用的是PB8引脚。
AccuratePwm pwm6(&PB6);//创建一个PWM输出对象。使用的是PB8引脚。
AccuratePwm pwm7(&PB7);//创建一个PWM输出对象。使用的是PB8引脚。
AccuratePwm pwm8(&PB8);//创建一个PWM输出对象。使用的是PB8引脚。
AccuratePwm pwm9(&PB9);//创建一个PWM输出对象。使用的是PB8引脚。
//用按键切换占空比，切换阈值
Button btn1(&PC4, 1);//创建一个按键对象，按键链接到Pc5，1:代表按键为上拉模式
Button btn2(&PC5, 1);//创建一个按键对象，按键链接到Pc5，1:代表按键为上拉模式
Button btn3(&PA6, 1);//创建一个按键对象，按键链接到Pc5，1:代表按键为上拉模式
void setup()
{
	ebox_init();
	btn1.begin();//初始化按键
	btn2.begin();//初始化按键
	fps.begin();
	pwm1.begin(300, 400);//初始化PWM输出
	pwm1.set_oc_polarity(1);//设置PWM输出极性。
	pwm2.begin(300, 100);//初始化PWM输出
	pwm2.set_oc_polarity(1);//设置PWM输出极性。
	pwm3.begin(300, 300);//初始化PWM输出
	pwm3.set_oc_polarity(1);//设置PWM输出极性。
	pwm4.begin(300, 500);//初始化PWM输出
	pwm4.set_oc_polarity(1);//设置PWM输出极性。
	pwm5.begin(300, 700);//初始化PWM输出
	pwm5.set_oc_polarity(1);//设置PWM输出极性。
	pwm6.begin(500, 100);//初始化PWM输出
	pwm6.set_oc_polarity(1);//设置PWM输出极性。
	pwm7.begin(500,300);//初始化PWM输出
	pwm7.set_oc_polarity(1);//设置PWM输出极性。
	pwm8.begin(500, 500);//初始化PWM输出
	pwm8.set_oc_polarity(1);//设置PWM输出极性。
	pwm9.begin(500, 700);//初始化PWM输出
	pwm9.set_oc_polarity(1);//设置PWM输出极性。

}
uint16_t y;

int main(void)
{
	int i;
	setup();
	while(1)
	{ 

		btn1.loop();//按键循环
		btn2.loop();//按键循环
		for (i = 0; i < 15; i++)
		{
			if (btn1.click())//按键单击事件
				pwm1.set_duty(600);
			if (btn2.click())//按键单击事件
				pwm1.set_duty(400);

			pwm2.set_duty(100 + 10 * i);
			pwm3.set_duty(300 + 10 * i);
			pwm4.set_duty(500 + 10 * i);
			pwm5.set_duty(700 + 10 * i);
			pwm6.set_duty(100 + 10 * i);
			pwm7.set_duty(300 + 10 * i);
			pwm8.set_duty(500 + 10 * i);
			pwm9.set_duty(700 + 10 * i);
			delay_us(20000);
		}
	printf("%f\r\n", fps.getFps());
	}
}



