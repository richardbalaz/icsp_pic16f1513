// Time constants
#define T_ERAB	1
#define T_PINT	10

// ICSP communication

void icsp_init();
void icsp_end();

// Commands
void icsp_move_to_config();
void icsp_move_to_program();

void icsp_move_to_address(uint16_t address);

void icsp_increment_address();

void icsp_flash(uint8_t address_high_byte, uint8_t address_low_byte, uint8_t value_high_byte, uint8_t value_low_byte);

void icsp_store_word(uint8_t high_byte, uint8_t low_byte);
uint16_t icsp_load_word();

void icsp_begin_programming();

void icsp_bulk_erase();

