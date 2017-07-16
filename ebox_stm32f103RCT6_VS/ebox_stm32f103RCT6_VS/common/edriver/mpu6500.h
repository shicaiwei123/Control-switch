#ifndef __MPU6500_H
#define __MPU6500_H

#include "ebox.h"


////////////////////////////////////////////////////////////////////////////////// 	
//���AD0��(9��)�ӵ�,IIC��ַΪ0X68(���������λ).
//�����V3.3,��IIC��ַΪ0X69(���������λ).
#define MPU6500_ADDRESS            0xD0  //MPU6500������IIC��ַ 0X68<<1
#define MPU6500_ID				0X71  	//MPU6500������ID
#define MPU6555_ID				0X73

//MPU6500���ڲ��Ĵ���
#define MPU6500_SELF_TESTX 		0X0D	//�Լ�Ĵ���X
#define MPU6500_SELF_TESTY 		0X0E	//�Լ�Ĵ���Y
#define MPU6500_SELF_TESTZ 		0X0F	//�Լ�Ĵ���Z
#define MPU6500_SELF_TESTA 		0X10	//�Լ�Ĵ���A
#define MPU6500_XG_OFFSET_H      0x13  // User-defined trim values for gyroscope
#define MPU6500_XG_OFFSET_L      0x14
#define MPU6500_YG_OFFSET_H      0x15
#define MPU6500_YG_OFFSET_L      0x16
#define MPU6500_ZG_OFFSET_H      0x17
#define MPU6500_ZG_OFFSET_L      0x18
#define MPU6500_SAMPLE_RATE 		0X19	//����Ƶ�ʷ�Ƶ��
#define MPU6500_CFG 				0X1A	//���üĴ���
#define MPU6500_GYRO_CFG 		0X1B	//���������üĴ���
#define MPU6500_ACCEL_CFG 		0X1C	//���ٶȼ����üĴ���
#define MPU6500_MOTION_DET 		0X1F	//�˶���ֵⷧ���üĴ���
#define MPU6500_FIFO_EN 			0X23	//FIFOʹ�ܼĴ���
#define MPU6500_I2CMST_CTRL 		0X24	//IIC�������ƼĴ���
#define MPU6500_I2CSLV0_ADDR 	0X25	//IIC�ӻ�0������ַ�Ĵ���
#define MPU6500_I2CSLV0 			0X26	//IIC�ӻ�0���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV0_CTRL 	0X27	//IIC�ӻ�0���ƼĴ���
#define MPU6500_I2CSLV1_ADDR 	0X28	//IIC�ӻ�1������ַ�Ĵ���
#define MPU6500_I2CSLV1 			0X29	//IIC�ӻ�1���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV1_CTRL 	0X2A	//IIC�ӻ�1���ƼĴ���
#define MPU6500_I2CSLV2_ADDR 	0X2B	//IIC�ӻ�2������ַ�Ĵ���
#define MPU6500_I2CSLV2 			0X2C	//IIC�ӻ�2���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV2_CTRL 	0X2D	//IIC�ӻ�2���ƼĴ���
#define MPU6500_I2CSLV3_ADDR 	0X2E	//IIC�ӻ�3������ַ�Ĵ���
#define MPU6500_I2CSLV3 			0X2F	//IIC�ӻ�3���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV3_CTRL 	0X30	//IIC�ӻ�3���ƼĴ���
#define MPU6500_I2CSLV4_ADDR 	0X31	//IIC�ӻ�4������ַ�Ĵ���
#define MPU6500_I2CSLV4 			0X32	//IIC�ӻ�4���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV4_DO 		0X33	//IIC�ӻ�4д���ݼĴ���
#define MPU6500_I2CSLV4_CTRL 	0X34	//IIC�ӻ�4���ƼĴ���
#define MPU6500_I2CSLV4_DI 		0X35	//IIC�ӻ�4�����ݼĴ���

#define MPU6500_I2CMST_STA 		0X36	//IIC����״̬�Ĵ���
#define MPU6500_INTBP_CFG 		0X37	//�ж�/��·���üĴ���
#define MPU6500_INT_EN 			0X38	//�ж�ʹ�ܼĴ���
#define MPU6500_INT_STA 			0X3A	//�ж�״̬�Ĵ���

#define MPU6500_ACCEL_XOUTH 		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU6500_ACCEL_XOUTL 		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU6500_ACCEL_YOUTH 		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU6500_ACCEL_YOUTL 		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU6500_ACCEL_ZOUTH 		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU6500_ACCEL_ZOUTL 		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���

