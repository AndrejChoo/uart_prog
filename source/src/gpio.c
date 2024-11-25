/*
 * gpio.c
 *
 *  Created on: 21 нояб. 2024 г.
 *      Author: Andrej
 */

#include "gpio.h"


void gpio_init(void)
{
	PGC_DDR |= (1 << PGC_PIN);
	PGDI_DDR &= ~(1 << PGDI_PIN);
	PGDI_PORT |= (1 << PGDI_PIN);
	PGDO_DDR |= (1 << PGDO_PIN);
	MWCS_DDR |= (1 << MWCS_PIN);
}
