/**
 * \file hd44780.c
 *
 * HD44780 LCD driver
 *
 * (C)2014 CandraTech Ltd. All rights reserved
 *
 */
#define HD44780_PORT_DATA PORTD_OUT
#define HD44780_DIR_DATA  PORTD_DIR
#define HD44780_PORT_CTRL PORTC_OUT
#define HD44780_DIR_CTRL  PORTC_DIR
#define HD44780_PIN_RS 1
#define HD44780_PIN_E 0
#define HD44780_PIN_D4 0
#define HD44780_PIN_D5 1
#define HD44780_PIN_D6 2
#define HD44780_PIN_D7 3

#define HD44780_CMD_SET_INTERFACE 0x28
#define HD44780_CMD_EN_DISP 0x0A
//#define HD44780_CMD_EN_DISP 0x08
#define HD44780_CMD_CLEAR_HOME 0x01
#define HD44780_CMD_SET_CSR 0x06
#define HD44780_CMD_TURN_ON_DISP 0x0C
#define HD44780_CMD_CLEAR_SCREEN 0x01

void hd44780Init(void);
void hd44780Str(char * str);
void hd44780ClearScreen(void);
void hd44780SetLine(unsigned char line);
