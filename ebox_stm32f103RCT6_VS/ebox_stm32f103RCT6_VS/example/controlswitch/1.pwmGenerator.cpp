#include "ebox.h"
#include "my_math.h"
#include "accurate_pwm.h"
#include "button.h"
FpsCounter fps;
AccuratePwm pwm1(&PA8);//����һ��PWM�������ʹ�õ���PB8���š�
AccuratePwm pwm2(&PA9);//����һ��PWM�������ʹ�õ���PB8���š�
AccuratePwm pwm3(&PA10);//����һ��PWM�������ʹ�õ���PB8���š�
AccuratePwm pwm4(&PA11);//����һ��PWM�������ʹ�õ���PB8���š�
AccuratePwm pwm5(&PA0);//����һ��PWM�������ʹ�õ���PB8���š�
AccuratePwm pwm6(&PB6);//����һ��PWM�������ʹ�õ���PB8���š�
AccuratePwm pwm7(&PB7);//����һ��PWM�������ʹ�õ���PB8���š�
AccuratePwm pwm8(&PB8);//����һ��PWM�������ʹ�õ���PB8���š�
AccuratePwm pwm9(&PB9);//����һ��PWM�������ʹ�õ���PB8���š�
//�ð����л�ռ�ձȣ��л���ֵ
Button btn1(&PC4, 1);//����һ���������󣬰������ӵ�Pc5��1:������Ϊ����ģʽ
Button btn2(&PC5, 1);//����һ���������󣬰������ӵ�Pc5��1:������Ϊ����ģʽ
Button btn3(&PA6, 1);//����һ���������󣬰������ӵ�Pc5��1:������Ϊ����ģʽ
void setup()
{
	ebox_init();
	btn1.begin();//��ʼ������
	btn2.begin();//��ʼ������
	fps.begin();
	pwm1.begin(300, 400);//��ʼ��PWM���
	pwm1.set_oc_polarity(1);//����PWM������ԡ�
	pwm2.begin(300, 100);//��ʼ��PWM���
	pwm2.set_oc_polarity(1);//����PWM������ԡ�
	pwm3.begin(300, 300);//��ʼ��PWM���
	pwm3.set_oc_polarity(1);//����PWM������ԡ�
	pwm4.begin(300, 500);//��ʼ��PWM���
	pwm4.set_oc_polarity(1);//����PWM������ԡ�
	pwm5.begin(300, 700);//��ʼ��PWM���
	pwm5.set_oc_polarity(1);//����PWM������ԡ�
	pwm6.begin(500, 100);//��ʼ��PWM���
	pwm6.set_oc_polarity(1);//����PWM������ԡ�
	pwm7.begin(500,300);//��ʼ��PWM���
	pwm7.set_oc_polarity(1);//����PWM������ԡ�
	pwm8.begin(500, 500);//��ʼ��PWM���
	pwm8.set_oc_polarity(1);//����PWM������ԡ�
	pwm9.begin(500, 700);//��ʼ��PWM���
	pwm9.set_oc_polarity(1);//����PWM������ԡ�

}
uint16_t y;

int main(void)
{
	int i;
	setup();
	while(1)
	{ 

		btn1.loop();//����ѭ��
		btn2.loop();//����ѭ��
		for (i = 0; i < 15; i++)
		{
			if (btn1.click())//���������¼�
				pwm1.set_duty(600);
			if (btn2.click())//���������¼�
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



