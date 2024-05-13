/**
  **************************************************************************
  * @file     readme.txt
  * @brief    readme
  **************************************************************************
  */

  this demo is based on the at-start board, in this demo, pa6, pa2 and pa8
  output pwm waveform. 
  the master tmrer tmr3 is running at 806 khz and the duty cycle is equal to 50%
  the tmr3 is running:
  - at (tmr1 frequency)/ (tmr3 period + 1) = 80 khz and a duty cycle
  equal to tmr3_c1dt/(tmr3_pr + 1) = 30%
  the tmr15 is running:
  - at (tmr1 frequency)/ (tmr15 period + 1) = 160 khz and a duty cycle
  equal to tmr15_c1dt/(tmr15_pr + 1) = 60%

  for more detailed information. please refer to the application note document AN0085.
