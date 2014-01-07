/*
 * FIFO Library
 * Author : Yasuhiro ISHII
 */

#ifndef __FIFO_H__
#define __FIFO_H__

int FIFO_Init(void* buffer,int size_in_bytes);
int FIFO_GetSize(void);
int FIFO_GetTotalSize(void);
int FIFO_Push(unsigned char data);
int FIFO_Pop(unsigned char* data);
void FIFO_Flush(void);

#endif /* __FIFO_H__ */
