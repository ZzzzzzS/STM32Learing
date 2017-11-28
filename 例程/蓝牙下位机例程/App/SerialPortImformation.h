/*************************718������λ������*********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����
*���ڸ���ϸ��˵��,���Է���http://zzshub.cn/2017/11/28/%E6%96%B0%E7%94%9F%E6%9D%AF%E6%99%BA%E8%83%BD%E8%BD%A6%E8%B5%9B%E8%93%9D%E7%89%99%E6%8E%A5%E6%94%B6%E7%AB%AF/

*************************************************************/
#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#include <stm32f10x.h>
#define BUFFERSIZE 20 //��������С,һ�㲻��Ҫ�޸�
typedef enum    //��ʱû�õ�ö��
{
	Function1Clicked = 0x01,
	Function2Clicked = 0x02,
	Function3Clicked = 0x04,
	Function4Clicked = 0x08,
	FSTOPClicked     = 0x10,
	ReservedFunction = 0x20
} serialPortInformationType;


typedef struct		//������յ�����Ϣ�Ľṹ��
{
	int GoSpeed;		//ǰ���ٶ�
	int GoSpeedOld;
	int TurnSpeed;	//ת���ٶ�
	int TurnSpeedOld;
	uint8_t OtherInfo;
	unsigned char serialPortQueueBuffer[BUFFERSIZE+5];	//���ջ�����
} serialPortInfo;


extern void addSerialPortDate(unsigned char data,serialPortInfo *this); //�򻺳����������
extern void serialPortexec(serialPortInfo *serialPortInfo);							//��while����ѭ���ж���Ϣ
extern void speedchangeEvent(int xSpeed,int ySpeed);										//���ٷ����ı��ִ���������
extern void function1ButtonClickedEvent(void);					//���������»�ִ���������
extern void function2ButtonClickedEvent(void);
extern void function3ButtonClickedEvent(void);
extern void function4ButtonClickedEvent(void);
extern void stopButtonClickedEvent(void);

#endif
