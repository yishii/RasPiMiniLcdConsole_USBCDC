/****************************************************************************
 *   $Id:: i2cslave.c 4059 2010-07-30 02:12:05Z usb00423                    $
 *   Project: NXP LPC11Uxx I2C Slave example
 *
 *   Description:
 *     This file contains I2C slave code example which include I2C slave 
 *     initialization, I2C slave interrupt handler, and APIs for I2C slave
 *     access.
*
****************************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.

* Permission to use, copy, modify, and distribute this software and its 
* documentation is hereby granted, under NXP Semiconductors' 
* relevant copyright in the software, without fee, provided that it 
* is used in conjunction with NXP Semiconductors microcontrollers.  This 
* copyright, permission, and disclaimer notice must appear in all copies of 
* this code.

****************************************************************************/

#include "LPC11Uxx.h"			/* LPC11xx Peripheral Registers */
#include "type.h"
#include "i2cslave.h"

volatile uint32_t I2CMasterState = I2C_IDLE;
volatile uint32_t I2CSlaveState = I2C_IDLE;

volatile uint32_t I2CMode;

volatile uint8_t I2CWrBuffer[BUFSIZE];
volatile uint8_t I2CRdBuffer[BUFSIZE];
volatile uint32_t I2CReadLength;
volatile uint32_t I2CWriteLength;

volatile uint32_t RdIndex = 0;
volatile uint32_t WrIndex = 0;

/* 
From device to device, the I2C communication protocol may vary, 
in the example below, the protocol uses repeated start to read data from or 
write to the device:
For master read: the sequence is: STA,Addr(W),offset,RE-STA,Addr(r),data...STO 
for master write: the sequence is: STA,Addr(W),offset,RE-STA,Addr(w),data...STO
Thus, in state 8, the address is always WRITE. in state 10, the address could 
be READ or WRITE depending on the I2C command.
*/   

/*****************************************************************************
** Function name:		I2C_IRQHandler
**
** Descriptions:		I2C interrupt handler, deal with master mode only.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
uint8_t StatValue;
#if 0
void I2C_IRQHandler(void) 
{
  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C->STAT;
  switch ( StatValue )
  {
	case 0x60:					/* An own SLA_W has been received. */
	case 0x70:
	RdIndex = 0;
	LPC_I2C->CONSET = I2CONSET_AA;	/* assert ACK after SLV_W is received */
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_WR_STARTED;
	break;
	
	case 0x80:					/*  data receive */
	case 0x90:
	if ( I2CSlaveState == I2C_WR_STARTED )
	{
	  I2CRdBuffer[RdIndex++] = LPC_I2C->DAT;
	  LPC_I2C->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  LPC_I2C->CONCLR = I2CONCLR_AAC;	/* assert NACK */
	}
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
		
	case 0xA8://確認済み					/* An own SLA_R has been received. */
	case 0xB0:
	//RdIndex = 0;//★
	WrIndex = I2CRdBuffer[0];	            /* The 1st byte is the index. */
	LPC_I2C->DAT = I2CRdBuffer[WrIndex+1];  /* write the same data back to master */
	WrIndex++;							    /* Need to skip the index byte in RdBuffer */
	LPC_I2C->CONSET = I2CONSET_AA;	        /* assert ACK after SLV_R is received */
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_RD_STARTED;
	break;
	
	case 0xB8:					/* Data byte has been transmitted */
	case 0xC8:
	if ( I2CSlaveState == I2C_RD_STARTED )
	{
	  LPC_I2C->DAT = I2CRdBuffer[WrIndex+1];/* write the same data back to master */
	  WrIndex++;							/* Need to skip the index byte in RdBuffer */
	  LPC_I2C->CONSET = I2CONSET_AA;		/* assert ACK  */
	}
	else
	{
	  LPC_I2C->CONCLR = I2CONCLR_AAC;		/* assert NACK  */
	}	
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;

	case 0xC0:					/* Data byte has been transmitted, NACK */
	LPC_I2C->CONCLR = I2CONCLR_AAC;			/* assert NACK  */
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = DATA_NACK;
	break;

	case 0xA0:					/* Stop condition or repeated start has */
	LPC_I2C->CONSET = I2CONSET_AA;	/* been received, assert ACK.  */
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_IDLE;
	break;

	default:
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	LPC_I2C->CONSET = I2CONSET_I2EN | I2CONSET_SI;	
	break;
  }
  return;
}
#else

int writePointer = 0;

void I2C_IRQHandler(void)
{
	StatValue = LPC_I2C->STAT;
	switch (StatValue) {
	case 0xa8:		// Own slave address and READ received
		writePointer = 0;
		LPC_I2C->DAT = I2CRdBuffer[writePointer];
		writePointer++;
		LPC_I2C->CONSET = I2CONSET_AA;
		LPC_I2C->CONCLR = I2CONCLR_SIC;
		I2CSlaveState = I2C_RD_STARTED;
		break;
	case 0xb0:
		while(1);
		break;
	case 0xb8:
		LPC_I2C->DAT = I2CRdBuffer[writePointer];
		writePointer++;
		LPC_I2C->CONSET = I2CONSET_AA;
		LPC_I2C->CONCLR = I2CONCLR_SIC;
		break;
	case 0xc0:
		LPC_I2C->CONSET = I2CONSET_AA;
		LPC_I2C->CONCLR = I2CONCLR_SIC;
		break;
	case 0xc8:
		while(1);
		break;
	case 0xa0:		// STOP or Repeated-START
		LPC_I2C->CONSET = I2CONSET_AA;
		LPC_I2C->CONCLR = I2CONCLR_SIC;
		break;
	default:
		while(1);
		break;
	}
}
#endif

/*****************************************************************************
** Function name:		I2CSlaveInit
**
** Descriptions:		Initialize I2C controller
**
** parameters:			I2c mode is either MASTER or SLAVE
** Returned value:		true or false, return false if the I2C
**				interrupt handler was not installed correctly
** 
*****************************************************************************/
void I2CSlaveInit( void ) 
{

  LPC_SYSCON->PRESETCTRL |= (0x1<<1);
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);
  LPC_IOCON->PIO0_4 &= ~0x3F;	/*  I2C I/O config */
  LPC_IOCON->PIO0_4 |= 0x01;		/* I2C SCL */
  LPC_IOCON->PIO0_5 &= ~0x3F;	
  LPC_IOCON->PIO0_5 |= 0x01;		/* I2C SDA */
//  LPC_IOCON->PIO0_4 |= (0x1<<10);	/* open drain pins */
//  LPC_IOCON->PIO0_5 |= (0x1<<10);	/* open drain pins */

  /*--- Clear flags ---*/
  LPC_I2C->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;    

  /*--- Reset registers ---*/
#if FAST_MODE_PLUS
  LPC_IOCON->PIO0_4 |= (0x1<<9);
  LPC_IOCON->PIO0_5 |= (0x1<<9);
  LPC_I2C->SCLL   = I2SCLL_HS_SCLL;
  LPC_I2C->SCLH   = I2SCLH_HS_SCLH;
#else
  LPC_I2C->SCLL   = I2SCLL_SCLL;
  LPC_I2C->SCLH   = I2SCLH_SCLH;
#endif

  LPC_I2C->ADR0 = PCF8594_ADDR;    
  I2CSlaveState = I2C_IDLE;
  
  /* Enable the I2C Interrupt */
  NVIC_EnableIRQ(I2C_IRQn);

  LPC_I2C->CONSET = I2CONSET_I2EN | I2CONSET_SI;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

