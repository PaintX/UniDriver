//=============================================================================
//
// PROJET       : PORTABLES 2014
// HEADER       : Board.h
//
//=============================================================================
#ifndef _CLOCK_H_
#define _CLOCK_H_
//=============================================================================
//--- DECLARATIONS
//=============================================================================

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#include <stdint.h>
#include "stm32f4xx.h"
#include "DriverInterface.h"

//-----------------------------------------------------------------------------
// Constantes : defines et enums
//-----------------------------------------------------------------------------
#define         SYSCFG_CLK      (uint32_t)0x00000001

#define UNUSED(x) ((void)(x))
#define __HAL_RCC_GPIOA_CLK_ENABLE()    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN)
#define __HAL_RCC_GPIOD_CLK_ENABLE()	do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                        UNUSED(tmpreg); \
                                        } while(0)

#define __HAL_RCC_SYSCFG_CLK_ENABLE()   do { \
                                        __IO uint32_t tmpreg; \
                                        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);\
                                        UNUSED(tmpreg); \
					} while(0)





#define __HAL_RCC_SYSCFG_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_SYSCFGEN))

//-----------------------------------------------------------------------------
// Variables et Fonctions partagees
//-----------------------------------------------------------------------------

//---------- Variables ----------


//---------- Fonctions ----------
void HAL_CLOCK_Config(uint32_t ulRequest,bool enable);

#endif
