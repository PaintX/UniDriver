/*
 * FreeRTOS+IO V1.0.1 (C) 2012 Real Time Engineers ltd.
 *
 * FreeRTOS+IO is an add-on component to FreeRTOS.  It is not, in itself, part
 * of the FreeRTOS kernel.  FreeRTOS+IO is licensed separately from FreeRTOS,
 * and uses a different license to FreeRTOS.  FreeRTOS+IO uses a dual license
 * model, information on which is provided below:
 *
 * - Open source licensing -
 * FreeRTOS+IO is a free download and may be used, modified and distributed
 * without charge provided the user adheres to version two of the GNU General
 * Public license (GPL) and does not remove the copyright notice or this text.
 * The GPL V2 text is available on the gnu.org web site, and on the following
 * URL: http://www.FreeRTOS.org/gpl-2.0.txt
 *
 * - Commercial licensing -
 * Businesses and individuals who wish to incorporate FreeRTOS+IO into
 * proprietary software for redistribution in any form must first obtain a low
 * cost commercial license - and in-so-doing support the maintenance, support
 * and further development of the FreeRTOS+IO product.  Commercial licenses can
 * be obtained from http://shop.freertos.org and do not require any source files
 * to be changed.
 *
 * FreeRTOS+IO is distributed in the hope that it will be useful.  You cannot
 * use FreeRTOS+IO unless you agree that you use the software 'as is'.
 * FreeRTOS+IO is provided WITHOUT ANY WARRANTY; without even the implied
 * warranties of NON-INFRINGEMENT, MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. Real Time Engineers Ltd. disclaims all conditions and terms, be they
 * implied, expressed, or statutory.
 *
 * 1 tab == 4 spaces!
 *
 * http://www.FreeRTOS.org
 * http://www.FreeRTOS.org/FreeRTOS-Plus
 *
 */
#include "DriverInterface.h"

#include "gpio.h"

static size_t _Write( Peripheral_Descriptor_t const pxPeripheral, const void *pvBuffer, const size_t xBytes );
static size_t _Read( Peripheral_Descriptor_t const pxPeripheral, void * const pvBuffer, const size_t xBytes );
static int _Ioctl( Peripheral_Descriptor_t const pxPeripheral, uint32_t ulRequest, void *pvValue );

#ifdef BOOTSTRAP
 __attribute__((section (".DRIVER.clock")))
 #endif
 const Peripheral_Control_t gpioDriver[]  =
{
   __HAL_GPIOA_DRIVER(),
   __HAL_GPIOB_DRIVER(),
   __HAL_GPIOC_DRIVER(),
   __HAL_GPIOD_DRIVER(),
   __HAL_GPIOE_DRIVER(),
   __HAL_GPIOF_DRIVER(),
   __HAL_GPIOG_DRIVER(),
   __HAL_GPIOH_DRIVER(),
   __HAL_GPIOI_DRIVER(),
};

static size_t _Write( Peripheral_Descriptor_t const pxPeripheral, const void *pvBuffer, const size_t xBytes )
{
   return xBytes;
}

static size_t _Read( Peripheral_Descriptor_t const pxPeripheral, void * const pvBuffer, const size_t xBytes )
{
   return xBytes;
}

static int _Ioctl( Peripheral_Descriptor_t const pxPeripheral, uint32_t ulRequest, void *pvValue )
{
   Peripheral_Control_t * p = pxPeripheral;
   GPIO_TypeDef * GPIOx = (GPIO_TypeDef*)p->pxDevice.pvBaseAddress;

   switch ( ulRequest )
   {
      case ( GPIO_SET_CONFIG ):
      {
         GPIO_InitTypeDef *GPIO_Init = (GPIO_InitTypeDef *)pvValue;
         HAL_GPIO_Init(GPIOx,GPIO_Init);
         break;
      }
      case ( GPIO_SET_PIN ):
      {
         HAL_GPIO_WritePin(GPIOx,(uint16_t)pvValue,true);
         break;
      }
      case ( GPIO_CLEAR_PIN ):
      {
         HAL_GPIO_WritePin(GPIOx,(uint16_t)pvValue,false);
         break;
      }
   }

   return 0;
}

void GPIO_LoadDriver(void)
{
   uint16_t i;
   uint16_t nbPeriph = sizeof(gpioDriver)/sizeof(Peripheral_Control_t);

   for ( i = 0 ; i < nbPeriph ; i++ )
   {
      DRIVER_Add(&gpioDriver[i]);
   }
}




