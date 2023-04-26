/*************************************************************************
	74HC595
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License     
Hardware: 74HC595
Date: 25102020
Comment:
	Tested Atemga88 8Mhz and Atmega328 8Mhz
************************************************************************/
/*** File Library ***/
#include "74hc595.h"

/*** File Constant & Macro ***/

/*** File Variable ***/
volatile uint8_t *hc595_DDR;
volatile uint8_t *hc595_PORT;
uint8_t HC595_datapin;
uint8_t HC595_clkpin; 
uint8_t HC595_outpin;

/*** File Header ***/
void HC595_shift_bit(uint8_t bool);
void HC595_shift_ibyte(uint8_t byte);
void HC595_shift_byte(uint8_t byte);
void HC595_shift_out(void);

/*** Procedure & Function ***/
HC595 HC595enable(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t datapin, uint8_t clkpin, uint8_t outpin)
{
	// LOCAL VARIABLES
	// ALLOCA��O MEMORIA PARA Estrutura
	HC595 hc595;
	// import parametros
	hc595_DDR = ddr;
	hc595_PORT = port;
	HC595_datapin = datapin;
	HC595_clkpin = clkpin;
	HC595_outpin = outpin;
	// inic variables
    *hc595_DDR |= (1 << datapin) | (1 << clkpin) | (1 << outpin);
	*hc595_PORT &= ~((1<<datapin) | (1<<clkpin) | (1 << outpin));
	// Direccionar apontadores para PROTOTIPOS
	hc595.bit = HC595_shift_bit;
	hc595.ibyte = HC595_shift_ibyte;
	hc595.byte = HC595_shift_byte;
	hc595.out = HC595_shift_out;
	
	return hc595;
}
void HC595_shift_bit(uint8_t bool)
{
	if (bool)
		*hc595_PORT |= (1 << HC595_datapin); // Data bit HIGH
	else
		*hc595_PORT &= ~(1 << HC595_datapin); // Data bit LOW
	*hc595_PORT |= (1 << HC595_clkpin); // Shift bit
	*hc595_PORT &= ~(1 << HC595_clkpin); // Shift disable
}
void HC595_shift_ibyte(uint8_t byte)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
		HC595_shift_bit(byte & (1 << i));
	HC595_shift_out();
}
void HC595_shift_byte(uint8_t byte)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
		HC595_shift_bit(byte & (1 << (7 - i)));
	HC595_shift_out();
}
void HC595_shift_out(void)
{
	*hc595_PORT |= (1<<HC595_outpin); // Output enable
	*hc595_PORT &= ~(1<<HC595_outpin); // Output disable
}

/***File Interrupt***/

/***EOF***/

