#include <avr/io.h>

#include "hw_layer.h"
#include "protocol_layer.h"

#include <util/delay.h>

uint16_t current_address = 0x00;

void icsp_init()
{
	icsp_bus_init();

	icsp_write(0x4D434850, 33);
}

void icsp_end()
{
	icsp_bus_end();
}

void icsp_flash(uint8_t address_high_byte, uint8_t address_low_byte, uint8_t value_high_byte, uint8_t value_low_byte)
{
	uint16_t address = 0;
	
	address |= address_high_byte;
	address <<= 8;

	address |= address_low_byte;

	icsp_move_to_address(address);

	icsp_store_word(value_high_byte, value_low_byte);

	icsp_begin_programming();
}

void icsp_move_to_config()
{
	icsp_write(0x00, 6);
	icsp_write(0x00, 16);	

	current_address = 0x8000;
}

void icsp_move_to_program() 
{
	icsp_write(0x16, 6);

	current_address = 0x0000;
}

void icsp_move_to_address(uint16_t address)
{
	if (address == current_address)
	{
		return;
	}

	if ((address >= 0x8000) && (current_address < 0x8000))
	{
		icsp_move_to_config(); // move to 0x8000
	}
	else if ((address < 0x8000) && (current_address >= 0x8000))
	{
		icsp_move_to_program(); // move to 0x0000
	}

	if (address < current_address)
	{
		if (address >= 0x8000)
		{
			icsp_move_to_config();
		}
		else if(address < 0x8000)
		{
			icsp_move_to_program();
		}
	}

	uint16_t i;
	uint16_t steps = address - current_address;

	for (i = 0; i < steps; ++i)
	{
		icsp_increment_address();
	}
}

void icsp_increment_address()
{
	icsp_write(0x06, 6);

	current_address++;
}

void icsp_store_word(uint8_t high_byte, uint8_t low_byte)
{
	icsp_write(0x02, 6);

	uint64_t word = 0;

	word |= high_byte;
	word <<= 8;

	word |= low_byte;
	word <<= 1;

	icsp_write(word, 16);
}

uint16_t icsp_load_word()
{
	icsp_write(0x04, 6);

	return icsp_read();
}


void icsp_begin_programming()
{
	icsp_write(0x08, 6);

	_delay_ms(T_PINT);
}

void icsp_bulk_erase()
{
	icsp_move_to_config();

	icsp_write(0x09, 6);

	_delay_ms(T_ERAB);
}
