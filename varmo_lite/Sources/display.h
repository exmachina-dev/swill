/* ###################################################################
**     Filename    : display.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VMC7
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

#include <string.h>
#include <stdio.h>

#ifndef SOURCES_DISPLAY_H_
#define SOURCES_DISPLAY_H_

/* MODULE main */

#include "LED_STATUS_1.h"
#include "LED_STATUS_2.h"
#include "LED_STATUS_3.h"
#include "LED_STATUS_4.h"

#include "menu.h"


#ifdef __cplusplus
extern "C" {
#endif

void led_init(int);

menu menu_init();

void velocity_fct();
void acceleration_fct();
void deceleration_fct();

void pos_velocity_fct();
void pos_acceleration_fct();
void pos_deceleration_fct();

void torque_fct();
void torque_rise_fct();
void torque_fall_fct();

void back_fct();



#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_DISPLAY_H_ */

