#ifndef __ACCURATE_PWM_H
#define __ACCURATE_PWM_H

#include "ebox.h"
#include "my_math.h"

class AccuratePwm :public Pwm
{
	float duty;
	uint16_t counter;
public:
	AccuratePwm(Gpio *pwm_pin);

	void begin(uint32_t frq, uint16_t duty);

	//��1000Ϊ��ռ�ձ�
	//�Ը������ͱ�֤��ߵľ���
	void set_duty(float duty);

	//ֱ�ӶԼĴ������в���
	//�����ڸ���Ԥ��Ƶϵ��ǰ�ݴ��������ֵ
	//�����ebox_pwm�ڸı�Ƶ��ʱ��λ�仯������
	void set_frq(uint32_t frq);
};

#endif
