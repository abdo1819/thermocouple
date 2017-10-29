/**
 * \file debug.h
 *
 * \brief Contains macros and definitions to aid with debugging
 *
 * (C)2013 CandraTech Ltd. All rights reserved
 *
 */

#include "system.h"
#include "uart.h"

/**
 * \def DEBUG_STR(str, level)
 *
 * DEBUG_STR outputs the given string on the debug port assuming the given level is 
 * less than or equal to the current DEBUG_LEVEL
 */

/**
 * \def DEBUG_TX(data, level)
 *
 * DEBUG_TX outputs a single charactor on the debug port assuming the given level is 
 * less than or equal to the current DEBUG_LEVEL
 */

/**
 * \def DEBUG_HEX16(data, level)
 *
 * DEBUG_HEX16 outputs a 16bit hex value on the debug port assuming the given level is 
 * less than or equal to the current DEBUG_LEVEL
 */

/**
 * \def DEBUG_HEX8(data, level)
 *
 * DEBUG_STR outputs an 8bit hex value on the debug port assuming the given level is 
 * less than or equal to the current DEBUG_LEVEL
 */

/** \name Debug Levels
 * Various debug levels are available, DEBUG_LEVEL_0 provides the least information, while
 * DEBUG_LEVEL_9 provides the most.
 *
 * Note that the higher the debug level, the larger the code generated.
 *
 * Generally make clean needs to be run when changing DEBUG_LEVEL in system.h
 *
 * DEBUG_LEVEL_0 is the default debug level, it is generally used for application signon
 * and general progress such as device driver initialisation, reporting of serial numbers
 * at boot time etc. As such it is defined as being used for general information as opposed to
 * debugging information per se.
 *
 * DEBUG_LEVEL_1 provides general system information, such as constants, supply voltages etc.
 *
 * DEBUG_LEVEL_2 is used for high level program flow control. Each function should sign on
 * and off at this level.
 *
 * DEBUG_LEVEL_5 is used for device driver program flow control. Each device driver function
 * should sign on and off at this level.
 *
 */
/**@{*/
#define DEBUG_LEVEL_0 0 
#define DEBUG_LEVEL_1 1 
#define DEBUG_LEVEL_2 2
#define DEBUG_LEVEL_3 3 
#define DEBUG_LEVEL_4 4 
#define DEBUG_LEVEL_5 5 
#define DEBUG_LEVEL_6 6 
#define DEBUG_LEVEL_7 7 
#define DEBUG_LEVEL_8 8 
#define DEBUG_LEVEL_9 9
/**@}*/

#ifndef DEBUG_LEVEL /*Default to level 0 if not defined*/
#define DEBUG_LEVEL DEBUG_LEVEL_0
#endif

#define DEBUG_STR(str, level) if(level <= DEBUG_LEVEL)uartStr(SYS_DEBUG_UART, str); else
#define DEBUG_TX(data, level) if(level <= DEBUG_LEVEL)uartTx(SYS_DEBUG_UART, data); else
#define DEBUG_HEX16(data, level) if(level <= DEBUG_LEVEL)uartHex16(SYS_DEBUG_UART, data); else
#define DEBUG_HEX8(data, level) if(level <= DEBUG_LEVEL)uartHex8(SYS_DEBUG_UART, data); else
