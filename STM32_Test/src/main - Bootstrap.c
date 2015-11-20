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
#include "Board.h"


typedef  void (*pFunction)(void);


Peripheral_Descriptor_t gpio;

int main(void)
{
   pFunction   Jump_To_Application;
   uint32_t    JumpAddress;

   //--- Jump to user application
   JumpAddress = *(__IO uint32_t*) (0x08020000 + 4);
   Jump_To_Application = (pFunction) JumpAddress;
 //  Jump_To_Application();
   DRIVER_LoadAll();

   GPIO_InitTypeDef gpioConf;

   BOARD_ConfAll();

 //  DRIVER_LoadAll();

   gpio = DRIVER_open("GPIOD",0);

   gpioConf.Pin = GPIO_PIN_15;
   gpioConf.Mode = GPIO_MODE_OUTPUT_PP ;
   gpioConf.Pull = GPIO_NOPULL;

   DRIVER_ioctl(gpio,GPIO_SET_CONFIG,&gpioConf);

   while ( 1 )
   {
      DRIVER_ioctl(gpio,GPIO_SET_PIN,GPIO_PIN_15);
      DRIVER_ioctl(gpio,GPIO_CLEAR_PIN,GPIO_PIN_15);
   }


    return 0;
}
