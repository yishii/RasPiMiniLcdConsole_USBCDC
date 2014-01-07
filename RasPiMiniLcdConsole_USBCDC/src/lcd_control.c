/*
 * LCD Control Main
 *
 * Author : Yasuhiro ISHII
 */

#include "LPC11Uxx.h"
#include <cr_section_macros.h>
#include "LPC11Uxx.h"
#include <NXP/crp.h>
#include "systick.h"
#include <stdbool.h>
#include "lcd_control.h"
#include "gpio.h"
#include "7x5fonts.h"

static void lcd_setsclk(bool data);
static void lcd_sendData(bool rs, unsigned char data);
static void lcd_setStartAddress(int address);

inline void lcd_setce(bool data)
{
	GPIOSetBitValue(1, 19, data == true ? 1 : 0);
}

void LCD_Init()
{
	GPIOSetDir(1, 19, 1);
	GPIOSetDir(1, 20, 1);
	GPIOSetDir(1, 22, 1);
	GPIOSetDir(1, 24, 1);

	GPIOSetDir(1, 21, 1);	// LCD_RESET

	wait_ms(50);

	GPIOSetBitValue(1, 21, 0);
	wait_ms(50);
	GPIOSetBitValue(1, 21, 1);
	wait_ms(50);

	lcd_setce(true);
	lcd_setsclk(true);

	lcd_sendData(false, 0xae);
	lcd_sendData(false, 0xa0);
	lcd_sendData(false, 0xc8);
	lcd_sendData(false, 0xa3);
	lcd_sendData(false, 0x2c);
	wait_ms(2);
	lcd_sendData(false, 0x2e);
	wait_ms(2);
	lcd_sendData(false, 0x2f);

	lcd_sendData(false, 0x23);
	lcd_sendData(false, 0x81);
	lcd_sendData(false, 0x1c);

	lcd_sendData(false, 0xa4);
	lcd_sendData(false, 0x40);
	lcd_sendData(false, 0xa6);
	lcd_sendData(false, 0xaf);

	lcd_sendData(false, 0xb0);		// Page address set to 0
	lcd_sendData(false, 0x40 | 0);	// Display start address set to 0

	LCD_Clear();
}

static void lcd_setsclk(bool data)
{
	GPIOSetBitValue(1, 20, data == true ? 1 : 0);
}
static void lcd_setmosi(bool data) {
	GPIOSetBitValue(1, 22, data == true ? 1 : 0);
}
static void lcd_setrs(bool data) {
	GPIOSetBitValue(1, 24, data == true ? 1 : 0);
}

static void lcd_sendData(bool rs, unsigned char data) {
	int i;

	lcd_setce(false);
	lcd_setrs(rs);
	for (i = 0; i <= 7; i++) {
		lcd_setsclk(false);
		lcd_setmosi((data >> (7 - i)) & 0x01 ? true : false);
		lcd_setsclk(true);
	}
	lcd_setce(true);
}

static void outputOnLcd(unsigned char c)
{
	if((c < 0x20) || (c > 0x7f)){
		c = 0x20;
	}
	lcd_sendData(true,font_5x7[(c - 0x20)*5 + 0]);
	lcd_sendData(true,font_5x7[(c - 0x20)*5 + 1]);
	lcd_sendData(true,font_5x7[(c - 0x20)*5 + 2]);
	lcd_sendData(true,font_5x7[(c - 0x20)*5 + 3]);
	lcd_sendData(true,font_5x7[(c - 0x20)*5 + 4]);
	lcd_sendData(true,0x00);
}

static void lcd_setPage(int page)
{
	lcd_sendData(false, 0xb0 | page);
}

static void lcd_setStartAddress(int address)
{
	lcd_sendData(false, 0x10 | ((address >> 4) & 0x0f));
	lcd_sendData(false, 0x00 | (address & 0x0f));
}

void LCD_SetLocate(int column,int row)
{
	lcd_setPage(row);
	lcd_setStartAddress(column * 6);
}

void LCD_OutputString(unsigned char* str)
{
	while(*str){
		outputOnLcd(*str);
		str++;
	}
}

void LCD_OutputStringBySize(unsigned char* str,int size)
{
	int i;
	for(i=0;i<size;i++){
		outputOnLcd(*str);
		str++;
	}
}

void LCD_Clear()
{
	int column,page;
	for(page=0;page<6;page++){
		lcd_setPage(page);
		lcd_setStartAddress(0);
		for(column=0;column<128;column++){
			lcd_sendData(true,0);
		}
	}
	lcd_setPage(0);
	lcd_setStartAddress(0);
}
