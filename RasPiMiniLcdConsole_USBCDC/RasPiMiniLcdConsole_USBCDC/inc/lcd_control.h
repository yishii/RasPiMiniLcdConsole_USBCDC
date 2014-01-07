/*
 * Author : Yasuhiro ISHII
 */

#ifndef __LCD_CONTROL_H__
#define __LCD_CONTROL_H__

void LCD_Init();
void LCD_OutputString(unsigned char* str);
void LCD_Clear();
void LCD_SetLocate(int column,int row);
void LCD_OutputStringBySize(unsigned char* str,int size);

#endif /* __LCD_CONTROL_H__ */
