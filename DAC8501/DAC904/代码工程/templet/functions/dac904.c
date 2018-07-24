#include <stdint.h>
#include <stdbool.h>
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
#include "utils/buttons.h"
#include "functions/dac904.h"
#include "functions/usart.h"

const uint16_t Wave_Value[256]={
 0x1FFF,0x20C8,0x2191,0x225A,0x2322,0x23EA,0x24B1,0x2577,0x263D,0x2702,0x27C5,0x2888,0x2949,0x2A09,0x2AC7,0x2B83
,0x2C3E,0x2CF7,0x2DAD,0x2E62,0x2F14,0x2FC5,0x3072,0x311D,0x31C6,0x326C,0x330F,0x33AF,0x344C,0x34E5,0x357C,0x360F
,0x369F,0x372C,0x37B5,0x383A,0x38BB,0x3939,0x39B2,0x3A28,0x3A9A,0x3B08,0x3B71,0x3BD6,0x3C37,0x3C94,0x3CEC,0x3D40
,0x3D8F,0x3DDA,0x3E20,0x3E61,0x3E9E,0x3ED6,0x3F09,0x3F37,0x3F61,0x3F86,0x3FA6,0x3FC1,0x3FD7,0x3FE8,0x3FF5,0x3FFC
,0x3FFE,0x3FFC,0x3FF5,0x3FE8,0x3FD7,0x3FC1,0x3FA6,0x3F86,0x3F61,0x3F37,0x3F09,0x3ED6,0x3E9E,0x3E61,0x3E20,0x3DDA
,0x3D8F,0x3D40,0x3CEC,0x3C94,0x3C37,0x3BD6,0x3B71,0x3B08,0x3A9A,0x3A28,0x39B2,0x3939,0x38BB,0x383A,0x37B5,0x372C
,0x369F,0x360F,0x357C,0x34E5,0x344C,0x33AF,0x330F,0x326C,0x31C6,0x311D,0x3072,0x2FC5,0x2F14,0x2E62,0x2DAD,0x2CF7
,0x2C3E,0x2B83,0x2AC7,0x2A09,0x2949,0x2888,0x27C5,0x2702,0x263D,0x2577,0x24B1,0x23EA,0x2322,0x225A,0x2191,0x20C8
,0x1FFF,0x1F36,0x1E6D,0x1DA4,0x1CDC,0x1C14,0x1B4D,0x1A87,0x19C1,0x18FC,0x1839,0x1776,0x16B5,0x15F5,0x1537,0x147B
,0x13C0,0x1307,0x1251,0x119C,0x10EA,0x1039,0x0F8C,0x0EE1,0x0E38,0x0D92,0x0CEF,0x0C4F,0x0BB2,0x0B19,0x0A82,0x09EF};

static uint8_t i;
//*****************************************************************************
//
//! DAC904引脚初始化
//!
//! This function must be called during application initialization to
//! configure the GPIO pins to which the pushbuttons are attached.  It enables
//! the port used by the buttons and configures each button GPIO as an input
//! with a weak pull-up.
//!
//! \return None.
//
//*****************************************************************************
void DAC904_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM))
    {
    }
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL))
    {
    }
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOQ))
    {
    }    
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK))
    {
    }       
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE,  GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);   
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE,  GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);     
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE,  GPIO_PIN_6|GPIO_PIN_7); 
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,  GPIO_PIN_2); 
    GPIOPadConfigSet(GPIO_PORTM_BASE, GPIO_PIN_0 |GPIO_PIN_1|GPIO_PIN_2,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	
    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_0 |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	    
    GPIOPadConfigSet(GPIO_PORTQ_BASE, GPIO_PIN_0 |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);	
    GPIOPadConfigSet(GPIO_PORTK_BASE, GPIO_PIN_6 |GPIO_PIN_7,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);    
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);        
}

//*****************************************************************************
//
//! 给DAC904写入值.
//!
//! This function must be called during application initialization to
//! configure the GPIO pins to which the pushbuttons are attached.  It enables
//! the port used by the buttons and configures each button GPIO as an input
//! with a weak pull-up.
//!
//! \return None.
//
//*****************************************************************************
void DACWrite(uint16_t value)
{
    CLK_SET;
    
    if(value&0x2000) {DATA14_SET;}
    else                       {DATA14_CLR;}
    value<<=1;
    if(value&0x2000) {DATA13_SET;}
    else                       {DATA13_CLR;}
    value<<=1;    
    if(value&0x2000) {DATA12_SET;}
    else                       {DATA12_CLR;}
    value<<=1;    
    if(value&0x2000) {DATA11_SET;}
    else                       {DATA11_CLR;}
    value<<=1;   
    if(value&0x2000) {DATA10_SET;}
    else                       {DATA10_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA9_SET;}
    else                       {DATA9_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA8_SET;}
    else                       {DATA8_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA7_SET;}
    else                       {DATA7_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA6_SET;}
    else                       {DATA6_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA5_SET;}
    else                       {DATA5_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA4_SET;}
    else                       {DATA4_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA3_SET;}
    else                       {DATA3_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA2_SET;}
    else                       {DATA2_CLR;}
    value<<=1; 
    if(value&0x2000) {DATA1_SET;}
    else                       {DATA1_CLR;}
    
    CLK_CLR;
}
//*****************************************************************************
//
//! 给DAC904生成波形.
//!
//! This function must be called during application initialization to
//! configure the GPIO pins to which the pushbuttons are attached.  It enables
//! the port used by the buttons and configures each button GPIO as an input
//! with a weak pull-up.
//!
//! \return None.
//
//*****************************************************************************
void DACWaveOut(void)
{
    DACWrite(Wave_Value[i++]);
    UARTprintf("%d\n",i);
}






