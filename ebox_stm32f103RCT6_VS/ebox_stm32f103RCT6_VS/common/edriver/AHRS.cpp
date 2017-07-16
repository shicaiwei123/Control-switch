#include "AHRS.h"

float MahonyAHRS9::invSqrt(float x)
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

MahonyAHRS9::MahonyAHRS9(float sampleFreq /*= 100*/, float kp /*= 2*/, float ki /*= 0.005*/) :
	Kp(kp), Ki(ki),
	q0(1), q1(0), q2(0), q3(0),
	exInt(0), eyInt(0), ezInt(0)
{
	setSampleRate(sampleFreq);
}

void MahonyAHRS9::update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
{
	float norm;
	float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
	float hx, hy, hz, bx, bz;
	float vx, vy, vz, wx, wy, wz;
	float ex, ey, ez;
	float qa, qb, qc;
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{

		// Normalise accelerometer measurement
		//�������ļ��ٶȲ���ֵ
		norm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= norm;
		ay *= norm;
		az *= norm;

		if (!((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)))
		{
			// Normalise magnetometer measurement
			//�������Ĵ����Ʋ���ֵ
			norm = invSqrt(mx * mx + my * my + mz * mz);
			mx *= norm;
			my *= norm;
			mz *= norm;
		}

		//Ԥ�Ƚ�����Ԫ���������㣬�Ա����ظ����������Ч�����⡣
		// Auxiliary variables to avoid repeated arithmetic
		q0q0 = q0 * q0;
		q0q1 = q0 * q1;
		q0q2 = q0 * q2;
		q0q3 = q0 * q3;
		q1q1 = q1 * q1;
		q1q2 = q1 * q2;
		q1q3 = q1 * q3;
		q2q2 = q2 * q2;
		q2q3 = q2 * q3;
		q3q3 = q3 * q3;

		hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
		hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
		hz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));
		bx = sqrt(hx * hx + hy * hy);
		bz = hz;

		vx = q1q3 - q0q2;
		vy = q0q1 + q2q3;
		vz = q0q0 - 0.5f + q3q3;
		wx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
		wy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
		wz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);

		//ʹ�ò�������������͵ش���
		// Error is sum of cross product between estimated direction and measured direction of field vectors
		ex = (ay * vz - az * vy) + (my * wz - mz * wy);
		ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
		ez = (ax * vy - ay * vx) + (mx * wy - my * wx);

		//�������л���
		exInt += Ki * ex * (1.0f / sampleFreq); // integral error scaled by Ki
		eyInt += Ki * ey * (1.0f / sampleFreq);
		ezInt += Ki * ez * (1.0f / sampleFreq);

		//����ʵ�ļ��ٶȲ���ֵ��һ�����������������ǣ�0������ȫ���������ǣ�1������ȫ���μ��ٶȣ�����1��
		gx = gx + Kp*ex + exInt;
		gy = gy + Kp*ey + eyInt;
		gz = gz + Kp*ez + ezInt;

		qa = q0;
		qb = q1;
		qc = q2;
		q0 += (-qb * gx - qc * gy - q3 * gz)*halfT;
		q1 += (qa * gx + qc * gz - q3 * gy)*halfT;
		q2 += (qa * gy - qb * gz + q3 * gx)*halfT;
		q3 += (qa * gz + qb * gy - qc * gx)*halfT;

		// Normalise quaternion

		norm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
		q0 *= norm;
		q1 *= norm;
		q2 *= norm;
		q3 *= norm;

	}
}

void MahonyAHRS9::setSampleRate(float sampleRate)
{
	this->sampleFreq = sampleRate;
	halfT = 1 / (2 * sampleFreq);
}

void MahonyAHRS9::getAngle(float* Pitch, float* Roll, float* Yaw)
{
	//��Ԫ��ת����ŷ����
	*Pitch = asin(2 * q0*q2 - 2 * q1*q3) / 3.14 * 180;
	*Roll = atan2(2 * q0*q1 + 2 * q2*q3, 1 - 2 * q1*q1 - 2 * q2*q2) / 3.14 * 180;
	*Yaw = atan2(2 * q0*q3 + 2 * q1*q2, 1 - 2 * q2*q2 - 2 * q3*q3) / 3.14 * 180;
}

void MahonyAHRS9::getQuaternion(float* q0, float* q1, float* q2, float* q3)
{
	*q0 = this->q0;
	*q1 = this->q1;
	*q2 = this->q2;
	*q3 = this->q3;
}
