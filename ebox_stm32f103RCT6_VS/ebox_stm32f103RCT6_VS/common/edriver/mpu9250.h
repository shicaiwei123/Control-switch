#ifndef __MPU9250_H
#define __MPU9250_H

#include "ebox.h"
#include <math.h>
#include "mpu6500.h"
#include "AK8963.h"
#include "AHRS.h"


class MPU9250:public MPU6500,public AK8963
{
protected:
	

public:
	MPU9250(I2c* i2c, MPU6500_Model_Typedef model = MPU6500_Model_6500,
		uint8_t address6500 = MPU6500_ADDRESS, uint8_t address8963 = AK8963_ADDRESS);

	void begin(uint32_t speed = 400000, uint16_t sampleRate = 100,
		MPU6500_Gyro_Full_Scale_Typedef gyroFsr = MPU6500_Gyro_Full_Scale_2000dps,
		MPU6500_Accel_Full_Scale_Typedef accelFsr = MPU6500_Accel_Full_Scale_8g,
		MPU6500_DLPF_Bandwidth_Typedef bwDLPF = MPU6500_DLPF_Bandwidth_41Hz,
		MPU6500_A_DLPF_Bandwidth_Typedef bwADLPF = MPU6500_A_DLPF_Bandwidth_44_8Hz);


};





class MPU9250AHRS :public MPU9250, private MahonyAHRS9
{
protected:
	void update()
	{
		float g[3], a[3], m[3];
		getGyro(g, g + 1, g + 2);
		getAccel(a, a + 1, a + 2);
		getMag(m, m + 1, m + 2);

		//MahonyAHRS9::update(
		//	g[0], g[1], g[2],
		//	a[0], a[1], a[2],
		//	m[0], m[1], m[2]);

		//����9250�ڲ��Ų����з���任
		MahonyAHRS9::update(
			-g[1], g[0], g[2],
			-a[1], a[0], a[2],
			m[0], -m[1], -m[2]);
	}
public:
	MPU9250AHRS(I2c* i2c, MPU6500_Model_Typedef model = MPU6500_Model_6500) :
		MPU9250(i2c, model),
		MahonyAHRS9(100, 2, 0.005)
	{

	}

	void begin(uint32_t speed = 400000, uint16_t sampleRate = 100,
		MPU6500_Gyro_Full_Scale_Typedef gyroFsr = MPU6500_Gyro_Full_Scale_2000dps,
		MPU6500_Accel_Full_Scale_Typedef accelFsr = MPU6500_Accel_Full_Scale_8g,
		MPU6500_DLPF_Bandwidth_Typedef bwDLPF = MPU6500_DLPF_Bandwidth_41Hz,
		MPU6500_A_DLPF_Bandwidth_Typedef bwADLPF = MPU6500_A_DLPF_Bandwidth_44_8Hz)
	{
		MPU9250::begin(speed, 1000, gyroFsr, accelFsr, bwDLPF, bwADLPF);
		MahonyAHRS9::setSampleRate(sampleRate);
	}


	virtual void getAngle(float* pitch, float* roll, float* yaw)
	{
		update();
		MahonyAHRS9::getAngle(pitch, roll, yaw);
	}

	virtual void getQuaternion(float* q0, float* q1, float* q2, float* q3)
	{
		update();
		MahonyAHRS9::getQuaternion(q0, q1, q2, q3);
	}
};



#endif
