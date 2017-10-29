/**
 * \file max6675.c
 *
 * MAX6675 driver
 *
 * (C)2014 CandraTech Ltd. All rights reserved
 *
 */

#include <avr/io.h>
#include "system.h"
#include "max6675.h"
#include "spi.h"
#include "uart.h"

static unsigned char openCouple = 0; /*1 = broken thermo-couple connection*/

void max6675Init(void)
{
  uartStr(UART_CHAN0, "max6675Init()...");
  /*Set CS pins as outputs and high*/
  MAX6675_CH1_CS_DIR |= (1 << MAX6675_CH1_CS_PIN);
  MAX6675_CH1_CS_PORT |= (1 << MAX6675_CH1_CS_PIN);
  uartStr(UART_CHAN0, "Done.\r\n");
}

unsigned int max6675Read(void)
{
  unsigned int result;
  
  MAX6675_CH1_CS_PORT &= ~(1 << MAX6675_CH1_CS_PIN);
  
  result = spiRxByte() << 8;
  result |= spiRxByte();

  MAX6675_CH1_CS_PORT |= (1 << MAX6675_CH1_CS_PIN);

  if(result & (1 << 2))
    openCouple = 1;
  else
    openCouple = 0;
  
  return (result >> 3)*0.25; 
}

unsigned char max6675CheckOpenCouple(void)
{
  return openCouple;
}
