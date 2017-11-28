#ifndef __74HC595__
#define __74HC595__

extern unsigned char data_table[];
extern unsigned char row[];

//�궨���滻����飬���ٺ�����Ƶ������IO�ڵĴ�����
#define OE(a)                                                                  \
  {                                                                            \
    if (a) {                                                                   \
      GPIO_SetBits(GPIOD, GPIO_Pin_0);                                         \
    } else {                                                                   \
      GPIO_ResetBits(GPIOD, GPIO_Pin_0);                                       \
    }                                                                          \
  }
#define SER(a)                                                                 \
  {                                                                            \
    if (a) {                                                                   \
      GPIO_SetBits(GPIOC, GPIO_Pin_12);                                        \
    } else {                                                                   \
      GPIO_ResetBits(GPIOC, GPIO_Pin_12);                                      \
    }                                                                          \
  }
#define RCLK(a)                                                                \
  {                                                                            \
    if (a) {                                                                   \
      GPIO_SetBits(GPIOC, GPIO_Pin_10);                                        \
    } else {                                                                   \
      GPIO_ResetBits(GPIOC, GPIO_Pin_10);                                      \
    }                                                                          \
  }
#define SRCLK(a)                                                               \
  {                                                                            \
    if (a) {                                                                   \
      GPIO_SetBits(GPIOC, GPIO_Pin_11);                                        \
    } else {                                                                   \
      GPIO_ResetBits(GPIOC, GPIO_Pin_11);                                      \
    }                                                                          \
  }
#define beeset(a)                                                              \
  {                                                                            \
    if (a) {                                                                   \
      GPIO_SetBits(GPIOC, GPIO_Pin_8);                                         \
    } else {                                                                   \
      GPIO_ResetBits(GPIOC, GPIO_Pin_8);                                       \
    }                                                                          \
  }

//��ʼ��595��Ӧ����
extern void hc595_init(void);
//��595����һ����
extern void Send_595(unsigned char dat);
//�������ʾ
extern void DisplayScan(unsigned char column, unsigned char row);

#endif
