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
#define         SYSCFG_CLK                   (uint32_t)( 0x00000001 << 0 )
#define         RCC_OSCILLATORTYPE_HSE       (uint32_t)( 0x00000001 << 1 )
#define         RCC_OSCILLATORTYPE_HSI       (uint32_t)( 0x00000001 << 2 )
#define         RCC_OSCILLATORTYPE_LSI       (uint32_t)( 0x00000001 << 3 )
#define         RCC_OSCILLATORTYPE_LSE       (uint32_t)( 0x00000001 << 4 )

/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                      ((uint8_t)0x00)
#define RCC_HSE_ON                       ((uint8_t)0x01)
#define RCC_HSE_BYPASS                   ((uint8_t)0x05)

/** @defgroup RCC_Flag Flags
  *        Elements values convention: 0XXYYYYYb
  *           - YYYYY  : Flag position in the register
  *           - 0XX  : Register index
  *                 - 01: CR register
  *                 - 10: BDCR register
  *                 - 11: CSR register
  * @{
  */
/* Flags in the CR register */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x21)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x39)
#define RCC_FLAG_PLLI2SRDY               ((uint8_t)0x3B)


/** @brief  Check RCC flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg RCC_FLAG_HSIRDY: HSI oscillator clock ready.
  *            @arg RCC_FLAG_HSERDY: HSE oscillator clock ready.
  *            @arg RCC_FLAG_PLLRDY: Main PLL clock ready.
  *            @arg RCC_FLAG_PLLI2SRDY: PLLI2S clock ready.
  *            @arg RCC_FLAG_LSERDY: LSE oscillator clock ready.
  *            @arg RCC_FLAG_LSIRDY: LSI oscillator clock ready.
  *            @arg RCC_FLAG_BORRST: POR/PDR or BOR reset.
  *            @arg RCC_FLAG_PINRST: Pin reset.
  *            @arg RCC_FLAG_PORRST: POR/PDR reset.
  *            @arg RCC_FLAG_SFTRST: Software reset.
  *            @arg RCC_FLAG_IWDGRST: Independent Watchdog reset.
  *            @arg RCC_FLAG_WWDGRST: Window Watchdog reset.
  *            @arg RCC_FLAG_LPWRRST: Low Power reset.
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define RCC_FLAG_MASK  ((uint8_t)0x1F)
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5) == 1)? RCC->CR :((((__FLAG__) >> 5) == 2) ? RCC->BDCR :((((__FLAG__) >> 5) == 3)? RCC->CSR :RCC->CIR))) & ((uint32_t)1 << ((__FLAG__) & RCC_FLAG_MASK)))!= 0)? 1 : 0)


/* CR register byte 3 (Bits[23:16]) base address */
#define RCC_CR_BYTE2_ADDRESS       ((uint32_t)0x40023802)

#define RCC_OFFSET                 (RCC_BASE - PERIPH_BASE)
/* Alias word address of HSION bit */
#define RCC_CR_OFFSET              (RCC_OFFSET + 0x00)
#define RCC_HSION_BIT_NUMBER       0x00
#define RCC_CR_HSION_BB            (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32) + (RCC_HSION_BIT_NUMBER * 4))



#define __HAL_RCC_HSE_CONFIG(__STATE__) (*(__IO uint8_t *) RCC_CR_BYTE2_ADDRESS = (__STATE__))

#define __HAL_RCC_HSI_ENABLE() (*(__IO uint32_t *) RCC_CR_HSION_BB = ENABLE)
#define __HAL_RCC_HSI_DISABLE() (*(__IO uint32_t *) RCC_CR_HSION_BB = DISABLE)

#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICalibrationValue__) (MODIFY_REG(RCC->CR,\
        RCC_CR_HSITRIM, (uint32_t)(__HSICalibrationValue__) << POSITION_VAL(RCC_CR_HSITRIM)))



#define __HAL_RCC_GPIOA_CLK_ENABLE()    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN)
#define __HAL_RCC_GPIOB_CLK_ENABLE()    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN)
#define __HAL_RCC_GPIOC_CLK_ENABLE()    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN)
#define __HAL_RCC_GPIOD_CLK_ENABLE()    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN)
#define __HAL_RCC_GPIOE_CLK_ENABLE()	 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN)
#define __HAL_RCC_GPIOF_CLK_ENABLE()    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN)
#define __HAL_RCC_GPIOG_CLK_ENABLE()    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN)
#define __HAL_RCC_GPIOH_CLK_ENABLE()	 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN)
#define __HAL_RCC_GPIOI_CLK_ENABLE()	 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN)

#define __HAL_RCC_SYSCFG_CLK_ENABLE()   SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN)


#define __HAL_RCC_GET_SYSCLK_SOURCE()     ((uint32_t)(RCC->CFGR & RCC_CFGR_SWS))


#define __HAL_RCC_SYSCFG_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_SYSCFGEN))

#define __HAL_RCC_PWR_CLK_ENABLE()        SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN)
#define __HAL_RCC_PWR_CLK_DISABLE()       (RCC->APB1ENR &= ~(RCC_APB1ENR_PWREN))


#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__) MODIFY_REG(PWR->CR, PWR_CR_VOS, (__REGULATOR__))


#define  __HAL_RCC_DRIVER()               { .pxDevice.pcPath = "RCC", .write = NULL, .read = NULL, .ioctl = _Ioctl, }


//-----------------------------------------------------------------------------
// Variables et Fonctions partagees
//-----------------------------------------------------------------------------

//---------- Variables ----------


//---------- Fonctions ----------
void HAL_CLOCK_Config(uint32_t ulRequest,bool enable);

#endif
