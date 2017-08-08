/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : IntFlashLdd1.h
**     Project     : varmo_lite
**     Processor   : MK20DX256VLH7
**     Component   : FLASH_LDD
**     Version     : Component 01.106, Driver 01.15, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-14, 11:05, # CodeGen: 305
**     Abstract    :
**          This embedded component implements an access to an on-chip flash memory.
**          Using this component the flash memory could be written to, erased,
**          read from. Some other services would be provided, if they are supported
**          by hardware, e.g. changes of the flash memory protection state.
**     Settings    :
**          Component name                                 : IntFlashLdd1
**          Device                                         : FTFL
**          Use user memory areas                          : no
**          Interrupt service                              : Disabled
**            Write batch size                             : Minimal
**            Erase batch size                             : Minimal
**            Read batch size                              : Unlimited
**          Safe launch and wait                           : yes
**            Safe routine location                        : On stack
**            Interruptable wait loop                      : no
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnOperationComplete                        : Enabled
**              OnError                                    : Enabled
**            CPU clock/configuration selection            : 
**              Clock configuration 0                      : This component enabled
**              Clock configuration 1                      : This component disabled
**              Clock configuration 2                      : This component disabled
**              Clock configuration 3                      : This component disabled
**              Clock configuration 4                      : This component disabled
**              Clock configuration 5                      : This component disabled
**              Clock configuration 6                      : This component disabled
**              Clock configuration 7                      : This component disabled
**     Contents    :
**         Init               - LDD_TDeviceData* IntFlashLdd1_Init(LDD_TUserData *UserDataPtr);
**         Read               - LDD_TError IntFlashLdd1_Read(LDD_TDeviceData *DeviceDataPtr,...
**         Write              - LDD_TError IntFlashLdd1_Write(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         Erase              - LDD_TError IntFlashLdd1_Erase(LDD_TDeviceData *DeviceDataPtr,...
**         GetOperationStatus - LDD_FLASH_TOperationStatus IntFlashLdd1_GetOperationStatus(LDD_TDeviceData...
**         GetError           - void IntFlashLdd1_GetError(LDD_TDeviceData *DeviceDataPtr,...
**         Main               - void IntFlashLdd1_Main(LDD_TDeviceData *DeviceDataPtr);
**         GetDriverState     - LDD_TDriverState IntFlashLdd1_GetDriverState(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file IntFlashLdd1.h
** @version 01.15
** @brief
**          This embedded component implements an access to an on-chip flash memory.
**          Using this component the flash memory could be written to, erased,
**          read from. Some other services would be provided, if they are supported
**          by hardware, e.g. changes of the flash memory protection state.
*/         
/*!
**  @addtogroup IntFlashLdd1_module IntFlashLdd1 module documentation
**  @{
*/         

#ifndef __IntFlashLdd1_H
#define __IntFlashLdd1_H

/* MODULE IntFlashLdd1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "FTFL_PDD.h"
#include "FMC_PDD.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Parameters of the flash memory blocks used by the component - general format */
#define IntFlashLdd1_BLOCK0_ADDRESS            0x00LU
#define IntFlashLdd1_BLOCK0_SIZE               0x00040000LU
#define IntFlashLdd1_BLOCK0_ERASABLE_UNIT_SIZE 0x0800LU
#define IntFlashLdd1_BLOCK0_PROT_UNIT_SIZE     0x2000LU

#define IntFlashLdd1_BLOCK1_ADDRESS            0x10000000LU
#define IntFlashLdd1_BLOCK1_SIZE               0x8000LU
#define IntFlashLdd1_BLOCK1_ERASABLE_UNIT_SIZE 0x0400LU
#define IntFlashLdd1_BLOCK1_PROT_UNIT_SIZE     0x1000LU

/* Parameters of the flash memory blocks used by the component - CPU specific format */
#define IntFlashLdd1_PFLASH_ADDRESS            0x00LU
#define IntFlashLdd1_PFLASH_SIZE               0x00040000LU
#define IntFlashLdd1_PFLASH_ERASABLE_UNIT_SIZE 0x0800LU
#define IntFlashLdd1_PFLASH_PROT_UNIT_SIZE     0x2000LU

#define IntFlashLdd1_DFLASH_ADDRESS            0x10000000LU
#define IntFlashLdd1_DFLASH_SIZE               0x8000LU
#define IntFlashLdd1_DFLASH_ERASABLE_UNIT_SIZE 0x0400LU
#define IntFlashLdd1_DFLASH_PROT_UNIT_SIZE     0x1000LU
#define IntFlashLdd1_ERASABLE_UNIT_SIZE        0x0800LU
#define IntFlashLdd1_ERASABLE_UNIT_MASK        0x07FFLU
#define IntFlashLdd1_WRITE_UNIT_SIZE           0x04LU
#define IntFlashLdd1_WRITE_UNIT_MASK           0x03LU

/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define IntFlashLdd1_PRPH_BASE_ADDRESS  0x40020000U
  
/* Methods configuration constants - generated for all enabled component's methods */
#define IntFlashLdd1_Init_METHOD_ENABLED /*!< Init method of the component IntFlashLdd1 is enabled (generated) */
#define IntFlashLdd1_Read_METHOD_ENABLED /*!< Read method of the component IntFlashLdd1 is enabled (generated) */
#define IntFlashLdd1_Write_METHOD_ENABLED /*!< Write method of the component IntFlashLdd1 is enabled (generated) */
#define IntFlashLdd1_Erase_METHOD_ENABLED /*!< Erase method of the component IntFlashLdd1 is enabled (generated) */
#define IntFlashLdd1_GetOperationStatus_METHOD_ENABLED /*!< GetOperationStatus method of the component IntFlashLdd1 is enabled (generated) */
#define IntFlashLdd1_GetError_METHOD_ENABLED /*!< GetError method of the component IntFlashLdd1 is enabled (generated) */
#define IntFlashLdd1_Main_METHOD_ENABLED /*!< Main method of the component IntFlashLdd1 is enabled (generated) */
#define IntFlashLdd1_GetDriverState_METHOD_ENABLED /*!< GetDriverState method of the component IntFlashLdd1 is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define IntFlashLdd1_OnOperationComplete_EVENT_ENABLED /*!< OnOperationComplete event of the component IntFlashLdd1 is enabled (generated) */
#define IntFlashLdd1_OnError_EVENT_ENABLED /*!< OnError event of the component IntFlashLdd1 is enabled (generated) */

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Init (component FLASH_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" property is set to "yes" ([Enabled in init.
**         code]) value then the device is also enabled(see the
**         description of the Enable() method). In this case the
**         Enable() method is not necessary and needn't to be generated.
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* IntFlashLdd1_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Write (component FLASH_LDD)
*/
/*!
**     @brief
**         This method sets up a flash memory write operation. The
**         operation itself is performing by defined batches (property
**         [Write batch size]) by periodical calling the componentís
**         Main method in the user application (higher level OS service)
**         or by the componentís ISR, if an componentís interrupt
**         service is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         FromPtr         - Pointer to data to be written to
**                           the flash memory.
**     @param
**         ToAddress       - Address to the flash memory
**                           the input data would be written to.
**     @param
**         Size            - Size of the input data (in bytes) to be
**                           written to the flash memory.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_DISABLED - Component is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - Some flash memory operation is
**                           already in progress 
**                           ERR_PARAM_ADDRESS - Desired flash memory
**                           area is out of allowed range
**                           ERR_NOTAVAIL - When Safe launch and wait
**                           mode is enabled (property Safe launch and
**                           wait) and safe routine location is defined
**                           in runtime (property Safe routine location)
**                           and the safe routine location has not been
**                           specified yet (the SetSafeRoutineLocation
**                           method has not been used to define the
**                           location the safe routine will be copied to).
*/
/* ===================================================================*/
LDD_TError IntFlashLdd1_Write(LDD_TDeviceData *DeviceDataPtr, LDD_TData *FromPtr, LDD_FLASH_TAddress ToAddress, LDD_FLASH_TDataSize Size);

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Read (component FLASH_LDD)
*/
/*!
**     @brief
**         This method sets up a flash memory read operation. The
**         operation itself is performing by defined batches (property
**         [Read batch size]) by periodical calling the componentís
**         Main method in the user application (higher level OS service).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         FromAddress     - Address to the flash
**                           memory the output data would be read from.
**     @param
**         ToPtr           - Pointer to a location the data would
**                           be written to.
**     @param
**         Size            - Size of the data (in bytes)  to be read
**                           from the flash memory.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_DISABLED - Component is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - Some flash memory operation is
**                           already in progress 
**                           ERR_PARAM_ADDRESS - Desired flash memory
**                           area is out of allowed range
*/
/* ===================================================================*/
LDD_TError IntFlashLdd1_Read(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TAddress FromAddress, LDD_TData *ToPtr, LDD_FLASH_TDataSize Size);

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Erase (component FLASH_LDD)
*/
/*!
**     @brief
**         This method sets up a flash memory erase operation. The
**         operation itself is performing by defined batches (property
**         [Erase batch size]) by periodical calling the componentís
**         Main method in the user application (higher level OS service)
**         or by the componentís ISR, if an componentís interrupt
**         service is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         FromAddress     - Address of the flash
**                           memory area (the first erase sector is the
**                           sector the given address belongs to) to be
**                           erased.
**     @param
**         Size            - Size of the flash memory area (in bytes)
**                           to be erased. The flash memory is erased by
**                           the erase sectors. The first erased sector
**                           is a sector the address specified by the
**                           input parameter Address belongs to. The
**                           last erased sector is a sector the address
**                           calculated like an addition of the address
**                           specified by the input parameter Address
**                           and the size specified by the input
**                           parameter Size belongs to.
**     @return
**                         - Error code
**                           ERR_OK - OK
**                           ERR_DISABLED - Component is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - Some flash memory operation is
**                           already in progress 
**                           ERR_PARAM_ADDRESS - Desired flash memory
**                           area is out of allowed range or is not
**                           aligned to erasable units' bounderies
**                           ERR_NOTAVAIL - When Safe launch and wait
**                           mode is enabled (property Safe launch and
**                           wait) and safe routine location is defined
**                           in runtime (property Safe routine location)
**                           and the safe routine location has not been
**                           specified yet (the SetSafeRoutineLocation
**                           method has not been used to define the
**                           location the safe routine will be copied to).
*/
/* ===================================================================*/
LDD_TError IntFlashLdd1_Erase(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TAddress FromAddress, LDD_FLASH_TDataSize Size);

/*
** ===================================================================
**     Method      :  IntFlashLdd1_GetOperationStatus (component FLASH_LDD)
*/
/*!
**     @brief
**         Returns a status of current (last) flash memory operation.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Current flash memory operation status. See
**                           the LDD_FLASH_TOperationStatus type's
**                           description for details.
*/
/* ===================================================================*/
LDD_FLASH_TOperationStatus IntFlashLdd1_GetOperationStatus(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  IntFlashLdd1_Main (component FLASH_LDD)
*/
/*!
**     @brief
**         This method is used to perform one batch of a flash memory
**         operation. This method is used to perform batches of all
**         flash memory operations (Write, Read, Erase, EraseBlock,
**         VerifyErasedBlock) when the component works in the polled
**         mode (interrupt service is disabled - property [Interrupt
**         service]). This method performs batches of the read flash
**         memory operation, when the component works in the interrupt
**         triggered mode (interrupt service is enabled). This method
**         is enabled only if the component works in the polled mode or
**         if the Read method is enabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
*/
/* ===================================================================*/
void IntFlashLdd1_Main(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  IntFlashLdd1_GetError (component FLASH_LDD)
*/
/*!
**     @brief
**         Returns an error state of a current (or last) flash
**         operation. 
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         OperationStatus - Pointer to an
**                           output structure with the error status
**                           details. See the LDD_FLASH_TErrorStatus
**                           type's description for details.
*/
/* ===================================================================*/
void IntFlashLdd1_GetError(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TErrorStatus *OperationStatus);

/*
** ===================================================================
**     Method      :  IntFlashLdd1_GetDriverState (component FLASH_LDD)
*/
/*!
**     @brief
**         This method returns the current driver status.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - The current driver status mask.
**                           Following status masks defined in PE_Types.
**                           h can be used to check the current driver
**                           status.
**                           PE_LDD_DRIVER_DISABLED_IN_CLOCK_CONFIGURATIO
**                           N - 1 - Driver is disabled in the current
**                           mode; 0 - Driver is enabled in the current
**                           mode.  
**                           PE_LDD_DRIVER_DISABLED_BY_USER - 1 - Driver
**                           is disabled by the user; 0 - Driver is
**                           enabled by the user.        
**                           PE_LDD_DRIVER_BUSY - 1 - Driver is the BUSY
**                           state; 0 - Driver is in the IDLE state.
*/
/* ===================================================================*/
LDD_TDriverState IntFlashLdd1_GetDriverState(LDD_TDeviceData *DeviceDataPtr);

/* END IntFlashLdd1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __IntFlashLdd1_H */
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
