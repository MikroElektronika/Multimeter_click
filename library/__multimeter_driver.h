/*
    __multimeter_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __multimeter_driver.h
@brief    Multimeter Driver
@mainpage Multimeter Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   MULTIMETER
@brief      Multimeter Click Driver
@{

| Global Library Prefix | **MULTIMETER** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **jul 2018.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _MULTIMETER_H_
#define _MULTIMETER_H_

/** 
 * @macro T_MULTIMETER_P
 * @brief Driver Abstract type 
 */
#define T_MULTIMETER_P    const uint8_t*

/** @defgroup MULTIMETER_COMPILE Compilation Config */              /** @{ */

   #define   __MULTIMETER_DRV_SPI__                            /**<     @macro __MULTIMETER_DRV_SPI__  @brief SPI driver selector */
//  #define   __MULTIMETER_DRV_I2C__                            /**<     @macro __MULTIMETER_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __MULTIMETER_DRV_UART__                           /**<     @macro __MULTIMETER_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup MULTIMETER_VAR Variables */                           /** @{ */



                                                                       /** @} */
/** @defgroup MULTIMETER_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup MULTIMETER_INIT Driver Initialization */              /** @{ */

#ifdef   __MULTIMETER_DRV_SPI__
void multimeter_spiDriverInit(T_MULTIMETER_P gpioObj, T_MULTIMETER_P spiObj);
#endif
#ifdef   __MULTIMETER_DRV_I2C__
void multimeter_i2cDriverInit(T_MULTIMETER_P gpioObj, T_MULTIMETER_P i2cObj, uint8_t slave);
#endif
#ifdef   __MULTIMETER_DRV_UART__
void multimeter_uartDriverInit(T_MULTIMETER_P gpioObj, T_MULTIMETER_P uartObj);
#endif
                                                                       /** @} */
/** @defgroup MULTIMETER_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Calibration function
 *
 * This function calibrates multimeter, and should be called before any 
 * operation with the click.
 *
 * @note R Terminal should be short circuited, while I Terminal, U Terminal and
 * C Terminal should stay open.
 */
void multimeter_calibrate();

/**
 * @brief Measure Voltage
 *
 * This function measures voltage, and returns the value in millivolts.
 *
 * @retval       Measured voltage in millivolts
 */
float multimeter_measureU();

/**
 * @brief Measure Resistance
 *
 * This function measures resistance, and returns the value in ohms.
 *
 * @retval       Measured resistance in ohms
 */
float multimeter_measureR();

/**
 * @brief Measure Capacitance
 *
 * This function measures capacitance, and returns the value in nanofarads.
 *
 * @retval       Measured capacitance in nanofarads
 */
float multimeter_measureC();

/**
 * @brief Measure Current
 *
 * This function measures current, and returns the value in milliamperes.
 *
 * @retval       Measured current in milliamperes
 */
float multimeter_measureI();





                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Multimeter_STM.c
    @example Click_Multimeter_TIVA.c
    @example Click_Multimeter_CEC.c
    @example Click_Multimeter_KINETIS.c
    @example Click_Multimeter_MSP.c
    @example Click_Multimeter_PIC.c
    @example Click_Multimeter_PIC32.c
    @example Click_Multimeter_DSPIC.c
    @example Click_Multimeter_AVR.c
    @example Click_Multimeter_FT90x.c
    @example Click_Multimeter_STM.mbas
    @example Click_Multimeter_TIVA.mbas
    @example Click_Multimeter_CEC.mbas
    @example Click_Multimeter_KINETIS.mbas
    @example Click_Multimeter_MSP.mbas
    @example Click_Multimeter_PIC.mbas
    @example Click_Multimeter_PIC32.mbas
    @example Click_Multimeter_DSPIC.mbas
    @example Click_Multimeter_AVR.mbas
    @example Click_Multimeter_FT90x.mbas
    @example Click_Multimeter_STM.mpas
    @example Click_Multimeter_TIVA.mpas
    @example Click_Multimeter_CEC.mpas
    @example Click_Multimeter_KINETIS.mpas
    @example Click_Multimeter_MSP.mpas
    @example Click_Multimeter_PIC.mpas
    @example Click_Multimeter_PIC32.mpas
    @example Click_Multimeter_DSPIC.mpas
    @example Click_Multimeter_AVR.mpas
    @example Click_Multimeter_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __multimeter_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */

