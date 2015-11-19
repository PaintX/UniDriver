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

    //-- chargement des drivers inclu dans le bootloader

    //-- chargement des drivers de l'application
    CLOCK_LoadDriver();
    GPIO_LoadDriver();
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
/*-----------------------------------------------------------*/
#if 0
/* See the function prototype definition for documentation information. */
portBASE_TYPE FreeRTOS_ioctl( Peripheral_Descriptor_t const xPeripheral, uint32_t ulRequest, void *pvValue )
{
Peripheral_Control_t *pxPeripheralControl = ( Peripheral_Control_t * ) xPeripheral;
portBASE_TYPE xReturn = pdFAIL, xCommandIsDeviceSpecific = pdFALSE;

	configASSERT( pxPeripheralControl );

	/* Handle any non peripheral specific commands here. */
	switch( ulRequest )
	{
		case ioctlUSE_ZERO_COPY_TX	:

			#if ioconfigUSE_ZERO_COPY_TX == 1
			{
				/* The peripheral is going to use a	Zero_Copy_Tx_State_t
				structure for transmission.  This allows characters to be
				transmitted directly from the buffer supplied to the
				FreeRTOS_write() function. */
				xReturn = xIOUtilsConfigureZeroCopyTx( pxPeripheralControl );

				/* Zero copy Tx buffers can only be used when interrupts are
				also used.  Enabling interrupts is a peripheral specific
				operation. */
				ulRequest = ioctlUSE_INTERRUPTS;
				pvValue = ( void * ) pdTRUE;
				xCommandIsDeviceSpecific = pdTRUE;
			}
			#endif /* ioconfigUSE_ZERO_COPY_TX */
			break;


		case ioctlUSE_CIRCULAR_BUFFER_RX :

			#if ioconfigUSE_CIRCULAR_BUFFER_RX == 1
			{
				/* The peripheral is going to use a Circular_Buffer_Rx_State_t
				structure for reception.  This places received characters into
				a buffer, then allows a pointer to the buffer to be returned
				directly in a read function. */
				xReturn = xIOUtilsConfigureCircularBufferRx( pxPeripheralControl, ( portBASE_TYPE ) pvValue );

				/* Circular buffer Rx can only be used when interrupts are also
				used.  Enabling interrupts is a peripheral specific operation. */
				ulRequest = ioctlUSE_INTERRUPTS;
				pvValue = ( void * ) pdTRUE;
				xCommandIsDeviceSpecific = pdTRUE;
			}
			#endif /* ioconfigUSE_CIRCULAR_BUFFER_RX */
			break;


		case ioctlUSE_CHARACTER_QUEUE_TX	:
		case ioctlUSE_CHARACTER_QUEUE_RX	:

			#if ( ioconfigUSE_TX_CHAR_QUEUE == 1 ) || ( ioconfigUSE_RX_CHAR_QUEUE == 1 )
			{
				/* The peripheral is going to use a character by character
				queue to transmit or receive data.  This is an easy and
				convenient method, but inefficient for systems that have a
				high throughput. */
				xReturn = xIOUtilsConfigureTransferQueue( pxPeripheralControl, ulRequest, ( unsigned portBASE_TYPE ) pvValue );

				/* Character queues can only be used when interrupts are also
				used.  Enabling interrupts is a device specific operation. */
				ulRequest = ioctlUSE_INTERRUPTS;
				pvValue = ( void * ) pdTRUE;
				xCommandIsDeviceSpecific = pdTRUE;
			}
			#endif /* ( ioconfigUSE_TX_CHAR_QUEUE == 1 ) || ( ioconfigUSE_RX_CHAR_QUEUE == 1 ) */
			break;


		case ioctlSET_TX_TIMEOUT 	:

			if( pxPeripheralControl->pxTxControl->ucType == ioctlUSE_CHARACTER_QUEUE_TX )
			{
				#if ( ioconfigUSE_TX_CHAR_QUEUE == 1 )
				{
					xIOUtilsSetTxQueueTimeout( pxPeripheralControl, ( portTickType ) pvValue );
					xReturn = pdPASS;
				}
				#endif /* ( ioconfigUSE_TX_CHAR_QUEUE == 1 ) */
			}
			else
			{
				/* There is nothing to do here as xReturn is already pdFAIL. */
			}
			break;


		case ioctlSET_RX_TIMEOUT	:

			if( pxPeripheralControl->pxRxControl->ucType == ioctlUSE_CIRCULAR_BUFFER_RX )
			{
				#if ioconfigUSE_CIRCULAR_BUFFER_RX == 1
				{
					vIOUtilsSetCircularBufferTimeout( pxPeripheralControl, ( portTickType ) pvValue );
					xReturn = pdPASS;
				}
				#endif /* ioctlUSE_CIRCUAL_BUFFER_RX */
			}
			else if( pxPeripheralControl->pxRxControl->ucType == ioctlUSE_CHARACTER_QUEUE_RX )
			{
				#if ioconfigUSE_RX_CHAR_QUEUE == 1
				{
					vIOUtilsSetRxQueueTimeout( pxPeripheralControl, ( portTickType ) pvValue );
					xReturn = pdPASS;
				}
				#endif /* ioconfigUSE_RX_CHAR_QUEUE */
			}
			else
			{
				/* Nothing to do here as xReturn is already pdFAIL. */
			}
			break;


		/* These two cases are intentionally together as their functionality is
		very similar. */
		case ioctlOBTAIN_WRITE_MUTEX :
		case ioctlWAIT_PREVIOUS_WRITE_COMPLETE :

			xReturn = pdTRUE;

			if( pxPeripheralControl->pxTxControl->ucType == ioctlUSE_ZERO_COPY_TX )
			{
				#if ioconfigUSE_ZERO_COPY_TX == 1
				{
					/* The write mutex should be obtained prior to attempting a
					zero copy Tx operation.  Obtaining the write mutex also shows
					no transmissions are currently in progress, so provides a
					useful method of waiting until a write has completed. */
					xReturn = xIOUtilsGetZeroCopyWriteMutex( pxPeripheralControl, ulRequest, ( portTickType ) pvValue );
				}
				#endif /* #if ioconfigUSE_ZERO_COPY_TX == 1 */
			}
			else if( pxPeripheralControl->pxTxControl->ucType == ioctlUSE_CHARACTER_QUEUE_TX )
			{
				#if ioconfigUSE_RX_CHAR_QUEUE == 1
				{
					xReturn = xIOUtilsWaitTxQueueEmpty( pxPeripheralControl, ( portTickType ) pvValue );
				}
				#endif /* ioconfigUSE_RX_CHAR_QUEUE */
			}
			else
			{
				/* Nothing to do here as xReturn is already set to pdTRUE.  It
				has to be set to pdTRUE before this if/else construct in case
				the configuration is such that code is conditionally compiled
				out (which would be an error anyway. */
			}
			break;


		case ioctlRELEASE_WRITE_MUTEX :

			xReturn = pdTRUE;

			#if ioconfigUSE_ZERO_COPY_TX == 1
			{
				if( pxPeripheralControl->pxTxControl->ucType == ioctlUSE_ZERO_COPY_TX )
				{
						/* Give back the write mutex, if it is held. */
						xReturn = xIOUtilsReleaseZeroCopyWriteMutex( pxPeripheralControl );
				}
			}
			#endif /* ioconfigUSE_ZERO_COPY_TX */
			break;


		case ioctlCLEAR_RX_BUFFER :

			if( pxPeripheralControl->pxRxControl->ucType == ioctlUSE_CIRCULAR_BUFFER_RX )
			{
				#if ioconfigUSE_CIRCULAR_BUFFER_RX == 1
				{
					vIOUtilsClearRxCircularBuffer( pxPeripheralControl );
					xReturn = pdPASS;
				}
				#endif /* ioconfigUSE_CIRCULAR_BUFFER_RX */
			}
			else if( pxPeripheralControl->pxRxControl->ucType == ioctlUSE_CHARACTER_QUEUE_RX )
			{
				#if ioconfigUSE_RX_CHAR_QUEUE == 1
				{
					xIOUtilsClearRxCharQueue( pxPeripheralControl );
					xReturn = pdPASS;
				}
				#endif /* ioconfigUSE_RX_CHAR_QUEUE */
			}
			else
			{
				/* Nothing to do here as xReturn is already set to pdFAIL; */
			}
			break;


		default :

			xCommandIsDeviceSpecific = pdTRUE;
			xReturn = pdPASS;
			break;
	}

	/* Handle any device specific commands. */
	if( ( xCommandIsDeviceSpecific == pdTRUE ) && ( xReturn != pdFAIL ) )
	{
		xReturn = pxPeripheralControl->ioctl( pxPeripheralControl, ulRequest, pvValue );
	}

	return xReturn;
}
/*-----------------------------------------------------------*/
#endif








