#include "stm32f10x.h"
#include "MPU6050.h"
#include "iic.h"

void delay_IIC( int ms );

//��ʼ��GPIO��6050
void Sys_Configuration(void)
{
	IIC_GPIO_Configuration( IIC_GOIO_SDA , IIC_SDA , IIC_GPIO_SCL , IIC_SCL );
	MPU6050_Inital();
}

//6050��ʼ������
void MPU6050_Inital(void)
{
	delay_IIC( 100 );
	//�������
	Single_Write_IIC( SLAVEADRESS , PWR_MGMT_1 , 0x00 );
	//����һЩ�Ĵ������������Բ���ͷ�ļ��к궨��
	Single_Write_IIC( SLAVEADRESS , SMPLRT_DIV , 0x07 );
	Single_Write_IIC( SLAVEADRESS , CONFIG , 0x06 );
	Single_Write_IIC( SLAVEADRESS , GYRO_CONFIG , 0x18 );
	Single_Write_IIC( SLAVEADRESS , ACCEL_CONFIG , 0x01 );
	//�����ٴν������
	Single_Write_IIC( SLAVEADRESS,PWR_MGMT_1,0x00);
	delay_IIC( 100 );
}


//��ȡX����ٶȷ���
int getAccX(void)
{
	int AccX = 0;
	char AccXH = 0 , AccXL = 0;

	AccXH = Single_Read_IIC( SLAVEADRESS , ACCEL_XOUT_H );
	AccXL = Single_Read_IIC( SLAVEADRESS , ACCEL_XOUT_L );

	AccX = (AccXH<<8)|AccXL;

	return AccX;
}

//��ȡY����ٶȷ���
int getAccY(void)
{
	int AccY = 0;
	char AccYH = 0 , AccYL = 0;

	AccYH = Single_Read_IIC( SLAVEADRESS , ACCEL_YOUT_H );
	AccYL = Single_Read_IIC( SLAVEADRESS , ACCEL_YOUT_L );

	AccY = (AccYH<<8)|AccYL;

	return AccY;
}

//��ȡZ����ٶȷ���
int getAccZ(void)
{
	int AccZ = 0;
	char AccZH = 0 , AccZL = 0;

	AccZH = Single_Read_IIC( SLAVEADRESS , ACCEL_ZOUT_H );
	AccZL = Single_Read_IIC( SLAVEADRESS , ACCEL_ZOUT_L );

	AccZ = (AccZH<<8)|AccZL;

	return AccZ;
}

//���X����ٶȷ���
int getGyroX(void)
{
	int GyroX = 0;
	char GyroXH = 0 , GyroXL = 0; 
	
	GyroXH = Single_Read_IIC( SLAVEADRESS , GYRO_XOUT_H );
	GyroXL = Single_Read_IIC( SLAVEADRESS , GYRO_XOUT_L );
	
	GyroX = (GyroXH<<8)|GyroXL;
	
	return GyroX;	
}
//��ȡY����ٶȷ���
int getGyroY(void)
{
   	int GyroY = 0;
	char GyroYH = 0 , GyroYL = 0; 
	
	GyroYH = Single_Read_IIC( SLAVEADRESS , GYRO_YOUT_H );
	GyroYL = Single_Read_IIC( SLAVEADRESS , GYRO_YOUT_L );
	
	GyroY = (GyroYH<<8)|GyroYL;
	
	return GyroY;	
}
//��ȡZ����ٶȷ���
int getGyroZ(void)
{
   	int GyroZ = 0;
	char GyroZH = 0 , GyroZL = 0; 
	
	GyroZH = Single_Read_IIC( SLAVEADRESS , GYRO_ZOUT_H );
	GyroZL = Single_Read_IIC( SLAVEADRESS , GYRO_ZOUT_L );
	
	GyroZ = (GyroZH<<8)|GyroZL;
	
	return GyroZ;	
}

//��ȡ�¶�ԭʼֵ
unsigned int getTemperature(void)
{
 	unsigned int temperature = 0;
	char temperatureH = 0 , temperatureL = 0;

	temperatureH = Single_Read_IIC( SLAVEADRESS , TEMP_OUT_H );
	temperatureL = Single_Read_IIC( SLAVEADRESS , TEMP_OUT_L );

	temperature = (temperatureH<<8)|temperatureL;

	return temperature;
}

//IICͨ���е���Ч��ʱ
void delay_IIC( int ms )
{
	int i,j;
	for( i = 0 ; i < ms ; i++ )
	{
		for( j = 0 ; j < 30000 ; j++ );
	}
}

