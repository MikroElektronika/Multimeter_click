/*
Example for Multimeter Click

    Date          : jul 2018.
    Author        : MikroE Team

Test configuration dsPIC :
    
    MCU                : P33FJ256GP710A
    Dev. Board         : EasyPIC Fusion v7
    dsPIC Compiler ver : v7.1.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes pin control, spi peripheral and logger.
- Application Initialization - Initializes the driver, and performs calibration.
- Application Task - Outputs read values.

*/

#include "Click_Multimeter_types.h"
#include "Click_Multimeter_config.h"

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_OUTPUT );
    
    mikrobus_spiInit( _MIKROBUS1, &_MULTIMETER_SPI_CFG[0] );

    mikrobus_logInit( _LOG_USBUART_A, 9600 );

    Delay_ms( 100 );
}

void applicationInit()
{
    multimeter_spiDriverInit( (T_MULTIMETER_P)&_MIKROBUS1_GPIO, (T_MULTIMETER_P)&_MIKROBUS1_SPI );
    multimeter_calibrate();
    mikrobus_logWrite("Initialized",_LOG_LINE);
}

void applicationTask()
{
    char text[20];
    float value = 0;
    value = multimeter_measureR();
    FloatToStr(value,text);
    mikrobus_logWrite("R = ",_LOG_TEXT);
    mikrobus_logWrite(text,_LOG_TEXT);
    mikrobus_logWrite("  Ohms",_LOG_LINE);

    value = multimeter_measureU();
    FloatToStr(value,text);
    mikrobus_logWrite("U = ",_LOG_TEXT);
    mikrobus_logWrite(text,_LOG_TEXT);
    mikrobus_logWrite("  mV",_LOG_LINE);


    value = multimeter_measureI();
    FloatToStr(value,text);
    mikrobus_logWrite("I = ",_LOG_TEXT);
    mikrobus_logWrite(text,_LOG_TEXT);
    mikrobus_logWrite("  mA",_LOG_LINE);


    value = multimeter_measureC();
    FloatToStr(value,text);
    mikrobus_logWrite("C = ",_LOG_TEXT);
    mikrobus_logWrite(text,_LOG_TEXT);
    mikrobus_logWrite("  nF",_LOG_LINE);

    mikrobus_logWrite("-------------------",_LOG_LINE);
    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}
