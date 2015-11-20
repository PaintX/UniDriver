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
#include "clock.h"

//-----------------------------------------------------------------------------
// Constantes : defines et enums
//-----------------------------------------------------------------------------
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))
//-----------------------------------------------------------------------------
// Variables et Fonctions Privees
//-----------------------------------------------------------------------------

//=============================================================================
//--- DEFINITIONS
//=============================================================================


//-----------------------------------------------------------------------------
// FONCTION    :  HAL_Get_Nb_GPIO
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
void HAL_CLOCK_Config(uint32_t ulRequest,bool enable)
{
    switch ( ulRequest )
    {
       case ( RCC_OSCILLATORTYPE_HSE ):
       {
         /* Reset HSEON and HSEBYP bits before configuring the HSE --------------*/
         __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF);
          while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET){}

         if ( enable )
         {
            /* Set the new HSE configuration ---------------------------------------*/
            __HAL_RCC_HSE_CONFIG(RCC_HSE_ON);
            while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET){}
         }
          break;
       }
       case ( RCC_OSCILLATORTYPE_HSI ):
   {
      if ( enable )
      {
         /* Enable the Internal High Speed oscillator (HSI). */
         __HAL_RCC_HSI_ENABLE();
          while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET){}

         /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
         __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(0);

      }
      else
      {
         /* Disable the Internal High Speed oscillator (HSI). */
        __HAL_RCC_HSI_DISABLE();
         while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET){}
      }
      break;
   }
       case ( RCC_OSCILLATORTYPE_LSI ):
   {

   TODO(" a faire ");
      break;
   }
          case ( RCC_OSCILLATORTYPE_LSE ):
   {

   TODO(" a faire ");
      break;
   }
        case ( SYSCFG_CLK ):
        {
            if ( enable )
                __HAL_RCC_SYSCFG_CLK_ENABLE();
            else
                __HAL_RCC_SYSCFG_CLK_DISABLE();
            break;
        }
        default:
        {
            break;
        }
    }
}




