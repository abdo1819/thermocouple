/**
 * \file pwm.c
 *
 * \brief PWM driver
 *
 * (C)2014 CandraTech Ltd. All rights reserved
 *
 */

#include <avr/io.h>
#include "debug.h"
#include "pwm.h"

/** PWM initialisation routine
 *
 * Currently this function initialises the PWM module along with TCE0 0.
 *
 */
void pwmInit(void)
{
  DEBUG_STR("pwmInit()...", DEBUG_LEVEL_0);

  /*Must set high before output!*/
  PORTE_OUT &= ~(1 << PIN1_bp); /*Set the Backlight line low */
  PORTE_OUT &= ~(1 << PIN0_bp); /*Set the Contrast line low */

  PORTE_DIR |= (1 << PIN1_bp); /*Set the PWM line as O/P */
  PORTE_DIR |= (1 << PIN0_bp); /*Set the CTRL line as O/P */

  TCE0_PER = PWM_MAX; /*Period reg */
  TCE0_CTRLB |= (3 << TC0_WGMODE_gp); /*Set Singleslope PWM mode*/

  TCE0_CTRLB |= TC0_CCAEN_bm; /*Enable OC pin A Boost*/
  TCE0_CTRLB |= TC0_CCBEN_bm; /*Enable OC pin B LED*/

  TCE0_CTRLA = 0;
  TCE0_CTRLA |= (TC_CLKSEL_DIV1_gc); /*Set clk source to be clk/2*/

  DEBUG_STR("Done.\r\n", DEBUG_LEVEL_0);

}

/** PWM set value routine
 *
 * Currently this function passes the required power level to the PWM module
 *
 */
void pwmSet(unsigned char channel, unsigned int value)
{
  switch(channel)
    {
    case 0: 
      TCE0_CCA = value;
      break;
    case 1: 
      TCE0_CCB = value;
      break;
    case 2: 
      TCE0_CCC = value;
      break;
    case 3: 
      TCE0_CCD = value;
      break;
    default:
      break;
    }
}
