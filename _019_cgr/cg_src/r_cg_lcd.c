/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_lcd.c
* Version      : Applilet4 for R7F0C019 V1.00.00.01 [31 Mar 2016]
* Device(s)    : R7F0C019L
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for LCD module.
* Creation Date: 2020/9/15 ÐÇÆÚ¶þ
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_lcd.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_LCD_Create
* Description  : This function initializes the LCD module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Create(void)
{
    volatile uint32_t wt_count;
    
    LCDON = 0U;    /* disable LCD clock operation */
    LCDM1 |= _00_LCD_VOLTAGE_HIGH;
    LCDM0 = _00_LCD_DISPLAY_WAVEFORM_A | _16_LCD_DISPLAY_MODE0;
    LCDM0 |= _40_LCD_VOLTAGE_MODE_INTERNAL;
    /* Set CAPL and CAPH pins */
    ISCLCD &= (uint8_t)~_01_LCD_CAPLH_INPUT_VALID;
    PU12 &= 0x3FU;
    P12 &= 0x3FU;
    PM12 |= 0xC0U;
    /* Set VL3 pin */
    ISCLCD &= (uint8_t)~_02_LCD_VL3_INPUT_VALID;
    PU12 &= 0xDFU;
    P12 &= 0xDFU;
    PM12 |= 0x20U;
    /* Set segment pins */
    PU1 &= 0xFEU;
    PU2 &= 0x7FU;
    PU3 &= 0xF0U;
    PU5 &= 0x63U;
    PU7 &= 0x0EU;
    POM5 &= 0xE7U;
    PIM5 &= 0xF7U;
    PFSEG0 |= 0xF0U;
    PFSEG1 |= 0xFFU;
    PFSEG2 |= 0xFFU;
    PFSEG3 |= 0xBBU;
    PFSEG4 |= 0x1BU;
    PMC1 &= 0xFEU;
    P1 &= 0xFEU;
    PM1 &= 0xFEU;
    PMC2 &= 0x7FU;
    P2 &= 0x7FU;
    PM2 &= 0x7FU;
    P3 &= 0xF0U;
    PM3 &= 0xF0U;
    P5 &= 0x63U;
    PM5 &= 0x63U;
    P7 &= 0x0EU;
    PM7 &= 0x0EU;
    LCDC0 = _05_LCD_CLOCK_FSUB_FIL_6;
    VLCD = _09_LCD_BOOST_VOLTAGE_125V;

    /* Change the waiting time according to the system */
    for (wt_count = 0U; wt_count <= LCD_REFVOLTAGE_WAITTIME; wt_count++)
    {
        NOP();
    }
}
/***********************************************************************************************************************
* Function Name: R_LCD_Start
* Description  : This function enables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Start(void)
{
    LCDON = 1U;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Stop
* Description  : This function disables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Stop(void)
{
    LCDON = 0U;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Voltage_On
* Description  : This function enables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Voltage_On(void)
{
    volatile uint32_t wt_count;

    LCDM0 |= _40_LCD_VOLTAGE_MODE_INTERNAL;
    VLCON = 1U;

    /* Change the waiting time according to the system */
    for(wt_count = 0U; wt_count <= LCD_VOLTAGE_WAITTIME; wt_count++)
    {
        NOP();
    }
    
    SCOC = 1U;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Voltage_Off
* Description  : This function disables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Voltage_Off(void)
{
    SCOC = 0U;
    VLCON = 0U;
    LCDM0 &= (uint8_t)~_C0_LCD_VOLTAGE_MODE_INITIALVALUE;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
