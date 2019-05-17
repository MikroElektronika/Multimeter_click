![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Multimeter Click

- **CIC Prefix**  : MULTIMETER
- **Author**      : Djordje Rosic
- **Verison**     : 1.0.0
- **Date**        : jul 2018.

---


### Software Support

We provide a library for the Multimeter Click on our [LibStock](https://libstock.mikroe.com/projects/view/2243/multimeter-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library contains calibration function, to be used on startup for more accurate readings, as well as
4 functions that measure Voltage, Current, Resistance and Capacitance.Calibration should be performed at startup 
when all measurement leads are disconnected.

Key functions :

- ``` float multimeter_measureU() ``` - This function measures voltage, and returns the value in millivolts.
- ``` float multimeter_measureR() ``` - This function measures resistance, and returns the value in ohms.
- ``` float multimeter_measureC() ``` - This function measures capacitance, and returns the value in nanofarads.
- ``` float multimeter_measureI() ``` - This function measures current, and returns the value in milliamperes.

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes pin control, spi peripheral and logger.
- Application Initialization - Initializes the driver, and performs calibration.
- Application Task (Code snippet) - Outputs read values.


```.c

    char text[20];
    float value = 0;
    value = multim_measureR();
    FloatToStr(value,text);
    mikrobus_logWrite("R = ",_LOG_TEXT);
    mikrobus_logWrite(text,_LOG_TEXT);
    mikrobus_logWrite("  Ohms",_LOG_LINE);

    value = multim_measureU();
    FloatToStr(value,text);
    mikrobus_logWrite("U = ",_LOG_TEXT);
    mikrobus_logWrite(text,_LOG_TEXT);
    mikrobus_logWrite("  mV",_LOG_LINE);


    value = multim_measureI();
    FloatToStr(value,text);
    mikrobus_logWrite("I = ",_LOG_TEXT);
    mikrobus_logWrite(text,_LOG_TEXT);
    mikrobus_logWrite("  mA",_LOG_LINE);


    value = multim_measureC();
    FloatToStr(value,text);
    mikrobus_logWrite("C = ",_LOG_TEXT);
    mikrobus_logWrite(text,_LOG_TEXT);
    mikrobus_logWrite("  nF",_LOG_LINE);

    mikrobus_logWrite("-------------------",_LOG_LINE);
    Delay_ms( 1000 );

```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2243/multimeter-click) page.

Other mikroE Libraries used in the example:

- Conversions
- C_String 
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
