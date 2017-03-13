// Clock Configuration

#define F_CPU 20000000L

// Port Configuration

#define ICSP_PORTREG	PORTB
#define ICSP_DIRREG		DDRB
#define ICSP_PINREG		PINB

// Pin Configuration

#define ICSP_DAT		PB0
#define ICSP_CLK		PB1
#define ICSP_MCLR		PB2

// Pin status macros

#define icsp_clk_high()	(ICSP_PORTREG |= (1 << ICSP_CLK))
#define icsp_clk_low()	(ICSP_PORTREG &= ~(1 << ICSP_CLK))

#define icsp_dat_high()	(ICSP_PORTREG |= (1 << ICSP_DAT))
#define icsp_dat_low()	(ICSP_PORTREG &= ~(1 << ICSP_DAT))

#define icsp_mclr_high()	(ICSP_PORTREG |= (1 << ICSP_MCLR))
#define icsp_mclr_low()		(ICSP_PORTREG &= ~(1 << ICSP_MCLR))

#define icsp_dat_as_input()		(ICSP_DIRREG &= ~(1 << ICSP_DAT))
#define icsp_dat_as_output()	(ICSP_DIRREG |= (1 << ICSP_DAT))

#define icsp_clk_as_output()	(ICSP_DIRREG |= (1 << ICSP_CLK))
#define icsp_mclr_as_output()	(ICSP_DIRREG |= (1 << ICSP_MCLR))

#define icsp_dat_pullup_on()	(ICSP_PORTREG |= (1 << ICSP_DAT))
#define icsp_dat_pullup_off()	(ICSP_PORTREG &= ~(1 << ICSP_DAT))

#define icsp_dat_is_high()		(((ICSP_PINREG & (1 << ICSP_DAT)) == 0) ? 0 : 1)

// Time constants

#define T_ENTH	1

// Clock 1uS high, 1uS low
#define T_CKH	1
#define T_CKL	1

// After every write wait 2uS
#define T_DLY	2

// Bus I/O functions

void icsp_bus_init();
void icsp_bus_end();

// Writes bus with data of length (writes LSB-first)
void icsp_write(uint64_t data, uint64_t len);

// Read 14 bit and returns as uint16_t (returns MSB-first)
uint16_t icsp_read();