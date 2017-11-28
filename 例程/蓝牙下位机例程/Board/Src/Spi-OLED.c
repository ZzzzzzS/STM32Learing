/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ     
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



#include "Spi-OLED.h"			//OLEDͷ�ļ�
#include "OLED_Fonts.h"		//OLED�ֿ��ļ�

#define XLevelL		0x00		
#define XLevelH		0x10		
#define XLevel		((XLevelH&0x0F)*16+XLevelL)	
#define Max_Column	128		
#define Max_Row		  64		
#define	Brightness	0xCF

#define X_WIDTH 128				//����OLED�ı߽�
#define Y_WIDTH 64				//����OLED�ı߽�

#define byte unsigned char //��unsigned char ȡ������byte
	
/*************************���º�������OLED���ڲ�����,�û�����Ҫ������Щ����************************/
void OLED_WrDat(unsigned char data);	//��OLEDд���ݺ���
void OLED_WrCmd(unsigned char cmd);		//��OLEDд�����
void OLED_Set_Pos(unsigned char x, unsigned char y);		//�趨׼��д������꺯��
void OLED_P8x16Str(unsigned char x, unsigned char y, unsigned char *ch);		//д��Ӣ���ַ�����
void OLED_P14x16Str(unsigned char x, unsigned char y, unsigned char *ch);		//д�������ַ�����
void OLED_Pins_Init(void);						//OLED�ܽų�ʼ������
void OLED_Fill(unsigned char bmp_data);
/*************************���Ϻ�������OLED���ڲ�����,�û�����Ҫ������Щ����************************/

/*============================================
��������LCD_DLY_ms(u16 ms)
���ã���ʱ����
==========================================*/
void LCD_DLY_ms(u16 ms)
{                         
  u16 a;
  while(ms)
  {
    a=1335;
    while(a--);
    ms--;
  }
  return;
}

/*============================================
��������OLED_WrDat(unsigned char data)
���ã���OLED��Ļд����
==========================================*/

void OLED_WrDat(unsigned char data)
{
	unsigned char retry=0;
	GPIO_SetBits(GPIOA,OLED_COMMAND_DATA_PIN); //�Ƚ����������л����øߵ�ƽ����д����״̬
	SPI_I2S_SendData(OLED_SPI,data);						//ʹ��SPI��������
	while (SPI_I2S_GetFlagStatus(OLED_SPI, SPI_I2S_FLAG_RXNE) == RESET) //�ȴ����ͳɹ�
	{
		retry++;
		if(retry>20)return;
	}
}

/*============================================
��������OLED_WrCmd(unsigned char cmd)
���ã���OLED��Ļд����
==========================================*/

void OLED_WrCmd(unsigned char cmd)
{
	unsigned char retry=0;
	GPIO_ResetBits(GPIOA,OLED_COMMAND_DATA_PIN);//�Ƚ����������л����øߵ�ƽ����д����״̬
	SPI_I2S_SendData(OLED_SPI,cmd);
	while (SPI_I2S_GetFlagStatus(OLED_SPI, SPI_I2S_FLAG_RXNE) == RESET)
	{
		retry++;
		if(retry>20)return;
	}
	
}

/*============================================
��������OLED_Pins_Init()
���ã�OLED�ܽų�ʼ������
==========================================*/
/*************************����˵��******************************
�ܽų�ʼ������:
	����Ӧ��ʱ���ſ�(�൱���ܿ���)->
	���ùܽų�ʼ��(�Ƿ���������,�Ƿ��˲���)->
	������Ӧģ���ʼ��
****************************************************************/

void OLED_Pins_Init()
{
	SPI_InitTypeDef OLED_SPI_Init;							//SPIģ�����ýṹ��
	GPIO_InitTypeDef OLED_SPI_GPIO_Init;				//SPI�ܽ����ýṹ��
	GPIO_InitTypeDef OLED_GPIO_Init;						//��λ��,��������ѡ�������ýṹ��
	
	/*************************��һ��************************/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);	 //��SPI1ģ���ʱ���ſ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);	//��GPIOʱ���ſ�
	
	/*************************�ڶ���************************/
	
	OLED_SPI_GPIO_Init.GPIO_Mode=GPIO_Mode_AF_PP;  //����SPI�ܽ�Ϊ���������������
	OLED_SPI_GPIO_Init.GPIO_Pin=GPIO_Pin_5 | GPIO_Pin_7; //����SPI��ʼ���ܽ�
	OLED_SPI_GPIO_Init.GPIO_Speed=GPIO_Speed_50MHz; //���ùܽŷ�Ӧ�ٶ�Ϊ�����ģʽ
	GPIO_Init(GPIOA,&OLED_SPI_GPIO_Init);						//��ʼ��SPI�ܽ�
	
	OLED_GPIO_Init.GPIO_Mode=GPIO_Mode_Out_PP;			//���ø�λ�߳�ʼ��,������ͬ��
	OLED_GPIO_Init.GPIO_Pin=OLED_RESET_PIN | OLED_COMMAND_DATA_PIN;
	OLED_GPIO_Init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&OLED_GPIO_Init);
	
	/*************************������************************/
	
	OLED_SPI_Init.SPI_Mode=SPI_Mode_Master;					//����SPIģʽΪ����ģʽ
	OLED_SPI_Init.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_8;		//����SPI��Ԥ��Ƶ
	OLED_SPI_Init.SPI_CPHA=SPI_CPHA_2Edge;
	OLED_SPI_Init.SPI_CPOL=SPI_CPOL_High;
	OLED_SPI_Init.SPI_DataSize=SPI_DataSize_8b;											//����SPI�������ݳ���
	OLED_SPI_Init.SPI_Direction=SPI_Direction_2Lines_FullDuplex;		//����SPIΪȫ˫��ģʽ
	OLED_SPI_Init.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(OLED_SPI,&OLED_SPI_Init);															//��ʼ��SPI
	SPI_Cmd(OLED_SPI,ENABLE);																				//����SPIģ��
	
	
}

