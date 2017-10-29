/**
 * \file hd44780.c
 *
 * HD44780 LCD driver
 *
 * (C)2014 CandraTech Ltd. All rights reserved
 *
 */

#include <avr/io.h>
#include "hd44780.h"
#include "uart.h"

static unsigned char curLine=1;

static void enDelay(void)
{
  unsigned int i;
  for(i=0; i < 10; i++)
      asm("nop");
}

static void hd44780WriteByte(unsigned char data)
{
  unsigned char i;

  /*Send high nibble*/
  if(data & (1 << 4)) HD44780_PORT_DATA |= (1 << HD44780_PIN_D4); else HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D4);
  if(data & (1 << 5)) HD44780_PORT_DATA |= (1 << HD44780_PIN_D5); else HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D5);
  if(data & (1 << 6)) HD44780_PORT_DATA |= (1 << HD44780_PIN_D6); else HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D6);
  if(data & (1 << 7)) HD44780_PORT_DATA |= (1 << HD44780_PIN_D7); else HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D7);

  HD44780_PORT_CTRL |= (1 << HD44780_PIN_E);
  enDelay();
  HD44780_PORT_CTRL &= ~(1 << HD44780_PIN_E);

  /*Send low nibble*/
  if(data & (1 << 0)) HD44780_PORT_DATA |= (1 << HD44780_PIN_D4); else HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D4);
  if(data & (1 << 1)) HD44780_PORT_DATA |= (1 << HD44780_PIN_D5); else HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D5);
  if(data & (1 << 2)) HD44780_PORT_DATA |= (1 << HD44780_PIN_D6); else HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D6);
  if(data & (1 << 3)) HD44780_PORT_DATA |= (1 << HD44780_PIN_D7); else HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D7);

  HD44780_PORT_CTRL |= (1 << HD44780_PIN_E);
  enDelay();
  HD44780_PORT_CTRL &= ~(1 << HD44780_PIN_E);

  for(i=0; i < 100; i++)
    enDelay();
}

static void hd44780WriteCmd(unsigned char data)
{
  HD44780_PORT_CTRL &= ~(1 << HD44780_PIN_RS); /*Clear RS for Commands*/
  hd44780WriteByte(data);
 }

static void hd44780WriteData(unsigned char data)
{
  HD44780_PORT_CTRL |= (1 << HD44780_PIN_RS);  /*Set RS for data*/
  hd44780WriteByte(data);
 }

/** Initialises the LCD control pins and the module itself.
 *
 */
void hd44780Init(void)
{
  unsigned char i;

  uartStr(UART_CHAN0, "hd44780Init...");

  /*We are using the display in read only mode, so we set
    all of the applicable pins as outputs*/
  HD44780_DIR_DATA |= (1 << HD44780_PIN_D7) | (1 << HD44780_PIN_D6) | (1 << HD44780_PIN_D5) | (1 << HD44780_PIN_D4);
  HD44780_DIR_CTRL |= (1 << HD44780_PIN_RS) | (1 << HD44780_PIN_E);

  HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D7) & ~(1 << HD44780_PIN_D6) & ~(1 << HD44780_PIN_D5) & ~(1 << HD44780_PIN_D4);
  HD44780_PORT_CTRL &= ~(1 << HD44780_PIN_RS) & ~(1 << HD44780_PIN_E);

  /*Initialise 4bit mode*/
  HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D7) & ~(1 << HD44780_PIN_D6) & ~(1 << HD44780_PIN_D5) & ~(1 << HD44780_PIN_D4);

  HD44780_PORT_DATA |= (1 << HD44780_PIN_D5) | (1 << HD44780_PIN_D4);
  HD44780_PORT_CTRL |= (1 << HD44780_PIN_E); /*Write 0x03 to high nibble*/
  enDelay();
  HD44780_PORT_CTRL &= ~(1 << HD44780_PIN_E);
  for(i=0; i < 100; i++)
    enDelay();

  HD44780_PORT_CTRL |= (1 << HD44780_PIN_E); /*Write 0x03 to high nibble (Data bits already set so we just toggle En)*/
  enDelay();
  HD44780_PORT_CTRL &= ~(1 << HD44780_PIN_E);
  for(i=0; i < 50; i++)
    enDelay();

  HD44780_PORT_CTRL |= (1 << HD44780_PIN_E); /*Write 0x03 to high nibble*/
  enDelay();
  HD44780_PORT_CTRL &= ~(1 << HD44780_PIN_E);
  for(i=0; i < 50; i++)
    enDelay();

  HD44780_PORT_DATA &= ~(1 << HD44780_PIN_D7) & ~(1 << HD44780_PIN_D6) & ~(1 << HD44780_PIN_D5) & ~(1 << HD44780_PIN_D4);
  HD44780_PORT_DATA |= (1 << HD44780_PIN_D5);
  HD44780_PORT_CTRL |= (1 << HD44780_PIN_E); /*Write 0x02 to high nibble*/
  enDelay();
  HD44780_PORT_CTRL &= ~(1 << HD44780_PIN_E);

  for(i=0; i < 100; i++)
    enDelay();


  hd44780WriteCmd(HD44780_CMD_SET_INTERFACE);
  hd44780WriteCmd(HD44780_CMD_EN_DISP);
  hd44780WriteCmd(HD44780_CMD_CLEAR_HOME);
  hd44780WriteCmd(HD44780_CMD_SET_CSR);
  hd44780WriteCmd(HD44780_CMD_TURN_ON_DISP);

  uartStr(UART_CHAN0, "Done.\r\n");
}


void hd44780SetLine(unsigned char line)
{
  switch(line)
    {
    case 1:
      hd44780WriteCmd(0x80); /*Move curser to beginning of line 1*/
      break;
    case 2:
      hd44780WriteCmd(0xC0); /*Move curser to beginning of line 2*/
      break;
    default:
      break;
    }
}

void hd44780ClearScreen(void)
{
  hd44780WriteCmd(HD44780_CMD_CLEAR_SCREEN);
}

/** Outputs a null terminated string to the LCD.
 */
void hd44780Str(char * str)
{
  while(*str != '\0')
    {
	hd44780WriteData((unsigned char)*str++);
    }

}
