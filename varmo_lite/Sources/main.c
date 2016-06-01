/* ###################################################################
**     Filename    : main.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-05-30, 15:08, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED_DEBUG.h"
#include "BitIoLdd1.h"
#include "T_500ms.h"
#include "LED_STATUS_1.h"
#include "BitIoLdd2.h"
#include "LED_STATUS_2.h"
#include "BitIoLdd3.h"
#include "LED_STATUS_3.h"
#include "BitIoLdd4.h"
#include "LED_STATUS_4.h"
#include "BitIoLdd5.h"
#include "ENCODER.h"
#include "ENCODER_PUSH.h"
#include "ExtIntLdd1.h"
#include "DIRECTION_1.h"
#include "ExtIntLdd2.h"
#include "DIRECTION_2.h"
#include "ExtIntLdd3.h"
#include "T_100ms.h"
#include "LCD.h"
#include "IntI2cLdd1.h"

//#include "LCD.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/


  /* Write your code here */
  LCD_SelectSlave(0x70);

  LCD_SendChar(0x0);

  byte error = LCD_SendStop();
  /*
  if (error == ERR_OK){
	  LED_STATUS_1_PutVal(1);
  }
  else if (error == ERR_BUSOFF){
	  LED_STATUS_2_PutVal(1);
  }
  else if (error == ERR_SPEED){
	  LED_STATUS_3_PutVal(1);
  }
  else if (error == ERR_DISABLED){
	  LED_STATUS_4_PutVal(1);
  }*/
  for(;;){

	  /*
	  bool mode = LCD_GetMode();
	  if (mode){
		  //master mode
		  LED_STATUS_4_PutVal(1);
	  }
	  else{
		  //slave mode
		  LED_STATUS_4_PutVal(0);
	  }

	  LCD_SelectSlave(0x1110000);
	  LCD_SendChar(0x0);

	  /*
	  LCD_SelectSlave(0x1110000);
	  LCD_SendChar(0x38);

	  LCD_SendChar(0x39);
	  LCD_SendChar(0x14);
	  LCD_SendChar(0x73);
	  LCD_SendChar(0x5E);
	  LCD_SendChar(0x6D);
	  LCD_SendChar(0x0C);
	  LCD_SendChar(0x01);
	  LCD_SendChar(0x06);*/


  }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
