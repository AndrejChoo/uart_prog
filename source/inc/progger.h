/*
 * progger.h
 *
 *  Created on: 19 ���. 2020 �.
 *      Author: andre
 */

#ifndef PROGGER_H_
#define PROGGER_H_

#include "usart.h"
#include "i2c.h"
#include "spi.h"
#include "gpio.h"
#include <util/delay.h>


#define MW_WEN		0x13
#define MW_WDIS		0x10
#define MW_ERAL		0x12


void deassemble_frame(void);//������� ������� �������
void send_errorFrame(void); //������� ��������� ��������� "������ ������"
void send_successConn(void); //������� �������� ������ "������������ ������������"
void send_frame(uint8_t *buff, uint8_t count); //������� �������� ������ �����
void send_arr(uint8_t marker, uint8_t *buff, uint16_t count, uint16_t offset);

//I2C EEPROM
void read_eeprom(void);
void write_eeprom(void);

//Microwire EEPROM
void read_mw(void);
void write_mw(void);

uint16_t mw_readCmd(uint8_t width, uint16_t add);
void mw_writeCmd(uint8_t width, uint16_t add, uint16_t dat);
void mw_emptyCmd(uint8_t width, uint8_t cmd);
uint8_t mw_waitBsy(void);

//SPI FLASH
void read_flash(void);
uint8_t read_sreg1(void);
void write_flash(void);

#endif /* PROGGER_H_ */
