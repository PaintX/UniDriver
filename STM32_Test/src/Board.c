//=============================================================================
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
#include "Board.h"

//-----------------------------------------------------------------------------
// Constantes : defines et enums
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Variables et Fonctions Privees
//-----------------------------------------------------------------------------

//=============================================================================
//--- DEFINITIONS
//=============================================================================

//-----------------------------------------------------------------------------
// FONCTION    :  _Conf_RCC
//
// DESCRIPTION :  Configuration des Clocks
//-----------------------------------------------------------------------------
static void _Conf_RCC(bool status)
{
   Peripheral_Descriptor_t rcc;

   __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
   __HAL_FLASH_DATA_CACHE_ENABLE();
   __HAL_FLASH_PREFETCH_BUFFER_ENABLE();

   rcc = DRIVER_open("RCC",0);

   DRIVER_ioctl(rcc,RCC_OSCILLATORTYPE_HSI,true);
}

//-----------------------------------------------------------------------------
// FONCTION    :  _Conf_GPIO
//
// DESCRIPTION :  Configuration des ports entrees/sorties
//-----------------------------------------------------------------------------
static void _Conf_GPIO(void)
{


}

//-----------------------------------------------------------------------------
// FONCTION    :  _Conf_NVIC
//
// DESCRIPTION :  Configuration des Interruptions
//-----------------------------------------------------------------------------
static void _Conf_NVIC(void)
{
   __enable_irq();
}

//-----------------------------------------------------------------------------
// FONCTION    :  _Conf_EXTI
//
// DESCRIPTION :  Configuration des Interruptions Externes
//-----------------------------------------------------------------------------
static void _Conf_EXTI(void)
{

}

//-----------------------------------------------------------------------------
// FONCTION    :  _Conf_RTC
//
// DESCRIPTION :  Configuration de la RTC
//-----------------------------------------------------------------------------
static void _Conf_RTC(void)
{

}

//-----------------------------------------------------------------------------
// FONCTION    :  BOARD_ConfAll
//
// DESCRIPTION :  Configuration globale
//-----------------------------------------------------------------------------
void BOARD_ConfAll(void)
{
   //--- Configuration des Clocks
   _Conf_RCC(true);

   //--- Configuration des Interruptions Externes
   _Conf_EXTI();

   //--- Configuration des Interruptions
   _Conf_NVIC();

   //--- Configuration des E/S
   _Conf_GPIO();

   //--- Configuration du TimeKeeper
   _Conf_RTC();
}

//-----------------------------------------------------------------------------
// FONCTION    :  BOARD_ShutDown
//
// DESCRIPTION :  Eteindre la carte
//-----------------------------------------------------------------------------
void  BOARD_ShutDown(void)
{
   while (1);
}


