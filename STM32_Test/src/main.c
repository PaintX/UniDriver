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
   DRIVER_LoadAll();

   uint16_t val16;

   gpio = DRIVER_open("GPIO",0);


   FreeRTOS_write(gpio,val16,sizeof(val16));

   return 0;
}
