/*
 * progger.c
 *
 *  Created on: 19 ���. 2020 �.
 *      Author: andre
 */

#include "progger.h"

extern uint8_t exchange[];
extern uint8_t main_buff[];
extern volatile uint8_t nxt;

uint32_t f_size;
uint16_t f_psize;
uint8_t f_type;
uint32_t ee_offset;
uint16_t block;

//Microwire
uint8_t mw_addsize;
uint16_t mw_size;

#define mw_freq			20

//�������� ������ �� ������
void send_errorFrame(void)
{

}

void send_successConn(void)
{
	exchange[0] = 0xFE;
	exchange[1] = 0x01;
	exchange[2] = 0xCC;
	exchange[3] = 0x00;
	send_frame(exchange, 4);
}

void send_frame(uint8_t *buff, uint8_t count)
{
	for(int n = 0; n < count; n++) USARTSend_char(buff[n]);
}

//
void send_arr(uint8_t marker, uint8_t *buff, uint16_t count, uint16_t offset)
{
	USARTSend_char(0xFE); //Start
	USARTSend_char(count);
	USARTSend_char(marker);
	for(int u = 0; u < count; u++) USARTSend_char(buff[u + offset]);
}

void deassemble_frame(void)
{
	switch(exchange[2])
	{
		case 0xCC:
		{
			send_successConn();
			break;
		}

		//������ EEPROM
		case 0xE0://������ EEPROM
		{
			f_size = exchange[4] | (exchange[3]<<8);
			read_eeprom();
			break;
		}

		case 0xE1://���������� � ������ EEPROM
		{
			f_size = exchange[4] | (exchange[3]<<8);
			ee_offset = 0;

			exchange[0] = 0xFE;
			exchange[1] = 0x01;
			exchange[2] = 0xE2;
			exchange[3] = 0x00;
			send_frame(exchange, 4);
			break;
		}

		case 0xE2://����� ��� ������ � EEPROM
		{
			write_eeprom();
			break;
		}
		///////////////////////////Microwire//////////////////////////
		case 0xB0://Read EEPROM
		{
			mw_size = exchange[4] | (exchange[3]<<8);

			switch(mw_size)
			{
				case 128: {mw_addsize = 6; break;}
				case 256:
				{
					if(exchange[5] == 0x00) mw_addsize = 8;
					else mw_addsize = 7;
					break;
				}
				case 512: {mw_addsize = 8; break;}
				case 1024: {mw_addsize = 10; break;}
				case 2048: {mw_addsize = 10; break;}
			}

			read_mw();
			break;
		}

		case 0xB1://���������� � ������ EEPROM
		{
			mw_size = exchange[4] | (exchange[3] << 8);

			switch(mw_size)
			{
				case 128: {mw_addsize = 6; break;}
				case 256:
				{
					if(exchange[5] == 0x00) mw_addsize = 8;
					else mw_addsize = 7;
					break;
				}
				case 512: {mw_addsize = 8; break;}
				case 1024: {mw_addsize = 10; break;}
				case 2048: {mw_addsize = 10; break;}
			}

			mw_emptyCmd(mw_addsize, MW_WEN);

			exchange[0] = 0xFE;
			exchange[1] = 0x01;
			exchange[2] = 0xB2;
			exchange[3] = 0x00;
			send_frame(exchange, 4);
			break;
		}

		case 0xB2://����� ��� ������ � EEPROM
		{
			write_mw();
			break;
		}
		case 0xBC: //Erase
		{
			mw_size = exchange[4] | (exchange[3] << 8);

			switch(mw_size)
			{
				case 128: {mw_addsize = 6; break;}
				case 256:
				{
					if(exchange[5] == 0x00) mw_addsize = 8;
					else mw_addsize = 7;
					break;
				}
				case 512: {mw_addsize = 8; break;}
				case 1024: {mw_addsize = 10; break;}
				case 2048: {mw_addsize = 10; break;}
			}

			mw_emptyCmd(mw_addsize, MW_WEN);
			mw_emptyCmd(mw_addsize, MW_ERAL);
			_delay_us(100);
			while(mw_waitBsy());
			mw_emptyCmd(mw_addsize, MW_WDIS);

			exchange[0] = 0xFE;
			exchange[1] = 0x01;
			exchange[2] = 0xBC;
			exchange[3] = 0x00;
			send_frame(exchange, 4);

			break;
		}

		//*************************SPI FLASH************************
		case 0xF0:
		{
			uint8_t temp_reg1 = 0, temp_reg2 = 0, temp_reg3 = 0;

			FLCS_LOW
			spi1_read(0x9F, 0);
			temp_reg3 = spi1_read(0x00, 0);
			temp_reg1 = spi1_read(0x00, 0);
			temp_reg2 = spi1_read(0x00, 0);
			FLCS_HIGH

			exchange[0] = 0xFE;
			exchange[1] = 0x03;
			exchange[2] = 0xF0;
			exchange[3] = temp_reg1;
			exchange[4] = temp_reg2;
			exchange[5] = temp_reg3;
			send_frame(exchange, 6);

			break;
		}
		case 0xF1:
		{
			uint8_t temp_reg1 = 0, temp_reg2 = 0;

			FLCS_LOW
			spi1_read(0x05, 0);
			temp_reg1 = spi1_read(0x00, 0);
			FLCS_HIGH

			FLCS_LOW
			spi1_read(0x35, 0);
			temp_reg2 = spi1_read(0x00, 0);
			FLCS_HIGH

			exchange[0] = 0xFE;
			exchange[1] = 0x02;
			exchange[2] = 0xF1;
			exchange[3] = temp_reg1;
			exchange[4] = temp_reg2;
			send_frame(exchange, 5);

			break;
		}
		case 0xF2:
		{
			uint32_t tmp_add;
			//[32:24]
			f_size = (exchange[3] << 8);
			f_size = f_size << 8;
			f_size = f_size << 8;
			//[23:16]
			tmp_add = (exchange[4] << 8);
			tmp_add = tmp_add << 8;
			f_size |= tmp_add;
			//[15:0]
			f_size |= (exchange[5] << 8) | exchange[6];

			read_flash();
			break;
		}

		case 0xF3:
		{
			uint8_t hSreg = exchange[3];
			uint8_t lSreg = exchange[4];

			FLCS_LOW
			spi1_read(0x50, 0);
			FLCS_HIGH

			while(!(read_sreg1() & (1 << 1)));

			FLCS_LOW
			spi1_read(0x01, 0);
			spi1_read(lSreg, 0);
			spi1_read(hSreg, 0);
			FLCS_HIGH

			FLCS_LOW
			spi1_read(0x04, 0);
			FLCS_HIGH

			exchange[0] = 0xFE;
			exchange[1] = 0x01;
			exchange[2] = 0xF3;
			exchange[3] = 0x00;
			send_frame(exchange, 4);

			break;
		}
		case 0xF4:
		{
			FLCS_LOW
			spi1_read(0x06, 0); //Write enable
			FLCS_HIGH

			while(!(read_sreg1() & (1 << 1)));

			FLCS_LOW
			spi1_write(0xC7, 0); //Erase
			FLCS_HIGH

			while(!(read_sreg1() & (1 << 1)));

			exchange[0] = 0xFE;
			exchange[1] = 0x01;
			exchange[2] = 0xF4;
			exchange[3] = 0x00;
			send_frame(exchange, 4);

			break;
		}
		case 0xF5:
		{
			f_psize = (exchange[3] << 8) | exchange[4];
			f_type = exchange[5];
			block = 0;
			ee_offset = 0;

			exchange[0] = 0xFE;
			exchange[1] = 0x01;
			exchange[2] = 0xF6;
			exchange[3] = 0x00;
			send_frame(exchange, 4);
			break;
		}
		case 0xF6:
		{
			write_flash();
			break;
		}

		default:
		{
			break;
		}
	}
}