/*============================================
��������OLED_CLS(void)
���ã�OLED����Ļ
==========================================*/

void OLED_CLS(void)
{
	byte y, x;
	for (y = 0; y<8; y++)
	{
		OLED_WrCmd(0xb0 + y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for (x = 0; x<X_WIDTH; x++)
			OLED_WrDat(0);
	}
}

void OLED_Fill(byte bmp_data)
{
	byte y, x;

	for (y = 0; y<8; y++)
	{
		OLED_WrCmd(0xb0 + y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for (x = 0; x<X_WIDTH; x++)
			OLED_WrDat(bmp_data);
	}
}

/*============================================
��������OLED_Set_Pos(byte x, byte y)
���ã�OLED�趨׼��д�������λ��
==========================================*/

void OLED_Set_Pos(byte x, byte y)
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
	OLED_WrCmd(x & 0x0f);//|0x01);
}

/*============================================
��������OLED_Init()
���ã�OLED��ʼ��
==========================================*/

void OLED_Init()
{
	OLED_Pins_Init();												//OLED��ʼ���ܽ�
	GPIO_SetBits(GPIOA,OLED_RESET_PIN);			//��λ������͵�ƽ��λ�ź�
	LCD_DLY_ms(50);													//��λ������͵�ƽ��λ�ź�
	GPIO_ResetBits(GPIOA,OLED_RESET_PIN);		//��λ������͵�ƽ��λ�ź�
	LCD_DLY_ms(50);													//��λ������͵�ƽ��λ�ź�
	GPIO_SetBits(GPIOA,OLED_RESET_PIN);			//��λ������͵�ƽ��λ�ź�
	
	/*************************������OLED�������������ʼ��OLED************************/
	
	OLED_WrCmd(0xae);//--turn off oled pane
  OLED_WrCmd(0x00);//---set low column address
  OLED_WrCmd(0x10);//---set high column address
  OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WrCmd(0x81);//--set contrast control register
  OLED_WrCmd(0xcf); // Set SEG Output Current Brightness
  OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0???? 0xa1??
  OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0???? 0xc8??
  OLED_WrCmd(0xa6);//--set normal display
  OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
  OLED_WrCmd(0x3f);//--1/64 duty
  OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WrCmd(0x00);//-not offset
  OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
  OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  OLED_WrCmd(0xd9);//--set pre-charge period
  OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WrCmd(0xda);//--set com pins hardware configuration
  OLED_WrCmd(0x12);
  OLED_WrCmd(0xdb);//--set vcomh
  OLED_WrCmd(0x40);//Set VCOM Deselect Level
  OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_WrCmd(0x02);//
  OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
  OLED_WrCmd(0x14);//--set(0x10) disable
  OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
  OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
  OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00);  //????
	OLED_Set_Pos(0, 0);
}


void OLED_PutPixel(byte x, byte y)
{
	byte data1;

	OLED_Set_Pos(x, y);
	data1 = 0x01 << (y % 8);
	OLED_WrCmd(0xb0 + (y >> 3));
	OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
	OLED_WrCmd((x & 0x0f) | 0x00);
	OLED_WrDat(data1);
}

void OLED_Rectangle(byte x1, byte y1, byte x2, /*byte y2,*/ byte gif)
{
	byte n;

	OLED_Set_Pos(x1, y1 >> 3);
	for (n = x1; n <= x2; n++)
	{
		OLED_WrDat(0x01 << (y1 % 8));
		if (gif == 1);
	}
	/*OLED_Set_Pos(x1, y2 >> 3);
	for (n = x1; n <= x2; n++)
	{
		OLED_WrDat(0x01 << (y2 % 8));
		if (gif == 1) 	OLED_DLY_ms(50);
	}*/

}

