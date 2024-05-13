/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
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

#include "at32l021_board.h"
#include "at32l021_clock.h"

/** @addtogroup AT32L021_periph_examples
  * @{
  */

/** @addtogroup 021_USART_modbus_receiver_timeout USART_modbus_receiver_timeout
  * @{
  */

#define USART1_BUFFER_SIZE            (128)

uint8_t usart1_rx_buffer[USART1_BUFFER_SIZE];
uint8_t usart1_rx_counter = 0x00;
uint8_t rx_complete_flag = 0;
uint8_t text_info[] = "usart example: modbus_receiver_timeout\r\n";

/**
  * @brief  config usart1
  * @param  none
  * @retval none
  */
void usart_configuration(void)
{
  gpio_init_type gpio_init_struct;

  /* enable the usart1 and gpio clock */
  crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  gpio_default_para_init(&gpio_init_struct);

  /* configure the usart1 tx/rx pin */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_9 | GPIO_PINS_10;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOA, &gpio_init_struct);

  /* config usart1 iomux */
  gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE9, GPIO_MUX_1);
  gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE10, GPIO_MUX_1);

  crm_usart_clock_select(CRM_USART1, CRM_USART_CLOCK_SOURCE_HICK48);
  
  /* configure usart1 param */
  usart_init(USART1, 9600, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_parity_selection_config(USART1, USART_PARITY_NONE);
  usart_transmitter_enable(USART1, TRUE);
  usart_receiver_enable(USART1, TRUE);
  
  usart_receiver_timeout_detection_enable(USART1, TRUE);
  usart_receiver_timeout_value_set(USART1, 4);
  
  nvic_irq_enable(USART1_IRQn, 0, 0);
  usart_interrupt_enable(USART1, USART_RTOD_INT, TRUE);
  
  usart_enable(USART1, TRUE);
  
  /* polling usart initialisation */
  while((!(usart_flag_get(USART1, USART_TXON_FLAG))) || (!(usart_flag_get(USART1, USART_RXON_FLAG))))
  { 
  }
}

/**
  * @brief  print info function.
  * @param  none
  * @retval none
  */
void print_info(void)
{
  uint32_t index = 0;
  
  /* send characters one per one, until last char to be sent */
  for (index = 0; index < sizeof(text_info); index++)
  {
    while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
    usart_data_transmit(USART1, text_info[index]);
  }

  /* wait for tdc flag to be raised for last char */
  while(usart_flag_get(USART1, USART_TDC_FLAG) == RESET);
}

/**
  * @brief  print echo function.
  * @param  none
  * @retval none
  */
void print_echo(void)
{
  uint32_t index = 0;
  
  /* send characters one per one, until last char to be sent */
  for (index = 0; index < usart1_rx_counter; index++)
  {
    while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
    usart_data_transmit(USART1, usart1_rx_buffer[index]);
  }
  usart1_rx_counter = 0;

  /* wait for tdc flag to be raised for last char */
  while(usart_flag_get(USART1, USART_TDC_FLAG) == RESET);
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  system_clock_config();
  at32_board_init();

  usart_configuration();

  print_info();
  usart_interrupt_enable(USART1, USART_RDBF_INT, TRUE);
  
  while(1)
  {
    if(rx_complete_flag == 1)
    {
      usart_interrupt_enable(USART1, USART_RDBF_INT, FALSE);
      rx_complete_flag = 0;
      at32_led_on(LED2);
      print_echo();
      at32_led_off(LED2);
      usart_interrupt_enable(USART1, USART_RDBF_INT, TRUE);
    }
  }
}

/**
  * @}
  */

/**
  * @}
  */