//**********************************I2C EEPROM*************************************
void read_eeprom(void)
{
	if(f_size == 128) //24c01, 24c02
	{
		eeprom_read_arr(0xA0, 1, 0, main_buff, f_size);
		for(int i = 0; i < f_size; i+= 128) send_arr(0xE0, main_buff, 128, i);
	}
	else if(f_size == 256) //24c01, 24c02
	{
		eeprom_read_arr(0xA0, 1, 0, main_buff, f_size);
		for(int i = 0; i < f_size; i+= 128)
			{
				send_arr(0xE0, main_buff, 128, i);
				_delay_ms(5);
			}
	}
	else if(f_size > 256 && f_size <= 2048) //24c04, 24c08, 24c16
	{
		for(int i = 0; i < f_size; i+= 128)
		{
			eeprom_read_arr((0xA0 | ((i >> 7) & 0x0E)), 1, i & 0xFF, main_buff, 128);
			send_arr(0xE0, main_buff, 128, 0);
			_delay_ms(5);
		}
	}
	else
	{
		for(int i = 0; i < f_size; i+= 128)
		{
			eeprom_read_arr(0xA0, 2, i, main_buff, 128);
			send_arr(0xE0, main_buff, 128, 0);
			_delay_ms(5);
		}
	}
}

void write_eeprom(void)
{
	uint16_t offs = (exchange[3] << 8) | exchange[4];

	if(f_size <= 256) //24c01, 24c02 8-�������� ��������
	{
		for(int k = 0; k < 32; k+= 8)
		{
			eeprom_write_arr(0xA0, k + offs, 1, exchange, 8, k + 5);
			_delay_ms(10);
		}
	}
	else if(f_size > 256 && f_size <= 2048) // 16-�������� ��������
	{
		uint8_t dop_add;

		for(int k = 0; k < 32; k+= 16)
		{
			dop_add = ((offs + k) >> 7) & 0x0E;
			eeprom_write_arr( (0xA0 | dop_add), ((k + offs) & 0xFF), 1, exchange, 16, k + 5);
			_delay_ms(15);
		}
	}
	else
	{
		eeprom_write_arr(0xA0, offs, 2, exchange, 32, 5);
		_delay_ms(25);
	}

	exchange[0] = 0xFE;
	exchange[1] = 0x01;
	exchange[2] = 0xE2;
	exchange[3] = 0x00;
	send_frame(exchange, 4);
}


