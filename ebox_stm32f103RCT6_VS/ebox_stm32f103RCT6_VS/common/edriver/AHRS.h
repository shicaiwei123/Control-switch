#ifndef __AHRS_H
#define __AHRS_H

#include <math.h>

class MahonyAHRS9
{
protected:
	float q0, q1, q2, q3;	// quaternion of sensor frame relativ
	float exInt, eyInt, ezInt;
	float Ki, Kp;// ��������֧��������accelerometer/magnetometer 
				 // ��������ִ�����������ǵ��ν�gyroscopeases 
	float halfT;
	float sampleFreq;

	//������ƽ����
	float invSqrt(float x);


public:
	MahonyAHRS9(float sampleFreq = 100, float kp = 2, float ki = 0.005);

	virtual void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);

	void setSampleRate(float sampleRate);

	virtual void getAngle(float* Pitch, float* Roll, float* Yaw);

	virtual void getQuaternion(float* q0, float* q1, float* q2, float* q3);
};



#endif

