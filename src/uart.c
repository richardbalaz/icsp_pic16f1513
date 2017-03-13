#include <avr/io.h>

#define F_CPU 20000000L
#define BAUD 9600

#include <util/delay.h>
#include <util/setbaud.h>

#include "uart.h"


void uart_printnum(uint16_t data)
{
	char str[8];
	itoa(data, str, 16);

	uart_putchar('D');

	uint32_t o;
	for (o = 0; o < 8; ++o)
	{
		uart_putchar(str[o]);
	}

	uart_putchar('B');

	for (o = 0x8000; o >= 0x01; o >>= 1)
	{
		if ((data & o) == 0)
		{
			uart_putchar('0');
		}
		else uart_putchar('1');
	}

	uart_putchar('\r');
	uart_putchar('\n');
}


void uart_init(void) {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

    UCSRA &= ~(_BV(U2X));

    UCSRC = _BV(UCSZ1) | _BV(UCSZ0); /* 8-bit data */
    UCSRB = _BV(RXEN) | _BV(TXEN);   /* Enable RX and TX */
}

void uart_putchar(char c) {
    loop_until_bit_is_set(UCSRA, UDRE); /* Wait until data register empty. */
    UDR = c;
}

char uart_getchar(void) {
    loop_until_bit_is_set(UCSRA, RXC); /* Wait until data exists. */
    return UDR;
}