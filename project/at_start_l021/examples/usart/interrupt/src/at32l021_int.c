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

extern uint8_t usart2_tx_buffer[];
extern uint8_t usart1_tx_buffer[];
extern uint8_t usart2_rx_buffer[];
extern uint8_t usart1_rx_buffer[];
extern uint8_t usart2_tx_counter;
extern uint8_t usart1_tx_counter;
extern uint8_t usart2_rx_counter;
extern uint8_t usart1_rx_counter;
extern uint8_t usart2_tx_buffer_size;
extern uint8_t usart1_tx_buffer_size;

/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_USART_interrupt
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
  * @brief  this function handles usart2 handler.
  * @param  none
  * @retval none
  */
void USART2_IRQHandler(void)
{
  if(usart_interrupt_flag_get(USART2, USART_RDBF_FLAG) != RESET)
  {
    /* read one byte from the receive data register */
    usart2_rx_buffer[usart2_rx_counter++] = usart_data_receive(USART2);

    if(usart2_rx_counter == usart1_tx_buffer_size)
    {
      /* disable the usart2 receive interrupt */
      usart_interrupt_enable(USART2, USART_RDBF_INT, FALSE);
    }
  }

  if(usart_interrupt_flag_get(USART2, USART_TDBE_FLAG) != RESET)
  {
    /* write one byte to the transmit data register */
    usart_data_transmit(USART2, usart2_tx_buffer[usart2_tx_counter++]);

    if(usart2_tx_counter == usart2_tx_buffer_size)
    {
      /* disable the usart2 transmit interrupt */
      usart_interrupt_enable(USART2, USART_TDBE_INT, FALSE);
    }
  }
}

/**
  * @brief  this function handles usart1 handler.
  * @param  none
  * @retval none
  */
void USART1_IRQHandler(void)
{
  if(usart_interrupt_flag_get(USART1, USART_RDBF_FLAG) != RESET)
  {
    /* read one byte from the receive data register */
    usart1_rx_buffer[usart1_rx_counter++] = usart_data_receive(USART1);

    if(usart1_rx_counter == usart2_tx_buffer_size)
    {
      /* disable the usart1 receive interrupt */
      usart_interrupt_enable(USART1, USART_RDBF_INT, FALSE);
    }
  }

  if(usart_interrupt_flag_get(USART1, USART_TDBE_FLAG) != RESET)
  {
    /* write one byte to the transmit data register */
    usart_data_transmit(USART1, usart1_tx_buffer[usart1_tx_counter++]);

    if(usart1_tx_counter == usart1_tx_buffer_size)
    {
      /* disable the usart1 transmit interrupt */
      usart_interrupt_enable(USART1, USART_TDBE_INT, FALSE);
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */