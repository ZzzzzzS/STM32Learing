/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����	����ZZS
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ
*		 �����⣬����ϵ��QQ523939208     by 718 ZZS       
******************************************************************/

/*************************����˵��******************************
ͨ��SPI����OLED��Ļ
ʲô��OLED:�л��Է�������Ļhttps://baike.baidu.com/item/OLED%E5%B1%8F%E5%B9%95/1688158?fr=aladdin
ʲô��SPI:�μ��ٶȰٿ�
	https://baike.baidu.com/item/SPI/4429726?fr=aladdin
	OLED���õĲ��Ǳ�׼��SPIͨ��,���õ�4���߷ֱ���:
	D0:SPIʱ�ӿ�����										A5
	D1:SPI���ݴ�����,MOSI��������				A7
	RES:��λ��,��һ������͵�ƽ�͸�λ		A3
	DC:����/����ѡ����,�ߵ�ƽ����,�͵�ƽ����  A1
OLED���ƹ���:
	��ʼ��SPI������,��ʼ��GPIO�ܽ�->��ʼ��OLED��Ļ->��OLED��ĻдҪ��ʾ������
****************************************************************/



#ifndef SPI_OLED_H								//��ֹ�ظ�����ͷ�ļ�
#define SPI_OLED_H								//�����ͷ�ļ��Ͳ��ٶ���,��ֹ�ظ�����

#include <stm32f10x_spi.h>				//spiͨ��ͷ�ļ�
#include <stm32f10x_gpio.h>				//gpioͷ�ļ�


#define OLED_SPI SPI1							//����OLEDSPIΪSPI1
#define OLED_RESET_PIN					GPIO_Pin_3	//����OLED��λ��
#define OLED_COMMAND_DATA_PIN 	GPIO_Pin_1	//����OLED����ָ���л���

/*************************���º�����OLED�⺯��,�û���Ҫ������Щ����************************/

extern void OLED_Init(void);			//OLED��ʼ������
extern void OLED_CLS(void);				//OLED��������
extern void OLED_Print(unsigned char x,unsigned char y,unsigned char *ch);	//OLED����ַ�����
extern void OLED_PutPixel(unsigned char x, unsigned char y);

#endif
