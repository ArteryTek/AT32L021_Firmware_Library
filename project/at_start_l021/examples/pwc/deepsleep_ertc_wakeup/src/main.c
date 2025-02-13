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

/** @addtogroup 021_PWC_deepsleep_ertc_wakeup PWC_deepsleep_ertc_wakeup
  * @{
  */

/**
  * @brief  ertc configuration.
  * @param  none
  * @retval none
  */
void ertc_config(void)
{
  /* allow access to ertc */
  pwc_battery_powered_domain_access(TRUE);

  /* reset ertc domain */
  crm_battery_powered_domain_reset(TRUE);
  crm_battery_powered_domain_reset(FALSE);

  /* enable the lext osc */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_LEXT, TRUE);

  /* wait till lext is ready */
  while(crm_flag_get(CRM_LEXT_STABLE_FLAG) == RESET);

  /* select the ertc clock source */
  crm_ertc_clock_select(CRM_ERTC_CLOCK_LEXT);

  /* enable the ertc clock */
  crm_ertc_clock_enable(TRUE);

  /* deinitializes the ertc registers */
  ertc_reset();

  /* wait for ertc apb registers synchronisation */
  ertc_wait_update();

  /* configure the ertc data register and ertc prescaler
     ck_spre(1hz) = ertcclk(lext) /(ertc_clk_div_a + 1)*(ertc_clk_div_b + 1)*/
  ertc_divider_set(127, 255);

  /* configure the hour format is 24-hour format*/
  ertc_hour_mode_set(ERTC_HOUR_MODE_24);

  /* set the date: friday june 11th 2021 */
  ertc_date_set(21, 6, 11, 5);

  /* set the time to 06h 20mn 00s am */
  ertc_time_set(6, 20, 0, ERTC_AM);
}

/**
  * @brief  ertc wakeup timer configuration.
  * @param  none
  * @retval none
  */
void ertc_wakeup_timer_config(void)
{
  exint_init_type exint_init_struct;

  /* config the exint line of the ertc wakeup timer */
  exint_init_struct.line_select   = EXINT_LINE_20;
  exint_init_struct.line_enable   = TRUE;
  exint_init_struct.line_mode     = EXINT_LINE_INTERRUPT;
  exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
  exint_init(&exint_init_struct);

  /* set wakeup timer clock 1hz */
  ertc_wakeup_clock_set(ERTC_WAT_CLK_CK_B_16BITS);

  /* enable the ertc interrupt */
  nvic_irq_enable(ERTC_IRQn, 0, 0);

  /* enable ertc wakeup timer a interrupt */
  ertc_interrupt_enable(ERTC_WAT_INT, TRUE);
}

/**
  * @brief  ertc wakeup value set.
  * @param  wakeup_index : ertc wakeup value
  * @retval none
  */
void ertc_wakeup_value_set(uint32_t wakeup_index)
{
  /* enable the wakeup timer */
  ertc_wakeup_enable(FALSE);
  
  while(ertc_flag_get(ERTC_WATWF_FLAG) == RESET);
  
  /* set the wakeup time */
  ertc_wakeup_counter_set(wakeup_index - 1);
  
  /* enable the wakeup timer */
  ertc_wakeup_enable(TRUE);
}

/**
  * @brief  systemclock recover.
  * @param  none
  * @retval none
  */
void system_clock_recover(void)
{
  /* enable external high-speed crystal oscillator - hext */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

  /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) == RESET);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL);
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  __IO uint32_t systick_index = 0;

  /* enable pwc and bpr clock */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

  /* congfig the system clock */
  system_clock_config();

  /* init at start board */
  at32_board_init();

  /* turn on the led light */
  at32_led_on(LED2);
  at32_led_on(LED3);
  at32_led_on(LED4);
  
  delay_ms(300);

  /* config ertc */
  ertc_config();

  /* config the wakeup timer  */
  ertc_wakeup_timer_config();

  while(1)
  {
    /* turn off the led light */
    at32_led_off(LED2);

    ertc_wakeup_value_set(5);
    
    /* select system clock source as hick before ldo set */
    crm_sysclk_switch(CRM_SCLK_HICK);

    /* wait till hick is used as system clock source */
    while(crm_sysclk_switch_status_get() != CRM_SCLK_HICK)
    {
    }
    
    /* reduce ldo before enter deepsleep mode */
    pwc_ldo_output_voltage_set(PWC_LDO_OUTPUT_1V1);
    
    ertc_flag_clear(ERTC_WATF_FLAG);
	
	/* congfig the voltage regulator mode.only used with deep sleep mode */
    pwc_voltage_regulate_set(PWC_REGULATOR_LOW_POWER);

    /* enter deep sleep mode */
    pwc_deep_sleep_mode_enter(PWC_DEEP_SLEEP_ENTER_WFI);

    /* turn on the led light */
    at32_led_on(LED2);
    
    /* resume ldo before system clock source enhance */
    pwc_ldo_output_voltage_set(PWC_LDO_OUTPUT_1V2);

    /* wake up from deep sleep mode, congfig the system clock */
    system_clock_recover();

    delay_ms(500);
  }
}

/**
  * @}
  */

/**
  * @}
  */
