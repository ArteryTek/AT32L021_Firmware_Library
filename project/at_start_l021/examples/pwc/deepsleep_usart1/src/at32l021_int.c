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


/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_PWC_deepsleep_usart1
  * @{
  */


uint16_t usart1_index = 0;

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
  * @brief  this function handles the usatt interrupt request.
  * @param  none
  * @retval none
  */
void USART1_IRQHandler(void)
{
  if(usart_interrupt_flag_get(USART1, USART_RDBF_FLAG) != RESET)
  {
    /* clear rdbf flag */
    usart1_index = usart_data_receive(USART1);

    /* toggle led */
    at32_led_toggle(LED4);
  }

  if(usart_interrupt_flag_get(USART1, USART_LPWUF_FLAG) != RESET)
  {
    usart_flag_clear(USART1, USART_LPWUF_FLAG);
  }

  if(exint_interrupt_flag_get(EXINT_LINE_25) != RESET)
  {
    exint_flag_clear(EXINT_LINE_25);
  }
}


/**
  * @}
  */

/**
  * @}
  */
