/*************************718����������**********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����

*************************************************************/
#include "include.h"
#include <stdio.h>
#include "SerialPortImformation.h"

//�궨�� ����ʱ�� GPIOʱ�� ������
#define USART_CLK RCC_APB2Periph_USART1
#define USART_GPIO_CLK RCC_APB2Periph_GPIOA
#define USART_BAUDRATE 115200
#define USARTx USART1
#define USARTx_APBxClkCmd RCC_APB2PeriphClockCmd

//USART GPIO�ܽź궨��
#define USART_TX_GPIO_PORT GPIOA
#define USART_TX_GPIO_PIN GPIO_Pin_9
#define USART_RX_GPIO_PORT GPIOA
#define USART_RX_GPIO_PIN GPIO_Pin_10

void USART_Config(void);
void NVIC_Configuration(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
void USART1_IRQHandler(void); 

	serialPortInfo blueToothInfo; //�жϴ�����Ϣ��Ҫ�Ľṹ��

int main() {

	
	/*��ʼ��USART ����ģʽΪ 115200 8-N-1��*/
  USART_Config();

	printf("718����ʵ����\n\n\n\n");
		
while(1){
	serialPortexec(&blueToothInfo); //��while1����һֱ�ж��ǲ��������õ�ָ��
}

}


/*
�������� void USART_Config(void)
���ã� 		USART��ʼ��
������    void
���أ�		void
˵����		USART1 ʹ��APB2 ʱ�� ����ʹ��APB1ʱ�ӣ
					��ϸ���ÿɼ������ֲ�
*/
void USART_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;		//GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;	//USART��ʼ���ṹ��
	//��GPIOʱ��
	RCC_APB2PeriphClockCmd(USART_GPIO_CLK,ENABLE);
	//�򿪴�������ʱ��
	USARTx_APBxClkCmd(USART_CLK,ENABLE);
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);
  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);
// ���ô��ڵĹ�������
	// ���ò�����Ϊ115200
	USART_InitStructure.USART_BaudRate = USART_BAUDRATE;
	// ���� �������ֳ�Ϊ8λ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ 1λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ ������
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������  ��
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode =  USART_Mode_Rx|USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(USARTx, &USART_InitStructure);
	//ʹ��USART
	USART_Cmd(USARTx,ENABLE);
	//�жϳ�ʼ��
	NVIC_Configuration();
	//ʹ��USART�����ж�
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	
	
}
/*
�������� NVIC_Configuration(void)
���ã� 		��ʼ���ж�
������    void
���أ�		void
˵����		��ϸ��Ϣ�ɼ������ֲ�
*/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ��  �������ȼ���λ �����ȼ���λ */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}



/*
��������	USART3_IRQHandler(void)
���ã� 		��ȡ���յ������� ���ط�
������    void
���أ�		void
˵����		ʹ���жϺ󣬵���־λUSART_IT_RXNEΪ1ʱ�����ռĴ����ǿգ� �����ж�
					�������ж���ж�����Դ �����ж�Դ��������USART3_IRQ�ж�  ������Ҫ���ж��ڲ��жϾ���Ϊ��һ�ж�����Դ������ж�
					��ϸ��ϸ�ɼ������ֲ�
*/
void USART1_IRQHandler(void){
	uint8_t ucTemp;
	if(USART_GetITStatus(USARTx,USART_IT_RXNE)!=RESET)		//ȷ��Ϊ���ռĴ������ж�
	{		
		ucTemp = USART_ReceiveData(USARTx);
		addSerialPortDate(ucTemp,&blueToothInfo);				//�����������ݵ��ṹ����
	}	 
}
int fputc(int ch, FILE *f)  //����ɾ����������ͻᵼ��printf����������,�������ҪprintfҲ����ɾ��
{
		USART_SendData(USARTx, (uint8_t) ch);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		
		return (ch);
}
void function1ButtonClickedEvent()							//��������ܼ�һ������,�ͻ�ִ���������
{
	//������д���ܼ�һ��������Ҫִ�еĲ�����
}
