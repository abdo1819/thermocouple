/**
 * \file uart.h
 *
 * \brief uart driver
 *
 * (C)2013 CandraTech Ltd. All rights reserved
 *
 */
void uartInit(unsigned char uart, unsigned char baud);
void uartTx(unsigned char uart, unsigned char data);
unsigned char uartRx(unsigned char uart);
void uartStr(unsigned char uart, char * str);
void uartHex16(unsigned char uart, unsigned int data);
void uartHex8(unsigned char uart, unsigned char data);
unsigned char uartIsData(unsigned char uart);
unsigned char uartGetData(unsigned char uart);

/** \name Uart channels
 *
 * The uart driver provides support for upto 5 uart channels
 *
 */
/**@{*/

#define UART_CHAN0 0 /**< \brief XMEGA USARTC0 */
#define UART_CHAN1 1 /**< \brief XMEGA USARTC1 */
#define UART_CHAN2 2 /**< \brief XMEGA USARTD0 */
#define UART_CHAN3 3 /**< \brief XMEGA USARTD1 */
#define UART_CHAN4 4 /**< \brief XMEGA USARTE0 */
/**@}*/

/** \name Baud rates
 *
 * Baud rate defines for use with the driver, note that the available baud rates depends
 * on thecurrent clock frequency. The current frequency is defined by \ref UP_CLK
 */
/**@{*/
#define UART_BAUD_2K4 0
#define UART_BAUD_4K8 1
#define UART_BAUD_9K6 2
#define UART_BAUD_14k4 3
#define UART_BAUD_19K2 4
#define UART_BAUD_28K8 5
#define UART_BAUD_38K4 6
#define UART_BAUD_57K6 7
#define UART_BAUD_76K8 8
#define UART_BAUD_115K2 9
#define UART_BAUD_230K4 10
#define UART_BAUD_460K8 11
#define UART_BAUD_921K6 12
#define UART_BAUD_1M382 13
#define UART_BAUD_2M 14
#define UART_BAUD_2M304 15
#define UART_BAUD_2M5 16
#define UART_BAUD_3M 17
#define UART_BAUD_4M 18
/**@}*/
