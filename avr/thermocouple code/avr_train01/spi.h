/**
 * \file spi.c
 *
 * Hardware SPI driver
 *
 * (C)2014 CandraTech Ltd. All rights reserved
 *
 */

void spiInit(void);
void spiTxByte(unsigned char byte);
unsigned char spiRxByte(void);
