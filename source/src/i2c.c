

#include "i2c.h"


void i2c1_init(uint8_t speed)
{
	TWBR = ((F_CPU/F_SCL)-16)/2;
}

void i2c_start(void)
{
	TWCR = (1 << TWINT)|(1 << TWSTA)|(1<<TWEN);
	while (!(TWCR & (1 << TWINT)));
}

void i2c_stop(void)
{
	TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO);
}

void i2c_sendAdd(uint8_t add)
{
	TWDR = add;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

void i2c_sendData(uint8_t dat)
{
	TWDR = dat;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t i2c_readAck(void)
{
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t i2c_readNack(void)
{
		TWCR = (1<<TWEN) | (1<<TWINT);
		while (!(TWCR & (1 << TWINT)));
		return TWDR;
}


uint8_t eeprom_write_arr(uint8_t hw_add, uint16_t addr, uint8_t wide, uint8_t *data, uint16_t count, uint16_t offset)
{
	  i2c_start();
	  i2c_sendAdd(hw_add);

	  if(wide>1)//Если двухбайтный адрес
	  {
		  //Передаём старший байт регистра адреса
		  i2c_sendData((addr & 0xFF00) >> 8);
	  }
	  //Передаём младший байт регистра адреса
	  i2c_sendData(addr & 0xFF);

	  for(uint32_t i=0; i<count; i++)
	  {
		  //отправляем байт на запись
		  i2c_sendData(data[i + offset]);
	  }
	  i2c_stop();
	  return 0;
}

uint8_t eeprom_read_arr(uint8_t hw_add, uint8_t wide, uint16_t addr, uint8_t *data, uint32_t count)
{
	  i2c_start();
	  i2c_sendAdd(hw_add);

	  if(wide>1)//Если двухбайтный адрес
	  {
		  //Передаём старший байт регистра адреса
		  i2c_sendData((addr & 0xFF00) >> 8);
	  }
	  //Передаём младший байт регистра адреса
	  i2c_sendData(addr & 0xFF);

	  i2c_start();
	  i2c_sendAdd(hw_add | 0x01);

	  for(uint32_t i=0; i < count - 1; i++)
	  {
		  //отправляем байт на запись
		  data[i] = i2c_readAck();
	  }
	  data[count - 1] = i2c_readNack();
	  i2c_stop();
	  return 0;
}