//*********************************SPI FLASH********************************
//������ SREG1
uint8_t read_sreg1(void)
{
	uint8_t tmp;
	FLCS_LOW
	spi1_read(0x05, 0);
	tmp = spi1_read(0x00, 0);
	FLCS_HIGH
	return tmp;
}

void read_flash(void)
{
	FLCS_LOW
	if(f_size <= 0x1000000)
	{
		spi1_read(0x03, 0);
		spi1_read(0x00, 0);
		spi1_read(0x00, 0);
		spi1_read(0x00, 0);
	}
	else
	{
		spi1_read(0x33, 0);
		spi1_read(0x00, 0);
		spi1_read(0x00, 0);
		spi1_read(0x00, 0);
		spi1_read(0x00, 0);
	}

	for(uint32_t i = 0; i < f_size; i += 128)
	{

		for(int k = 0; k < 128; k++) main_buff[k] = spi1_read(0x03, 0);
		send_arr(0xF2, main_buff, 128, 0);

		while(!nxt);
		nxt = 0x00;

	}
	FLCS_HIGH
}

void write_flash(void)
{
	uint32_t tmp;

	for(int i = 0; i < exchange[1]; i++) main_buff[i + block] = exchange[i + 3];
	block += exchange[1];
	ee_offset += exchange[1];
	if(block == f_psize)
	{
		tmp = ee_offset - f_psize; //����� ����� ��� ������

		FLCS_LOW
		spi1_read(0x06, 0);
		FLCS_HIGH
		while(!(read_sreg1() & (1 << 1)));

		FLCS_LOW
		spi1_read(0x02, 0);
		if(f_type == 2) spi1_read((tmp >> 24), 0);
		spi1_read(((tmp >> 16)) & 0xFF, 0);
		spi1_read(((tmp >> 8) & 0xFF), 0);
		spi1_read((tmp & 0xFF), 0);
		for(int k = 0; k < f_psize; k++) spi1_read(main_buff[k], 0);
		FLCS_HIGH

		while((read_sreg1() & 0x01) == 0x01); //bit BSY

		block = 0;
	}
	exchange[0] = 0xFE;
	exchange[1] = 0x01;
	exchange[2] = 0xF6;
	exchange[3] = 0x00;
	send_frame(exchange, 4);
}

