/*
 * spi.h
 *
 *  Created on: 20 мар. 2020 г.
 *      Author: andre
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#define CS_PORT		PORTB
#define CS_PIN		1
#define CS_DDR		DDRB
#define FLCS_LOW	CS_PORT &= ~(1 << CS_PIN);
#define FLCS_HIGH	CS_PORT |= (1 << CS_PIN);


void spi1_init(uint8_t, uint8_t);
void spi2_init(char);
void spi1_write(uint8_t, uint8_t mode);
uint8_t spi1_read(uint8_t, uint8_t mode);

#endif /* SPI_H_ */
