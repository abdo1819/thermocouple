/**
 * \file spi.c
 *
 * Hardware SPI driver
 *
 * (C)2014 CandraTech Ltd. All rights reserved
 *
 */

#include <avr/io.h>

#include "system.h"
#include "spi.h"
#include "uart.h"

void spiInit(void)
{
  uartStr(UART_CHAN0, "spiInit()...");
  /*Set MOSI and SCK as outputs*/
  SPI_SCK_DDR |= (1 << SPI_SCK_PIN);

  PORTC_DIR |= (1 << 4); /*Set /SS as an output to stop it from 
			   screwing with the SPI transfers*/

  SPIC_CTRL = (1 << SPI_PRESCALER0_bp); /*Div by 8 prescale*/
  SPIC_CTRL |= (1 << SPI_ENABLE_bp) | (1 << SPI_MASTER_bp);

  uartStr(UART_CHAN0, "Done.\r\n");
}

void spiTxByte(unsigned char byte)
{
  if(!(SPIC_CTRL & (1 << SPI_MASTER_bp)))
    {
     SPIC_CTRL |= (1 << SPI_MASTER_bp);
    }

  SPIC_DATA = byte;
  while(!(SPIC_STATUS & (1 << SPI_IF_bp)))
    ;
}

unsigned char spiRxByte(void)
{
  spiTxByte(0x00); /*Write dummy byte*/
  return SPIC_DATA;
}
