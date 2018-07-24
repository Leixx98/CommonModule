#ifndef __DAC904_H__
#define __DAC904_H__


#define DATA1_SET           GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define DATA1_CLR           GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_2, 0)
#define DATA2_SET           GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define DATA2_CLR           GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_1, 0)
#define DATA3_SET           GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_0, GPIO_PIN_0)
#define DATA3_CLR           GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_0, 0)
#define DATA4_SET           GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, GPIO_PIN_0)
#define DATA4_CLR           GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, 0)
#define DATA5_SET           GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define DATA5_CLR           GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, 0)
#define DATA6_SET           GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define DATA6_CLR           GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2, 0)
#define DATA7_SET           GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define DATA7_CLR           GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_3, 0)
#define DATA8_SET           GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_0, GPIO_PIN_0)
#define DATA8_CLR           GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_0, 0)
#define DATA9_SET           GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_1, GPIO_PIN_1)
#define DATA9_CLR           GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_1, 0)
#define DATA10_SET         GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define DATA10_CLR         GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_2, 0)
#define DATA11_SET         GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define DATA11_CLR         GPIOPinWrite(GPIO_PORTQ_BASE, GPIO_PIN_3, 0)
#define DATA12_SET         GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_7, GPIO_PIN_7)
#define DATA12_CLR         GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_7, 0)
#define DATA13_SET         GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, GPIO_PIN_6)
#define DATA13_CLR         GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, 0)
#define DATA14_SET         GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_4, GPIO_PIN_4)
#define DATA14_CLR         GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_4, 0)
#define CLK_SET                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define CLK_CLR                GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0)


void DAC904_Init(void);
void DACWrite(uint16_t value);
void DACWaveOut(void);


#endif






