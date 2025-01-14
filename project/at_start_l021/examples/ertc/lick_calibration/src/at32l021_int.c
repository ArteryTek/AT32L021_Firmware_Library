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
#include "at32l021_board.h"
#include "stdio.h"

/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_ERTC_lick_calibration
  * @{
  */

extern __IO uint32_t period_value;
extern __IO uint32_t capture_number;
uint16_t tmp_c4[2] = {0, 0};

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
  * @brief  this function handles tmr14 global interrupt request.
  * @param  none
  * @retval none
  */
void TMR14_GLOBAL_IRQHandler(void)
{
  if (tmr_interrupt_flag_get(TMR14, TMR_C1_FLAG) != RESET)
  {
    /* get the input capture value */
    tmp_c4[capture_number++] = tmr_channel_value_get(TMR14, TMR_SELECT_CHANNEL_1);

    /* clear c1 interrupt pending bit */
    tmr_flag_clear(TMR14, TMR_C1_FLAG);

    if (capture_number >= 2)
    {
      /* compute the period length */
      period_value = (uint16_t)(0xFFFF - tmp_c4[0] + tmp_c4[1] + 1);
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */
