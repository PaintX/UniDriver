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
#include "stm32f4xx_conf.h"
#include "FreeRTOS_DriverInterface.h"

size_t GPIO_write( Peripheral_Descriptor_t const pxPeripheral, const void *pvBuffer, const size_t xBytes )
{

   return xBytes;
}

void GPIO_LoadDriver(void)
{
   Peripheral_Control_t dev;

   dev.pxDevice.pcPath = "GPIO0";
   dev.write = GPIO_write;

   DRIVER_Add(&dev);
}



Peripheral_Descriptor_t gpio;

int main(void)
{
   DRIVER_LoadAll();

   GPIO_LoadDriver();

   gpio = DRIVER_open("GPIO0",0);

   return 0;
}
