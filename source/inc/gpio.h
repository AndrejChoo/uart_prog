/*
 * gpio.h
 *
 *  Created on: 21 нояб. 2024 г.
 *      Author: Andrej
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <avr/io.h>

#define PGDI_PORT			PORTC
#define PGDO_PORT			PORTC
#define PGC_PORT			PORTC
#define MWCS_PORT			PORTC
#define PGDI_DDR			DDRC
#define PGDO_DDR			DDRC
#define PGC_DDR				DDRC
#define MWCS_DDR			DDRC
#define MWCS_PIN			0
#define PGDI_PIN			1
#define PGDO_PIN			2
#define PGC_PIN				3
#define PGDI_DIN			PINC
#define PGD_READ			PGDI_DIN & (1 << PGDI_PIN)



#define     PGDO_HIGH      	PGDO_PORT |= (1 << PGDO_PIN);
#define     PGDO_LOW       	PGDO_PORT &= ~(1 << PGDO_PIN);
#define     PGC_HIGH      	PGC_PORT |= (1 << PGC_PIN);
#define     PGC_LOW       	PGC_PORT &= ~(1 << PGC_PIN);
#define     MWCS_HIGH      	MWCS_PORT |= (1 << MWCS_PIN);
#define     MWCS_LOW       	MWCS_PORT &= ~(1 << MWCS_PIN);



void gpio_init(void);

#endif /* INC_GPIO_H_ */
