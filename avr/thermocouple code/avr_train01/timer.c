/**
 * \file timer.c
 *
 * \brief Timer driver
 *
 * (C)2014 OrcaLight Ltd. All rights reserved
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
volatile static unsigned int intSeconds; /*Driver internal seconds counter*/

volatile unsigned int tempUpdateTimer; /*Controls temperature readings*/
volatile unsigned int stageTimer; /*Times each reflow stage*/



#include "timer.h"

/** timer initialisation routine
 *
 * Currently this function initialises the PWM module along with TCD0 0.
 *
 */
void timerInit(void)
{
  uartStr(UART_CHAN0, "timerInit()...");

  // TCC1_CTRLA |= TC_CLKSEL_DIV4_gc;
  TCC1_PER = 0x7fff; /*Period reg */

  TCC1_CCA = 0x7A12; /*compare at 31,250*/
  TCC1_CCA = 0x1; /*compare at 31,250*/

  intSeconds = 0;



  TCC1_INTFLAGS=0;
  TCC1_INTCTRLA |= (1 << 0);
  /* Enable low level interrupts. */
  

  TCC1_CTRLA |= (TC_CLKSEL_DIV64_gc); /*Set clk source to be clk/64*/

  uartStr(UART_CHAN0, "Done.\r\n");

}

ISR(TCC1_OVF_vect)
{
  intSeconds++;
  tempUpdateTimer ++;
  stageTimer++;
  if(intSeconds > 59)
    {
      intSeconds = 0;
    }
}
