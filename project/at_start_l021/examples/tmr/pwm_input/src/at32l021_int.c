/**
  **************************************************************************
  * @file     at32l021_int.c
  * @brief    main interrupt service routines.
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* includes ------------------------------------------------------------------*/
#include "at32l021_int.h"

extern uint16_t duty_cycle;
extern uint32_t frequency;

/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_TMR_pwm_input
  * @{
  */

__IO uint16_t ic2value = 0;

/**
  * @brief  this function handles nmi exception.
  * @param  none
  * @retval none
  */
void NMI_Handler(void)
{
}

/**
  * @brief  this function handles hard fault exception.
  * @param  none
  * @retval none
  */
void HardFault_Handler(void)
{
  /* go to infinite loop when hard fault exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles svcall exception.
  * @param  none
  * @retval none
  */
void SVC_Handler(void)
{
}

/**
  * @brief  this function handles pendsv_handler exception.
  * @param  none
  * @retval none
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  this function handles systick handler.
  * @param  none
  * @retval none
  */
void SysTick_Handler(void)
{
}

/**
  * @brief  this function handles tmr3 global interrupt request.
  * @param  none
  * @retval none
  */
void TMR3_GLOBAL_IRQHandler(void)
{
  /* clear tmr3 channel interrupt pending bit */
  tmr_flag_clear(TMR3, TMR_C2_FLAG);

  /* get the input channel data value */
  ic2value = tmr_channel_value_get(TMR3, TMR_SELECT_CHANNEL_2);

  if(ic2value != 0)
  {
    /* duty cycle computation */
    duty_cycle = (tmr_channel_value_get(TMR3, TMR_SELECT_CHANNEL_1) * 100) / ic2value;

    /* frequency computation */
    frequency = system_core_clock / ic2value;
  }
  else
  {
    duty_cycle = 0;
    frequency = 0;
  }
}

/**
  * @}
  */

/**
  * @}
  */
