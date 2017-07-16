#ifndef _OLED_I2C_H
#define _OLED_I2C_H

#include "ebox.h"

class OLEDI2C
{
	uint32_t speed;
	uint8_t adress;
	I2c* i2c;
	char *printf_buf;

	void write_byte(uint8_t reg_address, uint8_t data);
	//д����
	void write_cmd(unsigned char cmd);
	//д����
	void write_data(unsigned char dat);

public:
	OLEDI2C(I2c* i2c, uint8_t adress = 0x78);

	void begin(uint32_t speed = 400000);

	//������ʼ������
	void set_xy(unsigned char x, unsigned char y);

	//ȫ�����
	void fill(unsigned char fill_Data);

	//����
	void clear(void);

	//��OLED�������л���
	void display_on(void);

	//��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
	void display_off(void);

	void show_char(unsigned char x, unsigned char y, char ch, unsigned char TextSize = 1);

	//x,y -- ��ʼ������(x:0~127, y:0~7); ch[] -- Ҫ��ʾ���ַ���; TextSize -- �ַ���С(1:6*8 ; 2:8*16)
	//��ʾcodetab.h�е�ASCII�ַ�,��6*8��8*16��ѡ��
	void show_string(unsigned char x, unsigned char y, char ch[], unsigned char TextSize = 1);

	void printf(uint8_t x, uint8_t y, unsigned char TextSize, const char *fmt, ...);

	//x,y -- ��ʼ������(x:0~127, y:0~7); N:������codetab.h�е�����
	//��ʾcodetab.h�еĺ���,16*16����
	void show_chinese(unsigned char x, unsigned char y, unsigned char N);

	//x0,y0 -- ��ʼ������(x0:0~127, y0:0~7); x1,y1 -- ���Խ���(������)������(x1:1~128,y1:1~8)
	//��ʾBMPλͼ
	void draw_bmp(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);

};


#endif


