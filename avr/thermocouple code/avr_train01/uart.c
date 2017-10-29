/**
 * \file uart.c
 *
 * uart driver
 *
 * (C)2013 CandraTech Ltd. All rights reserved
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "system.h"
#include "uart.h"

/** \name UART FIFO length
 *
 *Defines the length of the fifo available for each UART channel in bytes
 *
 */
/**@{*/
#define UART_CHAN0_FIFO_LEN 10
#define UART_CHAN1_FIFO_LEN 0
#define UART_CHAN2_FIFO_LEN 0
#define UART_CHAN3_FIFO_LEN 0
#define UART_CHAN4_FIFO_LEN 0
/**@}*/

/** \name UART FIFO Definitions
 *
 * Defines the FIFO buffer along with the read and write indicies for each channel
 *
 */
/**@{*/
unsigned char uartChan0Fifo[UART_CHAN0_FIFO_LEN];
unsigned char uartChan0FifoWrite = 0;
unsigned char uartChan0FifoRead = 0;

unsigned char uartChan1Fifo[UART_CHAN1_FIFO_LEN];
unsigned char uartChan1FifoWrite = 0;
unsigned char uartChan1FifoRead = 0;

unsigned char uartChan2Fifo[UART_CHAN2_FIFO_LEN];
unsigned char uartChan2FifoWrite = 0;
unsigned char uartChan2FifoRead = 0; 

unsigned char uartChan3Fifo[UART_CHAN3_FIFO_LEN];
unsigned char uartChan3FifoWrite = 0;
unsigned char uartChan3FifoRead = 0; 

unsigned char uartChan4Fifo[UART_CHAN4_FIFO_LEN];
unsigned char uartChan4FifoWrite = 0;
unsigned char uartChan4FifoRead = 0; 
/**@}*/

/** \name Baud rate definitions 
 *
 * BAUD[] containes a list of baud rate values corrisponding to the available baud rates
 * in uart.h
 */
/**@{*/
#if UP_CLK == 2000000
const unsigned int BAUD[] = {51,25,12,7,5,3,2,1,0,0,0,0,0,0,0,0,0,0,0};
#endif

/**@}*/

/** Initialises the selected UART to the desired BAUD rate.
 *
 */
void uartInit(unsigned char uart, unsigned char baud)
{
  switch(uart)
    {
    case UART_CHAN0:
      PORTC_OUT |= (1 << PIN3);
      PORTC_DIR |= (1 << PIN3);
      PORTC_DIR &= ~(1 << PIN2);
      USARTC0_BAUDCTRLB &= ~(0 << USART_BSCALE0_bp);
      USARTC0_BAUDCTRLA = BAUD[baud] & 0xff;
      USARTC0_BAUDCTRLB |= ((BAUD[baud] >> 8) & 0xff);

      USARTC0_CTRLA |= (2 << USART_RXCINTLVL0_bp); /*Set USART RX int the medium priority*/
      USARTC0_CTRLC |= (3 << USART_CHSIZE0_bp);

      USARTC0_CTRLB |= (1 << USART_RXEN_bp) | (1 << USART_TXEN_bp);

      break;

    /* case UART_CHAN4: */
    /*   PORTE_OUT |= (1 << PIN3); */
    /*   PORTE_DIR |= (1 << PIN3); */
    /*   PORTE_DIR &= ~(1 << PIN2); */
    /*   USARTE0_BAUDCTRLB &= ~(0 << USART_BSCALE0_bp); */
    /*   USARTE0_BAUDCTRLA = BAUD[baud] & 0xff; */
    /*   USARTE0_BAUDCTRLB |= ((BAUD[baud] >> 8) & 0xff); */

    /*   USARTE0_CTRLC |= (3 << USART_CHSIZE0_bp); */

    /*   USARTE0_CTRLB |= (1 << USART_RXEN_bp) | (1 << USART_TXEN_bp); */
    /*   break; */
    default:
      break;
    }
}

/** Initialises the selected UART to the desired BAUD rate.
 *
 */
void uartTx(unsigned char uart, unsigned char data)
{
  switch(uart)
    {
    case UART_CHAN0:
      while(!(USARTC0_STATUS & (1 << USART_DREIF_bp)));
      USARTC0_DATA = data;
      break;
    /* case UART_CHAN4: */
    /*   while(!(USARTE0_STATUS & (1 << USART_DREIF_bp))); */
    /*   USARTE0_DATA = data; */
    /*   break; */
    default:
      break;
    }
}

/** Retrieves a single character from the specified uart in polling mode.
 *
 * Returns the character if available or 0xff if no character is available.
 *
 */
unsigned char uartRx(unsigned char uart)
{
  switch(uart)
    {
    case UART_CHAN0:
      if(USARTC0_STATUS & (1 << 5))
	{
	  return USARTC0_DATA;
	}
    /* case UART_CHAN4: */
    /*   if(USARTE0_STATUS & (1 << 5)) */
    /* 	{ */
    /* 	  return USARTE0_DATA; */
    /* 	} */
    /*   else */
    /* 	{ */
    /* 	  return 0xff; */
    /* 	}  */
    /*   break; */
    default:
      return 0xff;
      break;
    }
}

/** Outputs a null terminated string on the specified port.
 */
void uartStr(unsigned char uart, char * str)
{
  while(*str != '\0')
    {
      uartTx(uart, (unsigned char)*str++);
      //      str++;
    }
}

/** Outputs a 16bit hex value on the specified port.
 */
void uartHex16(unsigned char uart, unsigned int data)
{
  unsigned char dec2Hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  uartStr(uart, "0x\0");
  uartTx(uart, dec2Hex[(data >> 12) & 0x0f]);
  uartTx(uart, dec2Hex[(data >> 8) & 0x0f]);
  uartTx(uart, dec2Hex[(data >> 4) & 0x0f]);
  uartTx(uart, dec2Hex[data & 0x0f]);
}

/** Outputs a 8bit hex value on the specified port.
 */
void uartHex8(unsigned char uart, unsigned char data)
{
  unsigned char dec2Hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  uartStr(uart, "0x\0");
  uartTx(uart, dec2Hex[(data >> 4) & 0x0f]);
  uartTx(uart, dec2Hex[data & 0x0f]);
}

/** returns 1 if data is available in the specified ports buffer or 0 if none. */
unsigned char uartIsData(unsigned char uart)
{
  switch(uart)
    {
    case UART_CHAN4:
      if(uartChan4FifoRead != uartChan4FifoWrite)
	return 1;
      else
	return 0;
      break;
    default:
      return 0;
      break;
    }
}

/** returns a byte if there is data available or 0 if no data is available */
unsigned char uartGetData(unsigned char uart)
{
  unsigned char tempData;

  switch(uart)
    {
    case UART_CHAN0:
      if(uartChan0FifoRead != uartChan0FifoWrite)
	{ 
	  tempData = uartChan0Fifo[uartChan0FifoRead];
	  if(uartChan0FifoRead < UART_CHAN0_FIFO_LEN)
	    uartChan0FifoRead++;
	  else
	    uartChan0FifoRead = 0;
	  return tempData;
	}
      else
	return 0;
      break;
      
    default:
      return 0;
      break;
    }
}

ISR(USARTC0_RXC_vect)
{
  uartChan0Fifo[uartChan0FifoRead] = USARTC0_DATA;
  if(uartChan0FifoWrite < UART_CHAN0_FIFO_LEN)
    uartChan0FifoWrite++;
  else
    uartChan0FifoWrite = 0;
}
