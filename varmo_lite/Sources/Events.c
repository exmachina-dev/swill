/* ###################################################################
**     Filename    : Events.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-05-30, 15:08, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "LED_DEBUG.h"
#include "LED_STATUS_1.h"
#include "LED_STATUS_2.h"
#include "LED_STATUS_3.h"
#include "LED_STATUS_4.h"

#ifdef __cplusplus
extern "C" {
#endif 

int i;
int encoder=1000;
bool FLAG_PUSH_SHORT =0;
bool FLAG_PUSH_LONG = 0;
short counter_100ms = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX256MC7]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  T_500ms_OnCounterRestart (module Events)
**
**     Component   :  T_500ms [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void T_500ms_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	//i++;
	//led_init(i);

	//LED_DEBUG_NegVal();
}

/*
** ===================================================================
**     Event       :  T_100ms_OnCounterRestart (module Events)
**
**     Component   :  T_100ms [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void T_100ms_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	counter_100ms += 1;
	if (counter_100ms == 5){
		FLAG_PUSH_LONG = 1;
		T_100ms_Disable(&UserDataPtr);
		counter_100ms =0;
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(1);
		LED_STATUS_4_PutVal(0);
	}
}

/*
** ===================================================================
**     Event       :  ENCODER_OnPortEvent (module Events)
**
**     Component   :  ENCODER [GPIO_LDD]
*/
/*!
**     @brief
**         Called if defined event on any pin of the port occured.
**         OnPortEvent event and GPIO interrupt must be enabled. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled if [Interrupt service/event] is Enabled and disabled
**         if [Interrupt service/event] is Disabled.
**     @param
**         UserDataPtr     - Pointer to RTOS device
**                           data structure pointer.
*/
/* ===================================================================*/
void ENCODER_OnPortEvent(LDD_TUserData *UserDataPtr)
{
	if (ENCODER_GetFieldValue(&UserDataPtr, ENCODER_B) == 1){
		if (ENCODER_GetFieldValue(&UserDataPtr, ENCODER_A) == 0){
			encoder -= 1;
		}
		else {
			encoder += 1;
		}
	}
	LED_STATUS_1_NegVal();
}

/*
** ===================================================================
**     Event       :  ENCODER_PUSH_OnInterrupt (module Events)
**
**     Component   :  ENCODER_PUSH [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ENCODER_PUSH_OnInterrupt(void)
{
	if (ENCODER_PUSH_GetVal() == 0){ //Encoder Pushed
		FLAG_PUSH_SHORT = 0;
		FLAG_PUSH_LONG = 0;
		LED_STATUS_2_PutVal(1);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(0);
		counter_100ms = 0;
		T_100ms_Enable(T_100ms_DeviceData);
	}
	else if (ENCODER_PUSH_GetVal() == 1 && FLAG_PUSH_LONG == 0){
		T_100ms_Disable(T_100ms_DeviceData);
		counter_100ms = 0;
		FLAG_PUSH_SHORT = 1;
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(1);
	}
	LED_DEBUG_NegVal();
}

/*
** ===================================================================
**     Event       :  DIRECTION_2_OnInterrupt (module Events)
**
**     Component   :  DIRECTION_2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DIRECTION_2_OnInterrupt(void)
{
	if (DIRECTION_2_GetVal() == 1) {
		//MOTOR DIRECTION -
	}
	else{
		//MOTOR OFF
	}
}

/*
** ===================================================================
**     Event       :  DIRECTION_1_OnInterrupt (module Events)
**
**     Component   :  DIRECTION_1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DIRECTION_1_OnInterrupt(void)
{
	if (DIRECTION_1_GetVal() == 1) {
		//MOTOR DIRECTION -
	}
	else{
		//MOTOR OFF
	}
}


/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
