/*
 * spi.c
 *
 *  Created on: 20 мар. 2020 г.
 *      Author: andre
 */

#include "spi.h"

uint32_t sspi_delay=100;

void spi1_init(uint8_t speed, uint8_t mode)
{
	CS_DDR |= (1 << CS_PIN);
	DDRB |= (1 << 3) | (1 << 5);
	DDRB &= ~((1 << 4) | (1 << 2));
	PORTB |= (1 << 2);

	CS_DDR |= (1 << CS_PIN);

	SPCR = (1 << MSTR) | (1 << SPE);

	//SPSR |= 0x01; //Удваиваем скорость

	FLCS_HIGH
}

void spi1_write(uint8_t dat, uint8_t mode)
{
	SPDR = dat;
	while(!(SPSR & (1<<SPIF)));
}

uint8_t spi1_read(uint8_t dat, uint8_t mode)
{
	SPDR = dat;
	while(!(SPSR & (1 << 7))){ asm("nop"); };
	return SPDR;
}


