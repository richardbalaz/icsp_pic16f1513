#include <avr/io.h>

#include "protocol_layer.h"
#include "uart.h"

int icsp_running = 0;

void listen_for_commands();

int main() 
{
	uart_init();

	listen_for_commands();

	while(1) continue;

	return 0;
}


void listen_for_commands() 
{
	uint8_t address_high, address_low, value_high, value_low;
	
	uint16_t address, value;

	char command;
	while(1)
	{
		command = uart_getchar();

		switch(command)
		{
			case 'B':
			{			
				icsp_init();

				icsp_running = 1;

				uart_putchar('R');

				break;
			}

			case 'Q':
			{
				icsp_end();

				icsp_running = 0;

				uart_putchar('R');

				break;
			}

			case 'E':
			{
				if (icsp_running)
				{
					icsp_bulk_erase();
				}

				uart_putchar('R');

				break;
			}

			case 'W':
			{
				address_high = uart_getchar();
				address_low = uart_getchar();

				value_high = uart_getchar();
				value_low = uart_getchar();
				
				if (icsp_running)
				{
					icsp_flash(address_high, address_low, value_high, value_low);
				}

				uart_putchar('R');

				break;
			}

			case 'R':
			{
				address_high = uart_getchar();
				address_low = uart_getchar();

				if (icsp_running)
				{
					address = 0;

					address |= address_high;
					address <<= 8;

					address |= address_low;

					icsp_move_to_address(address);

					value = icsp_load_word();

					uart_putchar((value >> 8));

					uart_putchar(value);

					uart_putchar('R');
				}
				else
				{
					uart_putchar(0);

					uart_putchar(0);

					uart_putchar('R');					
				}

				break;
			}
		}
	}
}
