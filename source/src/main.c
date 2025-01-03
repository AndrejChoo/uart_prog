/*
 * main.c
 *
 *  Created on: 9 ����. 2022 �.
 *      Author: Andrej
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart.h"
#include "spi.h"
#include "progger.h"
#include "gpio.h"

uint8_t exchange[150];
uint8_t rx_counter = 0;
uint8_t full_buff = 0; //����, �����������, ��� ������� ������ ��������
uint8_t packet_size = 0;
uint8_t main_buff[256];
volatile uint8_t nxt = 0;


ISR(USART_RX_vect)
{
	if(!(UCSR0A & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))))
	{
		exchange[rx_counter] = UDR0;
		rx_counter++;
		if(rx_counter == 3) {packet_size = exchange[1];}
		if((packet_size > 0) && (rx_counter == packet_size + 3))
		{
			rx_counter = 0;
			packet_size = 0;
			if(exchange[2] == 0x3D) {nxt = 1; return;}
			full_buff = 1;
		}
	}
}


int main(void)
{
	gpio_init();
	usart_init();
	spi1_init(0, 0);
	i2c1_init(0);

	MWCS_LOW
	PGDO_LOW
	PGC_LOW


	sei();

	while(1)
	{
		if(full_buff)
		{
			deassemble_frame();
			full_buff = 0;
		}
		asm(" ");
	}
}
