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
#include "i2c_application.h"

extern i2c_handle_type hi2cx;

#define I2Cx_DMA_TX_IRQHandler           DMA1_Channel1_IRQHandler
#define I2Cx_DMA_RX_IRQHandler           DMA1_Channel3_2_IRQHandler
#define I2Cx_IRQHandler                  I2C2_IRQHandler

/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_I2C_eeprom
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
  * @brief  this function handles dma interrupt request.
  * @param  none
  * @retval none
  */
void I2Cx_DMA_TX_IRQHandler(void)
{
  i2c_dma_tx_irq_handler(&hi2cx);
}

/**
  * @brief  this function handles dma interrupt request.
  * @param  none
  * @retval none
  */
void I2Cx_DMA_RX_IRQHandler(void)
{
  i2c_dma_rx_irq_handler(&hi2cx);
}

/**
  * @brief  this function handles i2c event interrupt request.
  * @param  none
  * @retval none
  */
void I2Cx_IRQHandler(void)
{
  i2c_evt_irq_handler(&hi2cx);
  i2c_err_irq_handler(&hi2cx);
}

/**
  * @}
  */

/**
  * @}
  */
