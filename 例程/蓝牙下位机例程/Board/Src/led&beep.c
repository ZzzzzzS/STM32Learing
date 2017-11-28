/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ     
******************************************************************/

#include "led&beep.h"

/*============================================
������:LED_Init()
����:��ʼ������led��
==========================================*/

void LED_Init()					//led��ʼ��									
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PC,PD��ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //LED1-->PC.9������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.0
 GPIO_SetBits(GPIOC,GPIO_Pin_9);						 //PC.9 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //LED2-->PC.8 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_8); 						 //PC.8 ����� 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //LED3-->PC.7 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_7); 						 //PC.2 ����� 

		
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED4-->PC.6 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_6); 						 //PC.6 ����� 
 
 	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //LED5-->PD.15 �˿�����, �������
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOD,GPIO_Pin_15); 						 //PCD.15 ����� 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	    		 //LED6-->PD.14 �˿�����, �������
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOD,GPIO_Pin_14); 						 //PCD.14 ����� 
}


/*============================================
������:LEDPower(LEDNumber Number,PowerState State)
����:����led��
==========================================*/

void LEDPower(LEDNumber Number,PowerState State)
{
	if(Number==LED1)
	{
		if(State==Power_ON)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_9);
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_9);
		}
	}
	else if(Number==LED2)
	{
		if(State==Power_ON)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_8); 
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_8); 
		}
	}
	else if(Number==LED3)
	{
		if(State==Power_ON)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_7);
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_7);
		}
	}
	else if(Number==LED4)
	{
		if(State==Power_ON)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_6);
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_6);
		}
	}
	else if(Number==LED5)
	{
		if(State==Power_ON)
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_15); 
		}
		else
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_15); 
		}
	}
	else if(Number==LED6)
	{
		if(State==Power_ON)
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_14);  
		}
		else
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_14);  
		}
	}
	
}

/*============================================
������:BeepInit()
����:��ʼ��������
==========================================*/

void BeepInit()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PC,PD��ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //LED1-->PC.9������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.0
}

/*============================================
������:BeepPower(PowerState State)
����:���ط�����
==========================================*/

void BeepPower(PowerState State)
{
	if(State==Power_ON)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_12);
	}
	
}
