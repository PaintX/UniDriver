/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "DriverInterface.h"






Peripheral_Descriptor_t gpio;

int main(void)
{
    GPIO_InitTypeDef gpioConf;
    DRIVER_LoadAll();

    uint16_t val16;

    gpio = DRIVER_open("GPIOD",0);

    gpioConf.Pin = GPIO_PIN_15;
    gpioConf.Mode = GPIO_MODE_OUTPUT_PP ;
    gpioConf.Pull = GPIO_NOPULL;


    FreeRTOS_ioctl(gpio,GPIO_SET_CONFIG,&gpioConf);

    FreeRTOS_ioctl(gpio,GPIO_SET_PIN,GPIO_PIN_9);

    return 0;
}
