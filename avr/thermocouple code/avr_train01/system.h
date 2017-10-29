/**
 * \file system.h
 *
 * \brief application header file for P129-002
 *
 * (C)2013 Orcalight Ltd. All rights reserved
 *
 */

#define UP_CLK 2000000 /**< Defines the application clock speed in Hz*/
#define SYS_DEBUG_UART UART_CHAN0 /**< Defines the UART to be used for debug info */
#define DEBUG_LEVEL DEBUG_LEVEL_1 /**< Defines the current debug level. See debug.h */

#define SPI_SCK_DDR 
#define PORTC_DIR
#define SPI_SCK_PIN 7

#define MAX6675_CH1_CS_DIR PORTB_DIR
#define MAX6675_CH1_CS_PORT PORTB_OUT
#define MAX6675_CH1_CS_PIN 3
