/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ     
******************************************************************/
#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f10x.h"
#include "stm32f10x_adc.h"

extern void NTC_CDS_Init(void);//���������ʼ��

extern uint16_t GetNTC(void);
extern uint16_t GetCDS(void);


#endif
