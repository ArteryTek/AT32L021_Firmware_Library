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

/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_TMR_oc_low
  * @{
  */

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
  if(tmr_interrupt_flag_get(TMR3, TMR_C1_FLAG) != RESET)
  {
    /* clear tmr3 channel1 interrupt pending bit */
    tmr_flag_clear(TMR3, TMR_C1_FLAG);

    /* pa.00 turnoff after 1000 ms */
    gpio_bits_set(GPIOA, GPIO_PINS_0);
  }
  else if(tmr_interrupt_flag_get(TMR3, TMR_C2_FLAG) != RESET)
  {
    /* clear tmr3 channel2 interrupt pending bit */
    tmr_flag_clear(TMR3, TMR_C2_FLAG);

    /* pa.01 turnoff after 500 ms */
    gpio_bits_set(GPIOA, GPIO_PINS_1);
  }
  else if(tmr_interrupt_flag_get(TMR3, TMR_C3_FLAG) != RESET)
  {
    /* clear tmr2 channel3 interrupt pending bit */
    tmr_flag_clear(TMR3, TMR_C3_FLAG);

    /* pa.02 turnoff after 250 ms */
    gpio_bits_set(GPIOA, GPIO_PINS_2);
  }
  else
  {
    /* clear tmr3 channel4 interrupt pending bit */
    tmr_flag_clear(TMR3, TMR_C4_FLAG);

    /* pa.03 turnoff after 125 ms */
    gpio_bits_set(GPIOA, GPIO_PINS_3);
  }
}

/**
  * @}
  */

/**
  * @}
  */