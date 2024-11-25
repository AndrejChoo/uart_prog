

#ifndef I2C_H	// Блокирую повторное включение этого модуля
#define I2C_H

#include <avr/io.h>

#define F_SCL   100000

#define HW_address     0xA0
#define WAIT_COUNTER   0x3FFF

void i2c1_init(uint8_t speed);

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_sendAdd(uint8_t);
void i2c_sendData(uint8_t);
uint8_t i2c_readAck(void);
uint8_t i2c_readNack(void);

uint8_t eeprom_write_arr(uint8_t hw_add, uint16_t addr, uint8_t wide, uint8_t *data, uint16_t count, uint16_t offset);
uint8_t eeprom_read_arr(uint8_t hw_add, uint8_t wide, uint16_t addr, uint8_t *data, uint32_t count);


#endif
