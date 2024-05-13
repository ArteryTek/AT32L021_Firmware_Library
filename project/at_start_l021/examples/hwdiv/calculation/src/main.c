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

/** @addtogroup 021_HWDIV_calculation HWDIV_calculation
  * @{
  */

#define DELAY                            100
#define FAST                             1
#define SLOW                             4

uint8_t g_speed = FAST;

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  system_clock_config();

  at32_board_init();
  
  uart_print_init(115200);

  crm_periph_clock_enable(CRM_HWDIV_PERIPH_CLOCK, TRUE);

  /* signed operation */
  hwdiv_signed_operate_enable(TRUE);
  hwdiv_dividend_set(1000);
  /* divisor is -300 */
  hwdiv_divisor_set(0xfffffed4);
  printf("signed operation\r\n");
  printf("%d...%d\r\n", hwdiv_quotient_get(), hwdiv_remainder_get());
  
  /* unsigned operation */
  hwdiv_signed_operate_enable(FALSE);
  hwdiv_dividend_set(1000);
  /* divisor is 249 */
  hwdiv_divisor_set(249);
  printf("unsigned operation\r\n");
  printf("%d...%d\r\n", hwdiv_quotient_get(), hwdiv_remainder_get());
  
  while(1)
  {
    at32_led_toggle(LED2);
    delay_ms(g_speed * DELAY);
    at32_led_toggle(LED3);
    delay_ms(g_speed * DELAY);
    at32_led_toggle(LED4);
    delay_ms(g_speed * DELAY);
  }
}

/**
  * @}
  */

/**
  * @}
  */