/*============================================
��������OLED_P8x16Str(byte x, byte y, byte ch[])
���ã�OLED���Ӣ���ַ�
==========================================*/

void OLED_P8x16Str(byte x, byte y, byte ch[])
{
	byte c = 0, i = 0, j = 0;

	while (ch[j] != '\0')
	{
		c = ch[j] - 32;
		if (x>120) { x = 0; y++; }
		OLED_Set_Pos(x, y);
		for (i = 0; i<8; i++)
		{
			OLED_WrDat(F8X16[c * 16 + i]);

		}
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i<8; i++)
		{
			OLED_WrDat(F8X16[c * 16 + i + 8]);

		}
		x += 8;
		j++;
	}
}

/*============================================
��������OLED_P14x16Str(byte x, byte y, byte ch[])
���ã�OLED��������ַ�
==========================================*/

void OLED_P14x16Str(byte x, byte y, byte ch[])
{
	byte wm = 0, ii = 0;
	int adder = 1;

	while (ch[ii] != '\0')
	{
		wm = 0;
		adder = 1;
		while (F14x16_Idx[wm] > 127)
		{
			if (F14x16_Idx[wm] == ch[ii])
			{
				if (F14x16_Idx[wm + 1] == ch[ii + 1])
				{
					adder = wm * 14;
					break;
				}
			}
			wm += 2;
		}
		if (x>118) { x = 0; y++; }
		OLED_Set_Pos(x, y);
		if (adder != 1)// ????					
		{
			OLED_Set_Pos(x, y);
			for (wm = 0; wm < 14; wm++)
			{
				OLED_WrDat(F14x16[adder]);
				adder += 1;
			}
			OLED_Set_Pos(x, y + 1);
			for (wm = 0; wm < 14; wm++)
			{
				OLED_WrDat(F14x16[adder]);
				adder += 1;
			}
		}
		else			  //??????			
		{
			ii += 1;
			OLED_Set_Pos(x, y);
			for (wm = 0; wm < 16; wm++)
			{
				OLED_WrDat(0);
			}
			OLED_Set_Pos(x, y + 1);
			for (wm = 0; wm < 16; wm++)
			{
				OLED_WrDat(0);
			}
		}
		x += 14;
		ii += 2;
	}
}

/*============================================
��������OLED_Print(byte x, byte y, byte ch[])(byte x, byte y, byte ch[])
���ã�OLED����ַ�,�Զ��ж���Ӣ��
==========================================*/


void OLED_Print(byte x, byte y, byte ch[])
{
	byte ch2[3];
	byte ii = 0;
	while (ch[ii] != '\0')
	{
		if (ch[ii] > 127)
		{
			ch2[0] = ch[ii];
			ch2[1] = ch[ii + 1];
			ch2[2] = '\0';	
			OLED_P14x16Str(x, y, ch2);	
			x += 14;
			ii += 2;
		}
		else
		{
			ch2[0] = ch[ii];
			ch2[1] = '\0';			
			OLED_P8x16Str(x, y, ch2);	
									
			x += 8;
			ii += 1;
		}
	}
}


void Draw_BMP(byte x0, byte y0, byte x1, byte y1, unsigned char bmp[])
{
	int ii = 0;
	byte x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y <= y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x <= x1; x++)
		{
			OLED_WrDat(bmp[ii++]);
		}
	}
}

void DisplayFloat(int i, unsigned char x, unsigned char y)
{
	unsigned char j;
	unsigned char a[6] = { 0 };
	if (i<0)
	{
		a[0] = '-';
		i = -i;
	}
	else
		a[0] = '+';
	a[1] = i / 10000;
	a[2] = i % 10000 / 1000;
	a[3] = '.';
	a[4] = i % 1000 / 100;
	a[5] = i % 100 / 10;
	
	for (j = 0; j<6; j++)
	{
		switch (a[j])
		{
		case 0: {OLED_Print(x, y, "0"); }break;
		case 1: {OLED_Print(x, y, "1"); }break;
		case 2: {OLED_Print(x, y, "2"); }break;
		case 3: {OLED_Print(x, y, "3"); }break;
		case 4: {OLED_Print(x, y, "4"); }break;
		case 5: {OLED_Print(x, y, "5"); }break;
		case 6: {OLED_Print(x, y, "6"); }break;
		case 7: {OLED_Print(x, y, "7"); }break;
		case 8: {OLED_Print(x, y, "8"); }break;
		case 9: {OLED_Print(x, y, "9"); }break;
		case '-': {OLED_Print(x, y, "-"); }break;
		case '+': {OLED_Print(x, y, "+"); }break;
		case '.': {OLED_Print(x, y, "."); }break;
		default:break;
		}
		x += 10;
		if (x == 90)
			x = 20;
	}
}
