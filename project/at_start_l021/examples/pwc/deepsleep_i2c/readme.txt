/**
  **************************************************************************
  * @file     readme.txt 
  * @brief    readme
  **************************************************************************
  */

  this demo is based on the at-start board, in this demo, shows how to exit
  deepsleep mode by interrupt of i2c1. if the communication is successful, 
  led3 will turn on, if the communication fails, led2 will keep flashing.
  change the macro definition MASTER_BOARD can switch among master-transmit/
  slave-receive master-receive/slave-transmit operation.

  attention:
    1. i2c bus must pull-up
    2. press the slave button first, then press the master button to start communication.

  pin used:
    1. scl --- pb6
    2. sda --- pb7
	
  for more detailed information. please refer to the application note document AN0139.


