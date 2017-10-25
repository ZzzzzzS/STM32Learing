/*************************718����������**********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����

*************************************************************/


#include "stm32f10x_it.h"
#include "TIM.h"
#define LED1_PORT  			GPIOC									//����һЩ�ܽ�
#define LED2_PORT  			GPIOC
#define LED3_PORT       GPIOC
#define LED4_PORT       GPIOC
#define LED_GPIO_CLK   RCC_APB2Periph_GPIOC
#define LED1_Pin        GPIO_Pin_6
#define LED2_Pin        GPIO_Pin_7
#define LED3_Pin        GPIO_Pin_8
#define LED4_Pin        GPIO_Pin_9

/*******************     GPIOD      *************************/

#define LED5_PORT  GPIOD
#define LED6_PORT  GPIOD

#define LED5_Pin  GPIO_Pin_14
#define LED6_Pin  GPIO_Pin_15

int time = 0;//�����ʱ����time
void LED_GPIO_Config()
	{
	GPIO_InitTypeDef GPIO_InitStructure;			//GPIO��ʼ���ṹ��					
  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);			//��GPIOʱ��	
  GPIO_InitStructure.GPIO_Pin = LED1_Pin |LED2_Pin |LED3_Pin |LED4_Pin ;			//ѡ��GPIO����	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//���ùܽ��������Ϊ50MHZ
  GPIO_Init(LED1_PORT, &GPIO_InitStructure);			//��ɳ�ʼ��
}

void led_off(){
	GPIO_ResetBits(LED1_PORT,LED1_Pin |LED2_Pin |LED3_Pin |LED4_Pin);	//�˿���0 ��LED
}

void led_on(){
	GPIO_SetBits(LED1_PORT,LED1_Pin |LED2_Pin |LED3_Pin |LED4_Pin);	//�˿���1 �ر�LED
}



int main() 
	{

		LED_GPIO_Config();												//��ʼ��LED��
    	BASIC_TIM_Init();													//��ʼ����ʱ��
		led_on();																	//�ȴ򿪵�
		while(1)
		{
			if(time==100)//��ʱ0.1s��ر�LED
			{
			led_off();
			}
			if(time==200)//�ٶ�ʱ0.1s���LED
			{
				time=0;
				led_on();
			}
		}
	}

	
void  TIM6_IRQHandler (void)//TIM6�жϷ�����
{
	if ( TIM_GetITStatus( TIM6, TIM_IT_Update) != RESET ) 
	{	
		time++;																					//���жϷ������н��м���
		TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);  		 
	}		 	
}