//*********************************Microwire********************************

void read_mw(void)
{
	uint16_t data;

	for(int j = 0; j < mw_size; j+= 128)
	{
		for(int i = 0; i < 64; i++)
		{
			data = mw_readCmd(mw_addsize, i + j / 2);
			main_buff[i * 2] = data & 0xFF;
			main_buff[(i * 2) + 1] = (data >> 8) & 0xFF;
		}

		send_arr(0xB0, main_buff, 128, 0);

		while(!nxt);
		nxt = 0x00;
	}
}

void write_mw(void)
{
	uint16_t offs = (exchange[3] << 8) | exchange[4];

	//mw_emptyCmd(mw_addsize, MW_WEN);

	for(int i = 0; i < 16; i++)
	{
		mw_writeCmd(mw_addsize, offs/2+i, (exchange[2*i+5]|(exchange[2*i+6]<<8)));
		while(mw_waitBsy());
		_delay_ms(15);
	}

	//mw_emptyCmd(mw_addsize, MW_WDIS);

	exchange[0] = 0xFE;
	exchange[1] = 0x01;
	exchange[2] = 0xB2;
	exchange[3] = 0x00;
	send_frame(exchange, 4);
}

uint16_t mw_readCmd(uint8_t width, uint16_t add)
{
	uint16_t tadd, tdat = 0;
	tadd = (add << 1) | (0x06 << (width + 1));

	MWCS_HIGH
	_delay_us(mw_freq);

	//Отправляем комманду чтения + адресс + бит ожидания
	for(int i = 0; i < (width + 4); i++)
	{
		if(tadd & (1 << (width + 3 - i))) PGDO_HIGH
		else PGDO_LOW
		_delay_us(mw_freq);
		PGC_HIGH
		_delay_us(mw_freq);
		PGC_LOW
	}

	//Читаем 16 битное слово
	for(int i = 0; i < 16; i++)
	{
		_delay_us(mw_freq);
		//заполняем данные побитно
		if(PGD_READ) tdat |= (1 << (15 - i));
		PGC_HIGH		
		_delay_us(mw_freq);
		PGC_LOW
	}
	MWCS_LOW

	return tdat;
}

void mw_writeCmd(uint8_t width, uint16_t add, uint16_t dat)
{
	uint16_t tadd;
	tadd = add | (0x05 << width);

	MWCS_HIGH
	_delay_us(mw_freq);

	//Отправляем комманду записи + адресс + бит ожидания
	for(int i = 0; i < (width + 3); i++)
	{
		if(tadd & (1 << (width + 2 - i))) PGDO_HIGH
		else PGDO_LOW
		_delay_us(mw_freq);
		PGC_HIGH
		_delay_us(mw_freq);
		PGC_LOW
	}
	//Отправляем данные на запись побитно
	for(int i = 0; i < 16; i++)
	{
		if(dat & (1 << (15 - i))) PGDO_HIGH
		else PGDO_LOW
		_delay_us(mw_freq);
		PGC_HIGH
		//заполняем данные побитно
		_delay_us(mw_freq);
		PGC_LOW
	}
	MWCS_LOW
	_delay_us(100);
}

void mw_emptyCmd(uint8_t width, uint8_t cmd)
{
	uint16_t tadd;
	tadd = cmd << (width - 2);

	MWCS_HIGH
	_delay_us(mw_freq);

	//Отправляем комманду чтения + адресс + бит ожидания
	for(int i = 0; i < (width + 3); i++)
	{
		if(tadd & (1 << (width + 2 - i))) PGDO_HIGH
		else PGDO_LOW
		_delay_us(mw_freq);
		PGC_HIGH
		_delay_us(mw_freq);
		PGC_LOW
	}

	MWCS_LOW
	_delay_us(100);
}

uint8_t mw_waitBsy(void)
{
	MWCS_HIGH
	_delay_us(400);
	if(!PGD_READ)
	{
		_delay_us(50);
		MWCS_LOW
		return 1;
	}
	MWCS_LOW
	return 0;
}
