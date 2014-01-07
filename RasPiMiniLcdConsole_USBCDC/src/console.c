/*
 Mini Console module for embedded microprocessors
 Author : Yasuhiro ISHII
 2013.12.31

 Semi-ESC support based on ISO/IEC 6429.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd_control.h"

#define CONSOLE_SIZE_X	21		// (Actually,21.333...)
#define CONSOLE_SIZE_Y	6

static unsigned char console_buffer_text[CONSOLE_SIZE_Y][CONSOLE_SIZE_X];
static unsigned char console_buffer_attr[CONSOLE_SIZE_Y][CONSOLE_SIZE_X];
static int cursor_x;
static int cursor_y;

static void console_Output1Line(char* str, int len);
static size_t console_findLineEnd(char* str);
static void console_LF();
static void console_CR();
static void console_update();
static char* console_processCodes(char* str);
static void console_cursorForward(int count);
static void console_cursorBackward(int count);

void CONSOLE_LocateCursor(int x, int y) {
	if ((x >= 0) && (x < CONSOLE_SIZE_X) && (y >= 0) && (y < CONSOLE_SIZE_Y)) {
		cursor_x = x;
		cursor_y = y;
	}
}

void CONSOLE_ClearAll() {
	memset(console_buffer_text, 0, sizeof(console_buffer_text));
	memset(console_buffer_text, 0, sizeof(console_buffer_attr));
	cursor_x = 0;
	cursor_y = 0;
}

void CONSOLE_Init() {
	CONSOLE_ClearAll();

	LCD_Init();
}

void console_ScrollUp() {
	int i;
	for (i = 1; i < CONSOLE_SIZE_Y; i++) {
		memcpy(console_buffer_text[i - 1], console_buffer_text[i],
				sizeof(console_buffer_text[0]));
	}
	memset(console_buffer_text[CONSOLE_SIZE_Y - 1], 0,
			sizeof(console_buffer_text[0]));
}

void CONSOLE_NewLine() {
	console_CR();
	console_LF();
	console_update();
}

static void console_CR() {
	cursor_x = 0;
}

static void console_LF() {
	if (cursor_y >= CONSOLE_SIZE_Y - 1) {
		cursor_y = CONSOLE_SIZE_Y - 1;
		console_ScrollUp();
	} else {
		cursor_y++;
	}
}

void CONSOLE_Output(char* str) {
	int len;
	int len_total;
	char* str_work;

	len_total = strlen(str);
	str_work = str;

	while (str_work < str + len_total) {
		len = console_findLineEnd(str_work);
		if (len > 0) {

			console_Output1Line(str_work, len);
			str_work += len;
		}
		str_work = console_processCodes(str_work);
	}
	console_update();
}

static void console_ESC_J(char* esc_param) {
	int p[1];
	sscanf(esc_param, "%d", &p[0]);

	if (p[0] == 2) {
		CONSOLE_ClearAll();
	}
}

// ESC[r;cH
static void console_ESC_H(char* esc_param) {
	int p[2];

	sscanf(esc_param, "%d;%d", &p[0], &p[1]);

	CONSOLE_LocateCursor(p[1], p[0]);
}

static void console_ESC_K(char* esc_param) {
	int p[1];
	sscanf(esc_param, "%d", &p[0]);

	// TODO: Implement later
}

static void console_ESC_A(char* esc_param) {
	int p[1];
	sscanf(esc_param, "%d", &p[0]);

	// TODO: Implement later
}

static void console_ESC_B(char* esc_param) {
	int p[1];
	sscanf(esc_param, "%d", &p[0]);

	// TODO: Implement later
}

static void console_ESC_C(char* esc_param) {
	int p[1];
	sscanf(esc_param, "%d", &p[0]);

	// TODO: Implement later
}

static void console_ESC_D(char* esc_param) {
	int p[1];
	sscanf(esc_param, "%d", &p[0]);

	// TODO: Implement later
}

static void console_ESC_m(char* esc_param) {

	// TODO: Implement later
}

static char* console_ESC(char* str) {
	char* str_ptr;
	char esc_param[64];
	char* esc_param_ptr;
	bool esc_complete;
	int count = 0;
	str_ptr = str;
	esc_param_ptr = esc_param;

	if (*str_ptr == '\x1b') {
		str_ptr++;
		if (*str_ptr == '[') {
			str_ptr++;
			esc_complete = false;
			while (esc_complete == false) {
				switch (*str_ptr) {
				case 'J':
					console_ESC_J(esc_param);
					esc_complete = true;
					break;
				case 'K':
					console_ESC_K(esc_param);
					esc_complete = true;
					break;
				case 'm':
					console_ESC_m(esc_param);
					esc_complete = true;
					break;
				case 'H':
					console_ESC_H(esc_param);
					esc_complete = true;
					break;
				case 'A':
					console_ESC_A(esc_param);
					esc_complete = true;
					break;
				case 'B':
					console_ESC_B(esc_param);
					esc_complete = true;
					break;
				case 'C':
					console_ESC_C(esc_param);
					esc_complete = true;
					break;
				case 'D':
					console_ESC_D(esc_param);
					esc_complete = true;
					break;
				default:
					*(esc_param_ptr++) = *str_ptr;
					*(esc_param_ptr + 1) = 0;
					count++;
					if (count > 64) {
						// tooooo long => may the data following from 0x1b is not valid ESC-seq?
						str_ptr = str + 1;
						esc_complete = true;
					}
					break;
				}
				str_ptr++;
			}
		}
	}

	return str_ptr;
}

static char* console_processCodes(char* str) {
	char val = *str;

	// If need to support more control codes,add here!

	while ((val == '\r') || (val == '\n') || (val == '\x1b')) {
		switch (val) {
		case '\r':
			// Currently,just skip it for \r
			str++;
			break;
		case '\n':
			str++;
			console_CR();
			console_LF();
			break;
		case '\x1b':
			//printf("****************************************!!!\n");
			str = console_ESC(str);
			break;
		case '\0':
			break;
		default:
			break;
		}
		val = *str;
	}

	return (str);
}

static size_t console_findLineEnd(char* str) {
	int len;
	int i;
	char val;

	len = strlen(str);
	i = 0;
	while (i < len) {
		val = *str;
		if ((val == '\n') || (val == '\r') || (val == '\x1b')) {
			break;
		}
		str++;
		i++;
	}

	return (i);
}

static void console_Output1Line(char* str, int len) {
	char* current_str;
	int remain;

	//printf("%s : str = [%s],len = %d\n",__func__,str,len);

	current_str = str;
	remain = len;

	while (current_str < str + len) {
		if (CONSOLE_SIZE_X - cursor_x < remain) {
			int size = CONSOLE_SIZE_X - cursor_x;
			memcpy(&(console_buffer_text[cursor_y][cursor_x]), current_str,
					size);
			current_str += size;
			cursor_x += size;
			remain -= size;
			console_CR();
			console_LF();
		} else {
			memcpy(&(console_buffer_text[cursor_y][cursor_x]), current_str,
					remain);
			current_str += remain;
			cursor_x += remain;
			remain = 0;
		}
	}
}

static void console_cursorForward(int count) {
	int i;

	if (count > CONSOLE_SIZE_X - cursor_x) {
		count -= CONSOLE_SIZE_X - cursor_x;
		cursor_x = 0;
		console_LF();

		if (count > 0) {
			for (i = 0; i < count / CONSOLE_SIZE_X; i++) {
				console_LF();
			}
			cursor_x += count % CONSOLE_SIZE_X;
		}

	} else {
		cursor_x += count;
	}

}

static void console_cursorBackward(int count) {
}

static void console_update() {
	int i;
	for (i = 0; i < CONSOLE_SIZE_Y; i++) {
		LCD_SetLocate(0, i);
		LCD_OutputStringBySize(console_buffer_text[i], CONSOLE_SIZE_X);
	}
}

#if 0

void disp_buff()
{
	int i,j;
	unsigned char val;

	printf("\x1b[42m=====================\x1b[m\n");
	for(i=0;i<CONSOLE_SIZE_Y;i++) {
		for(j=0;j<CONSOLE_SIZE_X;j++) {
			val = console_buffer_text[i][j];
			if(val == 0) {
				printf("\x1b[37m.\x1b[m");
			} else {
				printf("%c",val);
			}
		}
		printf("\n");
	}
	printf("\x1b[42m=====================\x1b[m\n");
	printf("cursor x,y=%d,%d\n",cursor_x,cursor_y);
}

int main(void)
{
	const char* str = "\x1b[2JMicrosoft MS-DOS Version 3.30B\nCopyright(C) 1990 Microsoft Corporation/NEC Corporation\nCommand prompt\nA>dir\nFile not found\nA>c:\nC>CLS\x1b[2JC>";
	int i;
	char s[10];

	CONSOLE_ClearAll();

	for(i=0;i<strlen(str);i++) {
		s[0] = str[i];
		s[1] = 0;
		CONSOLE_Output(s);
		disp_buff();
		usleep(10*1000);
	}

}
#endif
