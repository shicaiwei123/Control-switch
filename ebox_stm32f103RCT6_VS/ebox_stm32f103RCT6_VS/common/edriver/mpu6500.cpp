#include "mpu6500.h"
#include "my_math.h"

const uint16_t MPU6500::gyroFsrList[] = { 250,500,1000,2000 };
const uint8_t MPU6500::accelFsrList[] = { 2,4,8,16 };
const uint8_t MPU6500::mpuIDList[] = { MPU6500_ID,MPU6555_ID };

MPU6500::MPU6500(I2c* i2c, MPU6500_Model_Typedef model, uint8_t address /*= address*/) :
	I2cIC(i2c),
	address(address)
{
	mpuID = mpuIDList[model]; 

	for (int i = 0; i < 3; i++)
	{
		gyroBiasSub[i] = 0;
		accelBiasSub[i] = 0;
	}
}

void MPU6500::begin(uint32_t speed /*= 400000*/, uint16_t sampleRate /*= 1000*/,
	MPU6500_Gyro_Full_Scale_Typedef gyroFsrReg/* = MPU6500_Gyro_Full_Scale_2000dps*/,
	MPU6500_Accel_Full_Scale_Typedef accelFsrReg/* = MPU6500_Accel_Full_Scale_8g*/,
	MPU6500_DLPF_Bandwidth_Typedef bwDLPF /*= MPU6500_DLPF_Bandwidth_41Hz*/,
	MPU6500_A_DLPF_Bandwidth_Typedef bwADLPF /*= MPU6500_A_DLPF_Bandwidth_44_8Hz*/)
{
	I2cIC::begin(speed);

	//��ʼ��
	writeByte(address, MPU6500_PWR_MGMT1 , 0X80);//��λMPU6500
	delay_ms(100);  //��ʱ100ms
	writeByte(address, MPU6500_PWR_MGMT1 , 0X00);//����MPU6500

	//���������Ǻͼ��ٶȼ�
	setGyroFsr(gyroFsrReg);
	setAccelFsr(accelFsrReg);

	writeByte(address, MPU6500_INT_EN , 0X00);   //�ر������ж�
	writeByte(address, MPU6500_USER_CTRL , 0X00);//I2C��ģʽ�ر�
	writeByte(address, MPU6500_FIFO_EN , 0X00);	//�ر�FIFO
	writeByte(address, MPU6500_INTBP_CFG , 0X82);//INT���ŵ͵�ƽ��Ч������bypassģʽ������ֱ�Ӷ�ȡ������
	u8 id = readByte(address, MPU6500_DEVICE_ID );  //��ȡMPU6500��ID
	if (id == mpuID) //����ID��ȷ
	{
		writeByte(address, MPU6500_PWR_MGMT1 , 0X01);  	//����CLKSEL,PLL X��Ϊ�ο�
		writeByte(address, MPU6500_PWR_MGMT2 , 0X00);  	//���ٶ��������Ƕ�����
		setSampleRate(sampleRate);						       	//���ò�����
	}
}

void MPU6500::setGyroFsr(MPU6500_Gyro_Full_Scale_Typedef fsr)
{
	this->gyroFsr = this->gyroFsrList[fsr];
	uint8_t c = readByte(address, MPU6500_GYRO_CFG);
	replaceBits<uint8_t>(c, fsr, 4, 3);//MPU6500_GYRO_CFG[4:3]��GYRO_FS_SEL
	writeByte(address, MPU6500_GYRO_CFG, c);//���������������̷�Χ
}

void MPU6500::setAccelFsr(MPU6500_Accel_Full_Scale_Typedef fsr)
{
	this->accelFsr = this->accelFsrList[fsr];
	uint8_t c = readByte(address, MPU6500_ACCEL_CFG);
	replaceBits<uint8_t>(c, fsr, 4, 3);//MPU6500_ACCEL_CFG[4:3]��ACCEL_FS_SEL
	writeByte(address, MPU6500_ACCEL_CFG, c);//���ü��ٶȴ����������̷�Χ
}

void MPU6500::setBothLPF(MPU6500_DLPF_Bandwidth_Typedef bwDLPF, MPU6500_A_DLPF_Bandwidth_Typedef bwADLPF)
{
	setDLPF(bwDLPF);
	setADLPF(bwADLPF);
}


void MPU6500::setDLPF(MPU6500_DLPF_Bandwidth_Typedef bwDLPF)
{
	uint8_t c = readByte(address, MPU6500_CFG);
	replaceBits<uint8_t>(c, bwDLPF, 2, 0);//MPU6500_CFG[2:0]��DLPF_CFG
	writeByte(address, MPU6500_CFG, c);//�������ֵ�ͨ�˲���

	c = readByte(address, MPU6500_GYRO_CFG);
	replaceBits<uint8_t>(c, 0, 1, 0);//MPU6500_GYRO_CFG[1:0]��Fchoice_b
	writeByte(address, MPU6500_GYRO_CFG, c);//����GYRO�����˲���
}

void MPU6500::setADLPF(MPU6500_A_DLPF_Bandwidth_Typedef bwADLPF)
{
	uint8_t c = readByte(address, MPU6500_ACCEL_CFG);
	replaceBits<uint8_t>(c, 0, 3, 3);//MPU6500_ACCEL_CFG[3]��accel_fchoice_b
	replaceBits<uint8_t>(c, bwADLPF, 2, 0);//MPU6500_ACCEL_CFG[3]��A_DLPFCFG
	writeByte(address, MPU6500_ACCEL_CFG, c);//����ACCEL�����˲���
}

void MPU6500::setSampleRate(u16 sampleRate)
{
	u8 data;
	limit<u16>(sampleRate, 4, 1000);
	this->sampleRate = sampleRate;
	data = 1000 / sampleRate - 1;
	writeByte(address, MPU6500_SAMPLE_RATE, data); //This is the update rate of sensor register.
}

void MPU6500::setBypass()
{
	uint8_t c = readByte(address, MPU6500_INTBP_CFG);
	replaceBits<uint8_t>(c, 1, 1, 1);//MPU6500_INTBP_CFG[1]��BYPASS_EN
	writeByte(address, MPU6500_INTBP_CFG, 0X82);//INT���ŵ͵�ƽ��Ч������bypassģʽ������ֱ�Ӷ�ȡ������
}

float MPU6500::getTemp(void)
{
	u8 buf[2];
	short raw;
	float temp;
	readBytes(address, MPU6500_TEMP_OUTH , 2, buf);
	raw = ((u16)buf[0] << 8) | buf[1];
	temp = 21 + ((double)raw) / 333.87;
	return temp;
}

void MPU6500::getGyro(short *gx, short *gy, short *gz)
{
	u8 buf[6];
	readBytes(address, MPU6500_GYRO_XOUTH , 6, buf);
	*gx = ((u16)buf[0] << 8) | buf[1];
	*gy = ((u16)buf[2] << 8) | buf[3];
	*gz = ((u16)buf[4] << 8) | buf[5];
}

void MPU6500::getGyro(float *gx, float *gy, float *gz)
{
	short x, y, z;
	getGyro(&x, &y, &z);
	//16.4 = 2^16/4000 lsb ��/s     1/16.4=0.061     0.0174 = 3.141593/180
	//���������ݴ�ADCת��Ϊ����ÿ��(������Ҫ��ȥƫ��ֵ)
	*gx = (double)x * gyroFsr * 5.326322767469618e-7 - gyroBiasSub[0];  //2 / 65536 * 0.0174
	*gy = (double)y * gyroFsr * 5.326322767469618e-7 - gyroBiasSub[1];
	*gz = (double)z * gyroFsr * 5.326322767469618e-7 - gyroBiasSub[2];	//����ֵ��ȥ��׼ֵ���Ե�λ�����������ǽ��ٶ�
}

void MPU6500::getAccel(short *ax, short *ay, short *az)
{
	u8 buf[6];
	readBytes(address, MPU6500_ACCEL_XOUTH, 6, buf);
	*ax = ((u16)buf[0] << 8) | buf[1];
	*ay = ((u16)buf[2] << 8) | buf[3];
	*az = ((u16)buf[4] << 8) | buf[5];
}

void MPU6500::getAccel(float *ax, float *ay, float *az)
{
	short x, y, z;
	getAccel(&x, &y, &z);
	//+-8g,2^16/16=4096lsb/g--0.244mg/lsb
	//�˴�0.0098�ǣ�(9.8m/s^2)/1000,����mg��m/s^2
	*ax = (double)x * accelFsr * 0.000030517578125 - accelBiasSub[0];  //2 / 65536
	*ay = (double)y * accelFsr * 0.000030517578125 - accelBiasSub[1];
	*az = (double)z * accelFsr * 0.000030517578125 - accelBiasSub[2];
}

u16 MPU6500::getSampleRate()
{
	return sampleRate;
}

void MPU6500::caliGyro()
{
	getGyroBias(gyroBiasSub, gyroBiasSub + 1, gyroBiasSub + 2);
}

void MPU6500::setGyroBias(float bx, float by, float bz)
{
	gyroBiasSub[0] = bx;
	gyroBiasSub[1] = by;
	gyroBiasSub[2] = bz;
}

void MPU6500::getGyroBias(float* bx, float* by, float* bz, int sampleNum /*= 100*/)
{
	double g[3] = { 0 };
	//�ݴ�֮ǰ��ƫ��
	float temp[3];
	for (int i = 0; i < 3; i++)
	{
		temp[i] = gyroBiasSub[i];
	}
	setGyroBias(0, 0, 0);

	//����gSample��ȡƽ��
	float gSample[3];
	for (int i = 0; i < sampleNum; i++)
	{
		getGyro(gSample, gSample + 1, gSample + 2);
		for (int j = 0; j < 3; j++)
		{
			g[j] += gSample[j];
		}
	}
	for (int j = 0; j < 3; j++)
	{
		g[j] /= sampleNum;
	}
	*bx = g[0];
	*by = g[1];
	*bz = g[2];


	//�ָ�֮ǰ�ݴ��ƫ��
	setGyroBias(temp[0], temp[1], temp[2]);
}

void MPU6500::caliAccel()
{
	getAccelBias(accelBiasSub, accelBiasSub + 1, accelBiasSub + 2);
}

void MPU6500::setAccelBias(float bx, float by, float bz)
{
	accelBiasSub[0] = bx;
	accelBiasSub[1] = by;
	accelBiasSub[2] = bz;
}

void MPU6500::getAccelBias(float* bx, float* by, float* bz, int sampleNum /*= 100*/)
{
	double a[3] = { 0 };
	//�ݴ�֮ǰ��ƫ��
	float temp[3];
	for (int i = 0; i < 3; i++)
	{
		temp[i] = accelBiasSub[i];
	}
	setAccelBias(0, 0, 0);

	//����gSample��ȡƽ��
	float gSample[3];
	for (int i = 0; i < sampleNum; i++)
	{
		getAccel(gSample, gSample + 1, gSample + 2);
		for (int j = 0; j < 3; j++)
		{
			a[j] += gSample[j];
		}
	}
	for (int j = 0; j < 3; j++)
	{
		a[j] /= sampleNum;
	}
	*bx = a[0];
	*by = a[1];
	*bz = a[2] - 1;//��ȥ�������ٶ�1g

	//�ָ�֮ǰ�ݴ��ƫ��
	setAccelBias(temp[0], temp[1], temp[2]);
}
