#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"

#include "utils/uartstdio.h"

#include "functions/delay.h"
#include "functions/dac8501.h"


/*******************************************
�������ƣ�Dac8501__IO_Init
��    �ܣ���ʼ��SPI��������
��    ������
����ֵ  ����
********************************************/
void DAC8501_IO_Init()       
{
  //Init GPIOB,P
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
  // Check if the peripheral access is enabled.
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
	{
	}	
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOP))
	{
	}		
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE,GPIO_PIN_0|GPIO_PIN_1);
	//��������ǿ��
	GPIOPadConfigSet(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_5,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTP_BASE,GPIO_PIN_0|GPIO_PIN_1,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

/*******************************************
�������ƣ�DAC_Transform
��    �ܣ���һ��24λ����������������Ӧ
��    ����temp-24λ����������
					channel-ͨ��ѡ��1��2
����ֵ  ����
********************************************/
void DAC8501_Transform(uint32_t temp,uint8_t channel)
{
        uint8_t i;
        DAC8501_CLK_CLR;
        delay_us(1);
				if(channel==1)
					{DAC8501_CS1_CLR;}     //����Ƭѡ���������ݴ���
				else if(channel==2)
					{DAC8501_CS2_CLR;}
        delay_us(1);   
        for(i=0;i<24;i++)
        {
        	if(temp & 0x800000) {DAC8501_SDA_SET;} //�������λΪ0���õ������ߣ���������
            else  {DAC8501_SDA_CLR;}
            DAC8501_CLK_SET;
            delay_us(1);
            temp<<=1;
            delay_us(1);
            DAC8501_CLK_CLR;        //�½��ض�ȡ����
        }
				if(channel==1)
					{DAC8501_CS1_SET;}     //����Ƭѡ���������ݴ���
				else if(channel==2)
					{DAC8501_CS2_SET;}
        delay_us(1);
        DAC8501_CLK_SET; 

}

/*******************************************
�������ƣ� VoltToData
��    �ܣ���ģ���ѹֵת��Ϊ16λ��������
��    ����out_volt-ģ���ѹֵ
����ֵ  ��16λ��������
���䣺//(uint)(out_volt*4095)/(2*2.048) �Ƚ���ѹֵת��Ϊ0~4095������
        //0x0fff&  ת����16λ������������12λΪ����λ
********************************************/
uint32_t DAC8501_VoltToData(float out_volt) //˵��refΪ�ο�Դ��out_voltΪ���ģ���ѹֵ
{ 
   uint32_t temp;
   temp=(uint32_t)(out_volt*65536/(2*2.5));
	 //����Ϊ����ģʽ
   return(temp&0x00ffff);
}//����ѹֵת��Ϊ��Ӧ��24λ����������


/*******************************************
�������ƣ� Write_Data_Channel1
��    ��: ��ͨ��1д������
��    ����out_volt-ģ���ѹֵ
����ֵ  ����
���䣺//(uint)(out_volt*4095)/(2*2.048) �Ƚ���ѹֵת��Ϊ0~4095������
        //0x0fff&  ת����16λ������������12λΪ����λ
        //0xc000|  ǰ�����4λΪ1100������λ��������ģʽ���������ģ�д���ݵ�Aͨ��
********************************************/
void Write_Data_Channel1(float out_volt)
{
   uint32_t Data;
   Data=DAC8501_VoltToData(out_volt);//Aͨ��
   DAC8501_Transform(Data,1);
}

/*******************************************
�������ƣ� Write_Data_Channel2
��    ��: ��ͨ��2д������
��    ����out_volt-ģ���ѹֵ
����ֵ  ����
���䣺//(uint)(out_volt*4095)/(2*2.048) �Ƚ���ѹֵת��Ϊ0~4095������
        //0x0fff&  ת����16λ������������12λΪ����λ
        //0xc000|  ǰ�����4λΪ1100������λ��������ģʽ���������ģ�д���ݵ�Aͨ��
********************************************/
void Write_Data_Channel2(float out_volt)
{
   uint32_t Data;
   Data=DAC8501_VoltToData(out_volt);//Aͨ��
   DAC8501_Transform(Data,2);
}