#define MPU6500_TEMP_OUTH 		0X41	//�¶�ֵ�߰�λ�Ĵ���
#define MPU6500_TEMP_OUTL 		0X42	//�¶�ֵ��8λ�Ĵ���

#define MPU6500_GYRO_XOUTH 		0X43	//������ֵ,X���8λ�Ĵ���
#define MPU6500_GYRO_XOUTL 		0X44	//������ֵ,X���8λ�Ĵ���
#define MPU6500_GYRO_YOUTH 		0X45	//������ֵ,Y���8λ�Ĵ���
#define MPU6500_GYRO_YOUTL 		0X46	//������ֵ,Y���8λ�Ĵ���
#define MPU6500_GYRO_ZOUTH 		0X47	//������ֵ,Z���8λ�Ĵ���
#define MPU6500_GYRO_ZOUTL 		0X48	//������ֵ,Z���8λ�Ĵ���

#define MPU6500_I2CSLV0_DO 		0X63	//IIC�ӻ�0���ݼĴ���
#define MPU6500_I2CSLV1_DO 		0X64	//IIC�ӻ�1���ݼĴ���
#define MPU6500_I2CSLV2_DO 		0X65	//IIC�ӻ�2���ݼĴ���
#define MPU6500_I2CSLV3_DO 		0X66	//IIC�ӻ�3���ݼĴ���

#define MPU6500_I2CMST_DELAY 	0X67	//IIC������ʱ����Ĵ���
#define MPU6500_SIGPATH_RST 		0X68	//�ź�ͨ����λ�Ĵ���
#define MPU6500_MDETECT_CTRL 	0X69	//�˶������ƼĴ���
#define MPU6500_USER_CTRL 		0X6A	//�û����ƼĴ���
#define MPU6500_PWR_MGMT1 		0X6B	//��Դ����Ĵ���1
#define MPU6500_PWR_MGMT2 		0X6C	//��Դ����Ĵ���2 
#define MPU6500_FIFO_CNTH 		0X72	//FIFO�����Ĵ����߰�λ
#define MPU6500_FIFO_CNTL 		0X73	//FIFO�����Ĵ����Ͱ�λ
#define MPU6500_FIFO_RW 			0X74	//FIFO��д�Ĵ���
#define MPU6500_DEVICE_ID 		0X75	//����ID�Ĵ���

#define MPU6500_XA_OFFSET_H      0x77
#define MPU6500_XA_OFFSET_L      0x78
#define MPU6500_YA_OFFSET_H      0x7A
#define MPU6500_YA_OFFSET_L      0x7B
#define MPU6500_ZA_OFFSET_H      0x7D
#define MPU6500_ZA_OFFSET_L      0x7E

typedef enum
{
	MPU6500_Model_6500 = 0,
	MPU6500_Model_6555 = 1
}MPU6500_Model_Typedef;

typedef enum
{
	MPU6500_Gyro_Full_Scale_250dps = 0,
	MPU6500_Gyro_Full_Scale_500dps = 1,
	MPU6500_Gyro_Full_Scale_1000dps = 2,
	MPU6500_Gyro_Full_Scale_2000dps = 3
}MPU6500_Gyro_Full_Scale_Typedef;

typedef enum
{
	MPU6500_Accel_Full_Scale_2g = 0,
	MPU6500_Accel_Full_Scale_4g = 1,
	MPU6500_Accel_Full_Scale_8g = 2,
	MPU6500_Accel_Full_Scale_16g = 3
}MPU6500_Accel_Full_Scale_Typedef;

typedef enum
{
	MPU6500_DLPF_Bandwidth_250Hz = 0,
	MPU6500_DLPF_Bandwidth_184Hz = 1,
	MPU6500_DLPF_Bandwidth_92Hz = 2,
	MPU6500_DLPF_Bandwidth_41Hz = 3,
	MPU6500_DLPF_Bandwidth_20Hz = 4,
	MPU6500_DLPF_Bandwidth_10Hz = 5,
	MPU6500_DLPF_Bandwidth_5Hz = 6,
	MPU6500_DLPF_Bandwidth_3600Hz = 7
}MPU6500_DLPF_Bandwidth_Typedef;

