/*
    __multimeter_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__multimeter_driver.h"
#include "__multimeter_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

static uint8_t I_CHANNEL = 0x00;
static uint8_t U_CHANNEL = 0x01;
static uint8_t R_CHANNEL = 0x02;
static uint8_t C_CHANNEL = 0x03;

static float Rg_1 = 200000;
static float Rg_2 = 200000;
static float Rx_1 = 0;
static float Rx_2 = 0;
static float calibrationC = 0;
static float calibrationI = 0;
static float calibrationU = 0;
static uint8_t rangeScan;

/* Resistor values */

static float _ResSel[6]={ 100.0, 1000.0, 10000.0, 100000.0, 470000.0, 1000000.0 };
static float _Vmax = 4095.0;
#ifdef   __MULTIMETER_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint16_t readChannelValue(uint8_t channel);

//static void calibrateR();
static void calibrateC();
static void calibrateI();
static void calibrateU();


/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint16_t readChannelValue(uint8_t channel)
{
    uint8_t wr = 0;
    uint8_t rd[2] = { 0 };
    uint16_t result = 0;

    wr = 0x06;                                // Start and SGL bit
    hal_gpio_csSet(0);                        // Select MCP3204

    hal_spiWrite( &wr, 1 );                     // SPI communication using 8-bit segments
    wr = ( channel & 0x03 ) << 6;                       // Add channel bits (2 LSB in channel)
    hal_spiTransfer(&wr, rd, 1 );
    wr = 0;
    hal_spiTransfer(&wr, rd+1, 1 );

    result = rd[0] & 0x0F ;
    result <<= 8;
    result |= rd[1];

    hal_gpio_csSet(1);                        // Deselect MCP3204
    return result;                            // Returns 12-bit ADC value
}

static void calibrateR()
{
  rangeScan = 0;
}

static void calibrateC()
{
    float measurementC;
    measurementC = readChannelValue(C_CHANNEL)/2;
    calibrationC = (64285 / (measurementC*4));
}

static void calibrateI()
{
    calibrationI =  readChannelValue(I_CHANNEL)/2;
}

static void calibrateU()
{
    calibrationU =  readChannelValue(U_CHANNEL)/2;
}


/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __MULTIMETER_DRV_SPI__

void multimeter_spiDriverInit(T_MULTIMETER_P gpioObj, T_MULTIMETER_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MULTIMETER_DRV_I2C__

void multimeter_i2cDriverInit(T_MULTIMETER_P gpioObj, T_MULTIMETER_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MULTIMETER_DRV_UART__

void multimeter_uartDriverInit(T_MULTIMETER_P gpioObj, T_MULTIMETER_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

static void multimeter_rangeSel(uint8_t rSel)
{
    uint8_t _rSelTst;
    _rSelTst = rSel;
    if(_rSelTst > 5)
    {
       _rSelTst = 5;
    }
    hal_gpio_intSet(_rSelTst.B2);
    hal_gpio_pwmSet(_rSelTst.B1);
    hal_gpio_anSet(_rSelTst.B0);
    Delay_100ms();
    
    
}
static uint16_t multimeter_adcR(uint8_t rSel)
{
    uint16_t Rv;
    uint8_t _rSelTst;
    _rSelTst = rSel;
    if(_rSelTst > 5)
    {
       _rSelTst = 5;
    }
    Rv = readChannelValue(R_CHANNEL);
    return Rv;
}
uint16_t multimeter_measureRrange(uint8_t range)
{
    uint16_t Rv;
    float Rmx;

    multimeter_rangeSel(range);
    Delay_100ms();

    Rv = multimeter_adcR(range);

    return Rv;
}

float multimeter_measureR()
{
   float Rmx;
   uint16_t Rv;
   Rv = multimeter_measureRrange(rangeScan);
   if(rangeScan>5) rangeScan=0;
   if(rangeScan==5) rangeScan=0;
    if(Rv>2000)
    {
      if(Rv > 3000)
      {
         if(Rv>4090)
         {
           Rmx = ( ( ( _ResSel[rangeScan] * _Vmax ) / Rv ) - _ResSel[rangeScan] );
           if(rangeScan>5) rangeScan=5;
           rangeScan--;
           return  Rmx;
         }
      }
    }
    if(Rv<2000)
    {
      if(Rv < 1500)
      {
         if(Rv<100)
         {
           if(rangeScan<5) rangeScan++;
         }
      }
    }
   Rmx = ( ( ( _ResSel[rangeScan] * _Vmax ) / Rv ) - _ResSel[rangeScan] );
  
   return Rmx;
}

float multimeter_measureC()
{
    float measurementC;
    float capacitance;
    measurementC = readChannelValue(C_CHANNEL)/2;             // Get ADC result from Channel 3
    capacitance = ((64285 / (measurementC*4)) - calibrationC)*2;      // Calculate C [nF]

    if(capacitance < 1)
    {
        capacitance = 0;
    }

    return capacitance;
}

float multimeter_measureI()
{
    float measurementI;
    float current;

    measurementI = readChannelValue(I_CHANNEL)/2;       // Get ADC result from Channel 0

    current = measurementI - calibrationI;
    
    return current;
}

float multimeter_measureU()
{
    float measurementU = 0;
    float voltage = 0;

    measurementU = readChannelValue(U_CHANNEL)/2;       // Get ADC result from Channel 1
    voltage = (measurementU - calibrationU)*33/2 ;
    
    return voltage;
}

void multimeter_calibrate()
{
    calibrateC();
    calibrateI();
    calibrateR();
    calibrateU();
}






/* -------------------------------------------------------------------------- */
/*
  __multimeter_driver.c

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
