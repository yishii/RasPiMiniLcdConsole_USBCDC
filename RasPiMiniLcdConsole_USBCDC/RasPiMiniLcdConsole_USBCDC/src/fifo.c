/*
 * FIFO Library
 * Author : Yasuhiro ISHII
 */

#include "fifo.h"

/*
  Arduino Library : Buffered <Byte> Stream
  Author : Yasuhiro ISHII 2011 for Arduino platform
*/

/*
        リングバッファコントローラークラス2 for R8C/Tiny
        Copyright(C) 2003 Yasuhiro ISHII
        All rights reserved.
*/

static unsigned char* buff;
static signed int BUF_SIZE;
static int datasize;
static signed int s_ptr;
static signed int e_ptr;

int FIFO_Init(void* buffer,int size_in_bytes){
    buff = (unsigned char*)buffer;
    BUF_SIZE = size_in_bytes;
    datasize = 0;
    s_ptr = 0;
    e_ptr = 0;
    return(1);
}

int FIFO_GetSize(void){
    return (datasize);
}

int FIFO_GetTotalSize(void){
    return (BUF_SIZE);
}

int FIFO_Push(unsigned char data){
    if (datasize < BUF_SIZE){
        buff[s_ptr] = data;
        s_ptr = (s_ptr + 1) % BUF_SIZE;
        datasize++;
        return(1);
    } else {
        return(0);
    }
}

int FIFO_Pop(unsigned char* data){
    if (datasize){
        *data = buff[e_ptr];
        e_ptr = (e_ptr + 1) % BUF_SIZE;
        datasize--;
        return(1);
    } else {
        return(0);
    }
}

void FIFO_Flush(void){
    datasize = 0;
    s_ptr = 0;
    e_ptr = 0;
}
