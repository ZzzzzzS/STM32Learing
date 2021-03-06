/*************************718开发板例程**********************

*   编写：718创新实验室
*		平台：STM32F103VET6科创培训开发板
*		说明：该例程使用官方库进行编写，由于作者的水平有限， 
*								若有不足之处， 还请大家见谅
*									建议大家多查阅数据手册，多在新生群和大家交流。

*************************************************************/
#include "include.h"
#include <stdio.h>
#include "SerialPortImformation.h"

//宏定义 总线时钟 GPIO时钟 波特率
#define USART_CLK RCC_APB2Periph_USART1
#define USART_GPIO_CLK RCC_APB2Periph_GPIOA
#define USART_BAUDRATE 115200
#define USARTx USART1
#define USARTx_APBxClkCmd RCC_APB2PeriphClockCmd

//USART GPIO管脚宏定义
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

	serialPortInfo blueToothInfo; //判断串口信息需要的结构体

int main() {

	
	/*初始化USART 配置模式为 115200 8-N-1，*/
  USART_Config();

	printf("718创新实验室\n\n\n\n");
		
while(1){
	serialPortexec(&blueToothInfo); //在while1当中一直判断是不是有有用的指令
}

}


/*
函数名： void USART_Config(void)
作用： 		USART初始化
参数：    void
返回：		void
说明：		USART1 使用APB2 时钟 其他使用APB1时钟�
					详细设置可见数据手册
*/
void USART_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;		//GPIO初始化结构体
	USART_InitTypeDef USART_InitStructure;	//USART初始化结构体
	//打开GPIO时钟
	RCC_APB2PeriphClockCmd(USART_GPIO_CLK,ENABLE);
	//打开串口外设时钟
	USARTx_APBxClkCmd(USART_CLK,ENABLE);
	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);
  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);
// 配置串口的工作参数
	// 配置波特率为115200
	USART_InitStructure.USART_BaudRate = USART_BAUDRATE;
	// 配置 针数据字长为8位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位 1位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位 不检验
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制  无
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode =  USART_Mode_Rx|USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(USARTx, &USART_InitStructure);
	//使能USART
	USART_Cmd(USARTx,ENABLE);
	//中断初始化
	NVIC_Configuration();
	//使能USART接收中断
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	
	
}
/*
函数名： NVIC_Configuration(void)
作用： 		初始化中断
参数：    void
返回：		void
说明：		详细信息可见技术手册
*/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择  抢断优先级两位 子优先级两位 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}



/*
函数名：	USART3_IRQHandler(void)
作用： 		读取接收到的数据 并回发
参数：    void
返回：		void
说明：		使能中断后，当标志位USART_IT_RXNE为1时（接收寄存器非空） 进入中断
					如果外界有多个中断请求源 各个中断源均会引起USART3_IRQ中断  所以需要在中断内部判断具体为哪一中断请求源引起的中断
					详细详细可见技术手册
*/
void USART1_IRQHandler(void){
	uint8_t ucTemp;
	if(USART_GetITStatus(USARTx,USART_IT_RXNE)!=RESET)		//确认为接收寄存器空中断
	{		
		ucTemp = USART_ReceiveData(USARTx);
		addSerialPortDate(ucTemp,&blueToothInfo);				//这就是添加数据到结构体中
	}	 
}
int fputc(int ch, FILE *f)  //警告删除这个函数就会导致printf工作不正常,如果不需要printf也可以删除
{
		USART_SendData(USARTx, (uint8_t) ch);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		
		return (ch);
}
void function1ButtonClickedEvent()							//如果功能键一被按下,就会执行这个函数
{
	//在这里写功能键一被按下需要执行的操作吧
}
