/* ###################################################################
**     Filename    : main.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-03, 16:50, # CodeGen: 62
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
#include "LEVER_DIR1.h"
#include "ExtIntLdd2.h"
#include "LEVER_DIR2.h"
#include "ExtIntLdd3.h"
#include "T_100ms.h"
#include "I2C0.h"
#include "IntI2cLdd1.h"
#include "PUSH_BUTTON_SEND.h"
#include "ExtIntLdd4.h"
#include "PUSH_BUTTON_REC.h"
#include "ExtIntLdd5.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "LCD_CTR.h"
#include "BitIoLdd6.h"
#include "WAIT1.h"
#include "LCD_EN.h"
#include "BitIoLdd7.h"
#include "KSDK1.h"
#include "CS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "encoder_variable.h"
#include "display.h"
#include "protocol.h"
#include "LCD.h"
#include "PCA9670.h"
#include <stdio.h>
#include <stdlib.h>

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  counter_100ms =0;
  FLAG_PUSH_LONG = 0;
  FLAG_PUSH_SHORT = 0;
  cnt = 0;
  FLAG_MSG_RCV = 0;
  FLAG_MSG_ERR = 0;
  FLAG_MSG_OK = 0;
  FLAG_MENU = 1;
  nb_data = 0;

  int cnt_err = 0;
  int cnt_ok = 0;
  WAIT1_Waitms(15);
  PCA9670_Init();
  T_100ms_Disable(T_100ms_DeviceData);
  LCD_Init();

  //LCD_Cursor_Blink_On();
  //LCD_Write_Block("Varmo V2.0", 1, 3);
  menu_init();


  for(;;){
	  char msg[cnt];
	  int nb_data = 0;

	  if (FLAG_ENCODER == 1){
		  if (FLAG_MENU == 1){
			  encoder = refresh((int)encoder);
		  }
		  FLAG_ENCODER = 0;
	  }
	  if (FLAG_PUSH_SHORT == 1){
		  if (FLAG_MENU == 1){
			  encoder = select((int)encoder);
		  }
		  FLAG_PUSH_SHORT = 0;
	  }

	  if (FLAG_PUSH_LONG == 1){
		  encoder = back((int) encoder);
		  FLAG_PUSH_LONG = 0;
	  }
/*
	  //Check message received
	  if (FLAG_MSG_RCV == 1){
		  binaryRepr size;
		  size.toUint_8.toUint_8_1 = in_buffer[8];
		  size.toUint_8.toUint_8_0 = in_buffer[9];
		  size.toInt.int0 = (size.toUint_8.toUint_8_1 && 0xFF00) + size.toUint_8.toUint_8_0;
		  if ( size.toInt.int0 == (cnt + 1)){
			  int temp = cnt;
			  cnt = 0;
			  for (int f =0; f<=temp; f++){
				  msg[f] = in_buffer[f];
				  if (msg[f] == ':' || msg[f]== '\r'){
					  nb_data += 1;
				  }
				  FLAG_MSG_OK =1;
			  }
		  }
		  else{
			  cnt = 0;
			  FLAG_MSG_ERR = 1;
		  }
		  FLAG_MSG_RCV = 0;
	  }

	  ///Processing msg received
	  if (FLAG_MSG_OK == 1){
		  FLAG_MSG_ERR = msg_parse(msg);
		  FLAG_MSG_OK  = 0;
	  }
	  //COMMUNICATION ERR
	  if (FLAG_MSG_ERR == 1){
		  cnt_err += 1;
		  LED_STATUS_2_SetVal();
		  FLAG_MSG_ERR = 0;
	  }
	  else {
		  cnt_ok += 1;
		  LED_STATUS_2_ClrVal();
	  }*/
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
