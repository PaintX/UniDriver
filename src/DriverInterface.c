///============================================================================
//
// PROJET       : PORTABLES 2014
// MODULE       : Board.c
// DESCRIPTION  : Configuration de la carte
//
//=============================================================================


//=============================================================================
//--- DECLARATIONS
//=============================================================================

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#include "DriverInterface.h"

//-----------------------------------------------------------------------------
// Constantes : defines et enums
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Variables et Fonctions Privees
//-----------------------------------------------------------------------------



/* Holds the list of peripherals that are available to the FreeRTOS+IO
interface.  boardAVAILABLE_DEVICED_LIST is defined in FreeRTOS_IO_BSP.h, and is
specific to a hardware platform. */
static int xNumberOfPeripherals;
static Peripheral_Control_t xAvailablePeripherals[MAX_DRIVER_SUPPORTED];

//=============================================================================
//--- DEFINITIONS
//=============================================================================

//-----------------------------------------------------------------------------
// FONCTION    :  DRIVER_Add
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
bool    DRIVER_Add(Peripheral_Control_t * d)
{
    bool ret = false;
    int i;
    for ( i = 0 ; i < MAX_DRIVER_SUPPORTED ; i++)
    {
        if ( xAvailablePeripherals[i].pxDevice.pcPath == NULL )
        {
            xAvailablePeripherals[i].pxDevice.pcPath = d->pxDevice.pcPath;
            xAvailablePeripherals[i].pxDevice.pvBaseAddress = d->pxDevice.pvBaseAddress;
            xAvailablePeripherals[i].cPeripheralNumber = i;
            if ( d->write != NULL )
               xAvailablePeripherals[i].write = d->write;
            if ( d->read != NULL )
               xAvailablePeripherals[i].read = d->read;
            if ( d->ioctl != NULL )
               xAvailablePeripherals[i].ioctl = d->ioctl;

            xNumberOfPeripherals++;
            ret = true;
            break;
        }
    }
    return ret;
}


//-----------------------------------------------------------------------------
// FONCTION    :  DRIVER_LoadAll
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
void    DRIVER_LoadAll ( void )
{
    int i;
    //-- initialisation
    xNumberOfPeripherals = 0;
    for ( i = 0 ; i < MAX_DRIVER_SUPPORTED ; i++)
    {
        xAvailablePeripherals[i].pxDevice.pcPath = NULL;
        xAvailablePeripherals[i].cPeripheralNumber = 0;
    }
#ifndef BOOTSTRAP
    //-- chargement des drivers inclu dans le bootloader
   Peripheral_Control_t * p = 0x0801F000;
   for ( i = 0 ; i < MAX_DRIVER_SUPPORTED ; i++)
   {
      if ( p->pxDevice.pcPath == NULL )
         break;
      DRIVER_Add(p);
      p++;
   }

#else
    //-- chargement des drivers de l'application
    CLOCK_LoadDriver();
    GPIO_LoadDriver();
#endif
}



/* See the function prototype definition for documentation information. */
Peripheral_Descriptor_t DRIVER_open( const char *pcPath, const uint32_t ulFlags )
{
   int xIndex;

   Peripheral_Control_t *pxPeripheralControl = NULL;


   for( xIndex = 0; xIndex < xNumberOfPeripherals; xIndex++ )
   {
      if( strcmp( ( const char * const ) pcPath, ( const char * const ) xAvailablePeripherals[ xIndex ].pxDevice.pcPath ) == 0 )
      {
         /* pcPath is a valid path, search no further. */
         pxPeripheralControl = &xAvailablePeripherals[ xIndex ];
         break;
      }
   }

   return ( Peripheral_Descriptor_t ) pxPeripheralControl;
}




