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

extern uint8_t spi1_tx_buffer[];
extern uint8_t spi2_rx_buffer[];
extern uint32_t tx_index;
extern uint32_t rx_index;

/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_SPI_halfduplex_interrupt
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
  * @brief  This function handles the spi1 interrupt request.
  * @param  None
  * @retval None
  */
 void SPI1_IRQHandler(void)
{
  if(spi_i2s_interrupt_flag_get(SPI1, SPI_I2S_TDBE_FLAG) != RESET)
  {
    spi_i2s_data_transmit(SPI1, spi1_tx_buffer[tx_index++]);
    if(tx_index == BUFFER_SIZE)
    {
      spi_i2s_interrupt_enable(SPI1, SPI_I2S_TDBE_INT, FALSE);
    }
  }
}

/**
  * @brief  This function handles the spi2 interrupt request.
  * @param  None
  * @retval None
  */
 void SPI2_IRQHandler(void)
{
  if(spi_i2s_interrupt_flag_get(SPI2, SPI_I2S_RDBF_FLAG) != RESET)
  {
    spi2_rx_buffer[rx_index++] = spi_i2s_data_receive(SPI2);
  }
}

/**
  * @}
  */

/**
  * @}
  */