typedef enum
{
	MPU6500_A_DLPF_Bandwidth_218_1Hz = 1,
	MPU6500_A_DLPF_Bandwidth_99Hz = 2,
	MPU6500_A_DLPF_Bandwidth_44_8Hz = 3,
	MPU6500_A_DLPF_Bandwidth_21_2Hz = 4,
	MPU6500_A_DLPF_Bandwidth_10_2Hz = 5,
	MPU6500_A_DLPF_Bandwidth_5_05Hz = 6,
	MPU6500_A_DLPF_Bandwidth_420Hz = 7
}MPU6500_A_DLPF_Bandwidth_Typedef;

class MPU6500:public I2cIC
{
protected:
	//���ò���
	uint8_t address;
	u8 mpuID;//��ͬ�ͺŵ�ID��������֤�Ƿ�������ȷ
	u16 sampleRate;

	//�洢ID���ͺŵĶ�Ӧ��ϵ
	static const uint8_t mpuIDList[];

	//�洢�������̣�����ת����׼��λ
	uint16_t gyroFsr;
	uint8_t accelFsr;

	//���̼Ĵ���ֵ�����̵Ķ�Ӧ��ϵ
	static const uint16_t gyroFsrList[];
	static const uint8_t accelFsrList[];

	//У׼ƫ��
	float gyroBiasSub[3], accelBiasSub[3];

public:
	MPU6500(I2c* i2c, MPU6500_Model_Typedef model = MPU6500_Model_6500, uint8_t address = MPU6500_ADDRESS);

	void begin(uint32_t speed = 400000, uint16_t sampleRate = 1000,
		MPU6500_Gyro_Full_Scale_Typedef gyroFsr = MPU6500_Gyro_Full_Scale_2000dps,
		MPU6500_Accel_Full_Scale_Typedef accelFsr = MPU6500_Accel_Full_Scale_8g,
		MPU6500_DLPF_Bandwidth_Typedef bwDLPF = MPU6500_DLPF_Bandwidth_41Hz,
		MPU6500_A_DLPF_Bandwidth_Typedef bwADLPF = MPU6500_A_DLPF_Bandwidth_44_8Hz);

	//���������Ǵ����������̷�Χ
	//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
	void setGyroFsr(MPU6500_Gyro_Full_Scale_Typedef fsr);

	//���ü��ٶȴ����������̷�Χ
	//fsr:0,��2g;1,��4g;2,��8g;3,��16g
	void setAccelFsr(MPU6500_Accel_Full_Scale_Typedef fsr);

	//����Gyro��Accel���ֵ�ͨ�˲���
	//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
	void setBothLPF(MPU6500_DLPF_Bandwidth_Typedef bwDLPF, MPU6500_A_DLPF_Bandwidth_Typedef bwADLPF);

	//����Gyro���ֵ�ͨ�˲���
	void setDLPF(MPU6500_DLPF_Bandwidth_Typedef bwDLPF);

	//����Accel���ֵ�ͨ�˲���
	void setADLPF(MPU6500_A_DLPF_Bandwidth_Typedef bwADLPF);

	//���ò�����4~1000(Hz)
	void setSampleRate(u16 sampleRate);
	//��ȡ������
	u16 getSampleRate();

	//����bypassģʽ
	void setBypass();

	//�õ��¶�ֵ
	float getTemp(void);

	//�õ�������ֵ(ԭʼֵ)
	//gx,gy,gz:������x,y,z���ԭʼ����(������)
	void getGyro(short *gx, short *gy, short *gz);
	//gx,gy,gz:������x,y,z��ı�׼��λ����
	void getGyro(float *gx, float *gy, float *gz);

	//�õ����ٶ�ֵ(ԭʼֵ)
	//gx,gy,gz:���ٶ�x,y,z���ԭʼ����(������)
	void getAccel(short *ax, short *ay, short *az);
	//gx, gy, gz:���ٶ�x, y, z��ı�׼��λ����(g)
	void getAccel(float *ax, float *ay, float *az);


	///У׼

	//�ھ�ֹ�������ֱ�ӵ���caliGyro
	void caliGyro();

	//����GyroBias
	void setGyroBias(float bx, float by, float bz);
	//��ȡsampleNum�β�����У׼ǰ���ݣ���Ϊƫ��
	void getGyroBias(float* bx, float* by, float* bz, int sampleNum = 100);

	//��ˮƽ���õ������ֱ�ӵ���caliAccel
	void caliAccel();

	//����GyroBias
	void setAccelBias(float bx, float by, float bz);
	//��ȡsampleNum�β�����У׼ǰ���ݣ���Ϊƫ��
	void getAccelBias(float* bx, float* by, float* bz, int sampleNum = 100);
};


#endif


