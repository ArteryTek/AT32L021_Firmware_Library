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

extern __IO uint16_t c1dt_val;
extern __IO uint16_t c2dt_val;
extern __IO uint16_t c3dt_val;
extern __IO uint16_t c4dt_val;

/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_TMR_pwm_output_simulate
  * @{
  */

uint16_t capture = 0;

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

void TMR3_GLOBAL_IRQHandler(void)
{
  if(tmr_interrupt_flag_get(TMR3, TMR_C1_FLAG) != RESET)
  {
    tmr_flag_clear(TMR3, TMR_C1_FLAG );

    gpio_bits_write(GPIOA, GPIO_PINS_0, (confirm_state)(1 - gpio_output_data_bit_read(GPIOA, GPIO_PINS_0)));
    capture = tmr_channel_value_get(TMR3, TMR_SELECT_CHANNEL_1);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, capture + c1dt_val);
  }
  else if(tmr_interrupt_flag_get(TMR3, TMR_C2_FLAG) != RESET)
  {
    tmr_flag_clear(TMR3, TMR_C2_FLAG);

    gpio_bits_write(GPIOA, GPIO_PINS_1, (confirm_state)(1 - gpio_output_data_bit_read(GPIOA, GPIO_PINS_1)));
    capture = tmr_channel_value_get(TMR3, TMR_SELECT_CHANNEL_2);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_2, capture + c2dt_val);
  }
  else if(tmr_interrupt_flag_get(TMR3, TMR_C3_FLAG) != RESET)
  {
    tmr_flag_clear(TMR3, TMR_C3_FLAG);

    gpio_bits_write(GPIOA, GPIO_PINS_2, (confirm_state)(1 - gpio_output_data_bit_read(GPIOA, GPIO_PINS_2)));
    capture = tmr_channel_value_get(TMR3, TMR_SELECT_CHANNEL_3);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_3, capture + c3dt_val);
  }
  else
  {
    tmr_flag_clear(TMR3, TMR_C4_FLAG);

    gpio_bits_write(GPIOA, GPIO_PINS_3, (confirm_state)(1 - gpio_output_data_bit_read(GPIOA, GPIO_PINS_3)));
    capture = tmr_channel_value_get(TMR3, TMR_SELECT_CHANNEL_4);
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_4, capture + c4dt_val);
  }
}

/**
  * @}
  */

/**
  * @}
  */
